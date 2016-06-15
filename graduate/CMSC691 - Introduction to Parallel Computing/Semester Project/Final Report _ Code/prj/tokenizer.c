
// Tokenzier
// Patrick Trinkle
// Mike Corbin
// CMSC691 - Parallel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "tokenizer.h"

#include "mpi.h"

int main(int argc, char **argv)
{
	//const char *pathname = "/bluegrit/pvfs1/tri1/";
	const char *pathname = "/home/corbin2/userset/userset/";
	struct dirent *dp = NULL;
	struct dirent *xp = NULL;
	char tmp[MAX_PATH_LENGTH];
	uint32_t userfolderlen = 0;
	uint32_t pathlen = strlen(pathname);
	DIR *dir = NULL;
	int i, numclients;

	/* MPI STUFF */
	int numprocs, myid;
	int tag = 31;

	MPI_Datatype userCounts;
	MPI_Datatype type[2] = {MPI_CHAR, MPI_UNSIGNED};
	int blocklen[2] = {MAX_PATH_LENGTH, STOPWORDS_CNT};
	MPI_Aint disp[2];

	MPI_Status status;
	MPI_Comm world = MPI_COMM_WORLD;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	disp[0] = (uint32_t)&user_terms.user[0] - (uint32_t)&user_terms;
	disp[1] = (uint32_t)&user_terms.counts[0] - (uint32_t)&user_terms;
	MPI_Type_create_struct(2, blocklen, disp, type, &userCounts);
	MPI_Type_commit(&userCounts);

	if (numprocs < 3) {
		printf("Not enough MPI Processes, minimum 3\n");
		MPI_Finalize();
		exit( -1 );
	}

	numclients = numprocs - 2; // discount distroserver and printserver

	if (DISTROSERVER == myid) {
		char more = ' ';

#ifdef PRINT_STATUS
		printf("I am the distro server %d.\n", myid);
#endif
		dir = opendir(pathname);
		if (dir == NULL) {
			printf("opendir(%s) failed.\n", pathname);
			exit( -1 );
		}

		// get list of user directories
		while ((dp = readdir(dir)) != NULL) {
			// hidden directory .x or . or ..
			if (strncmp(dp->d_name, ".", 1) != 0) {
				userfolderlen = strlen(dp->d_name);

				bzero(&(tmp[0]), sizeof(tmp));	
				strncpy(tmp, pathname, pathlen);
				strncat(tmp, dp->d_name, userfolderlen);

				// listen for a request from a client
				MPI_Recv(&(more), 1, MPI_CHAR, MPI_ANY_SOURCE, SERVERTAG, world, &status);

#ifdef PRINT_STATUS
				printf("Received request from: %d\n", status.MPI_SOURCE);
#endif
				// this is a client's way of asking for data
				if ('m' == more)
					MPI_Send(&(tmp[0]), sizeof(tmp), MPI_CHAR, status.MPI_SOURCE, SERVERTAG, world);
			}
		}

		// terminate the clients
#ifdef PRINT_STATUS
		printf("Server out of users to distribute, sending term user\n");
#endif

		bzero(&(tmp[0]), sizeof(tmp));
		strncpy(tmp, "done", 4);
		i = 0;

#ifdef PRINT_STATUS
		printf("DistroServer: Waiting on %d clients.\n", numclients);
#endif

		while (i < numclients) {
			MPI_Recv(&(more), 1, MPI_CHAR, MPI_ANY_SOURCE, SERVERTAG, world, &status);
			MPI_Send(&(tmp[0]), sizeof(tmp), MPI_CHAR, status.MPI_SOURCE, SERVERTAG, world);
			i++;
		}

		closedir(dir);

		strncpy(&(user_terms.user[0]), "fakeuser", MAX_PATH_LENGTH);

		MPI_Send(&(user_terms), 1, userCounts, PRINTSERVER, PRINTTAG, world);

	}
	else {
		char usernamebuf[MAX_PATH_LENGTH];
		char more = 'm';
		uint32_t work = 1;
		uint32_t fileCnt = 0;

#ifdef PRINT_STATUS
		printf("I am a worker bee: %d\n", myid);
#endif
		while (work) {
#ifdef PRINT_STATUS
			printf("%d, Sending request.\n", myid);
#endif
			bzero(&(usernamebuf[0]), sizeof(usernamebuf));

			MPI_Send(&(more), 1, MPI_CHAR, DISTROSERVER, SERVERTAG, world);

			MPI_Recv(
				&(usernamebuf[0]),
				sizeof(usernamebuf),
				MPI_CHAR,
				DISTROSERVER,
				SERVERTAG,
				world,
				&status);

#ifdef PRINT_STATUS
			printf("%d, Received user: %s\n", myid, usernamebuf);
#endif
			if (strcmp(usernamebuf, "done") == 0) {
#ifdef PRINT_STATUS
				printf("done...\n");
#endif
				break;
			}

			// process_user clears out and fixes up user_terms
			fileCnt = process_user(usernamebuf);

#ifdef PRINT_STATUS
			printf("user %d has processed %d files\n", myid, fileCnt);
#endif

			MPI_Send(&(user_terms), 1, userCounts, PRINTSERVER, PRINTTAG, world);
		}

#ifdef PRINT_STATUS
		printf("user %d has broken from loop\n", myid);
#endif
	}

	MPI_Finalize();

	return 0;
}

int
process_user(const char *userfolder)
{
	char username[MAX_PATH_LENGTH];
	char ftmp[MAX_PATH_LENGTH];
	char *local = NULL;
	char *directory = NULL;
	char delims[] = "/";
	int filelen = 0;
	int userfolderlen = strlen(userfolder);
	int filenamelen = 0;
	struct dirent *xp = NULL;
	uint32_t i = 0;

	// clear out user terms structure
	bzero(&(user_terms), sizeof(user_terms));
	bzero(&(username[0]), sizeof(username));

	// copy path into user for parsing
	strncpy(username, userfolder, MAX_PATH_LENGTH);
	filelen = strlen(username);

	// extract username from path
	directory = strtok(username, delims);

	if (directory != NULL) {
		filelen -= (strlen(directory) + 1);

		while (filelen > 0) {
			local = strtok(NULL, delims);
			filelen -= ( strlen(local) + 1 );
		}
	}

#ifdef PRINT_STATUS
	printf("Processing user: %s\n", local);
#endif

	// copy username path into username field
	strncpy(&(user_terms.user[0]), local, MAX_PATH_LENGTH);

	// start processing files in user directory
	DIR *user = opendir(userfolder);

	if (NULL == user) {
		printf("%s failed to open.\n", userfolder);
		return 0;
	}

	while ((xp = readdir(user)) != NULL) {
		if (strncmp(xp->d_name, ".", 1) != 0) {
			filenamelen = strlen(xp->d_name);

			bzero(&(ftmp[0]), sizeof(ftmp));
			strncpy(ftmp, userfolder, userfolderlen);
			strncat(ftmp, "/", 1);
			strncat(ftmp, xp->d_name, filenamelen);

			// process email sorted preprocessed email file
			i++;
			process_file(ftmp);
		}
	}

	closedir(user);

	return i;
}

void
process_file(const char *filepath)
{
	int i, b, j, stopCnt;
	char tokenbuffer[MAX_TOKEN_LENGTH];

	//printf("Processing file: %s\n", filepath);
	FILE *fd = fopen(filepath, "r");
	if (fd == NULL) {
		printf("could not open: %s\n", filepath);
		return;
	}

	/* initializer tokenbuffer */
	bzero(&(tokenbuffer[0]), sizeof(tokenbuffer));

	b = fgetc(fd);

	i = 0;
	while (EOF != b) {
		/* make lowercase */
		if ('A' <= b && b <= 'Z')
			b += ' ';

		if (':' == b) {
			if (strcmp(tokenbuffer, "to") == 0) {
				//printf("found to:, breaking\n");
				break; // early out
			}
		}

		if ('a' <= b && b <= 'z') {
			tokenbuffer[i++] = b; // if i is not max length it'll get caught below
		} else if (' ' == b
			|| '\n' == b
			|| '\t' == b
			|| '\r' == b) {
				if (strlen(tokenbuffer) > 0) {
					for (j = 0; j < STOPWORDS_CNT; j++) {
						if (strcmp(tokenbuffer, terms[j]) == 0) {
							//token is in list
							user_terms.counts[j]++;
						}
					}

					bzero(&(tokenbuffer[0]), sizeof(tokenbuffer));
					i = 0;
				}
		}

		if (MAX_TOKEN_LENGTH == i) {
			// this means we are now pointing beyond tokenbuffer
			// and none of the terms we care about are this long
			bzero(&(tokenbuffer[0]), sizeof(tokenbuffer));
			i = 0;
		}

		b = fgetc(fd);
	}

	if (0 != fclose(fd))
		printf("Could not close file\n");

	return;
}

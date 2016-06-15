/*****************************************
 ** File: dm.c
 ** Author: Patrick Trinkle
 ** Date: March 1, 2006
 ** E-Mail: tri1@umbc.edu
 **
 ** This program emulates the producer/
 ** consumer problem using doonut makers as
 ** producers and students as consumers. 
 ** For more information see README.txt
 *****************************************/

#include "dm.h"

int main(int argc, char * argv[])
{
   int M = 0; /* numMakers must be >= 5 */
   int S = 0; /* shelves */
   int D = 0; /* donuts / shelf */
   int Z = 0; /* maker naps for Z ms */
   int C = 0; /* C ms to make a donut */
   int B = 0; /* donuts per batch >= 10 */
   int U = 0; /* U >= 7 students */
   int E = 0; /* E ms to eat a donut */
   int H = 0; /* num donuts before full */
   int R = 0; /* R ms sleeping */
   int N = 0; /* srandom seed */
   
   if (argc != 23)
   {
      fprintf(stderr, "No enough cmds.\n");
      exit(-1);
   }
   
   int arg = 0;
   /* arg = 0 is the program file */
   for (arg = 1; arg < argc; ++arg)
   {
      if (strcmp(argv[arg], "-m") == 0)
      {
	 M = atoi(argv[arg+1]);
	 arg++;
      }
      else if (strcmp(argv[arg], "-s") == 0)
      {
	 S = atoi(argv[arg+1]);
	 arg++;
      }
      else if (strcmp(argv[arg], "-d") == 0)
      {
	 D = atoi(argv[arg+1]);
	 arg++;
      }
      else if (strcmp(argv[arg], "-z") == 0)
      {
	 Z = atoi(argv[arg+1]);
	 arg++;
      }
      else if (strcmp(argv[arg], "-c") == 0)
      {
	 C = atoi(argv[arg+1]);
	 arg++;
      }
      else if (strcmp(argv[arg], "-b") == 0)
      {
	 B = atoi(argv[arg+1]);
	 arg++;
      }
      else if (strcmp(argv[arg], "-u") == 0)
      {
	 U = atoi(argv[arg+1]);
	 arg++;
      }
      else if (strcmp(argv[arg], "-e") == 0)
      {
	 E = atoi(argv[arg+1]);
	 arg++;
      }
      else if (strcmp(argv[arg], "-h") == 0)
      {
	 H = atoi(argv[arg+1]);
	 arg++;
      }
      else if (strcmp(argv[arg], "-r") == 0)
      {
	 R = atoi(argv[arg+1]);
	 arg++;
      }
      else if (strcmp(argv[arg], "-n") == 0)
      {
	 N = atoi(argv[arg+1]);
	 arg++;
      }
      else
      {
	 /* runHelp(); */
	 exit(-2);
      }
   }
   
   if (M < 5 || U < 7 || B < 10)
   {
      fprintf(stderr, "M >= 5, U >= 7, B >= 10\n");
      exit(-3);
   }
   
   numShelves = S;
   numDonuts = D;
   srandom(N);

   M = random() % (M - 4 + 1) + 5;
   U = random() % (U - 6 + 1) + 7;
      
   /* semaphore stuff */
   /* mutex */
   baker = semget(IPC_PRIVATE, S, IPC_CREAT);
   student = semget(IPC_PRIVATE, S, IPC_CREAT);
   
   /* set stuff */
   int semCount = 0;
   
   /* set mutex to 1 */
   for (semCount = 0; semCount < numShelves; ++semCount)
   {
      struct sembuf set_baker = {semCount, 1, 0};
      semop(baker, &set_baker, 1);
   }
   for (semCount = 0; semCount < numShelves; ++semCount)
   {
      struct sembuf set_student = {semCount, 1, 0};
      semop(student, &set_student, 1);
   }


   /* file stuff */
   FILE * opf = NULL;
      
   /* shared memory stuff */
   int * sharedbaker_shelf = NULL;
   int * sharedstudent_shelf = NULL;
   int * sharedbaker_in = NULL;
   int * sharedbaker_out = NULL;
   int * sharedstudent_in = NULL;
   int * sharedstudent_out = NULL;
   int segment_shelf_sze, segment_shelf_id;
   int inout_sze, segment_in_id, segment_out_id;
   
   pid_t pid;
   
   segment_shelf_sze = sizeof(int) * numShelves * numDonuts;
   inout_sze = sizeof(int) * numShelves;
   
   /* IPC_CREAT | 0666 works to */
   segment_shelf_id = shmget(IPC_PRIVATE, segment_shelf_sze, IPC_CREAT|0777);
   segment_in_id = shmget(IPC_PRIVATE, inout_sze, IPC_CREAT|0777);
   segment_out_id = shmget(IPC_PRIVATE, inout_sze, IPC_CREAT|0777);
   
   shelves = (int *) shmat(segment_shelf_id, NULL, 0);
   producer = (int *) shmat(segment_in_id, NULL, 0);
   consumer = (int *) shmat(segment_out_id, NULL, 0);
   if (shelves < 0 || producer < 0 || consumer < 0)
   {
      fprintf(stderr, "Ahh, couldn't attach!\n");
      exit(-1);
   }
   
   /* initialize stuff */
   int i = 0;
   for (i = 0; i < (numShelves * numDonuts); ++i)
    shelves[i] = 0;
   
   for (i = 0; i < numShelves; ++i)
   {
      producer[i] = 0;
      consumer[i] = 0;
   }

   /* begin forking bakers */
   int bakerCount;
   for (bakerCount = 0; bakerCount < M; ++bakerCount)
   {
      pid = fork();
      if (pid < 0)
      {
	 fprintf(stderr, "Go fork yourself.\n");
	 exit(-2);
      }
      
      if (pid == 0)
      {
	 sharedbaker_in = (int *) shmat(segment_in_id, NULL, 0);
	 sharedbaker_out = (int *) shmat(segment_out_id, NULL, 0);
	 sharedbaker_shelf = (int * ) shmat(segment_shelf_id, NULL, 0);
	 if (sharedbaker_shelf < 0 || sharedbaker_in < 0 || sharedbaker_out < 0)
	 {
	    fprintf(stderr, "Child couldn't attach.\n");
	    exit(-3);
	 }

	 /* set baker vars */
	 int bakerID = bakerCount + 1;
	 int batchID = 1;
	 int donutID = 0;
	 int location = 0;
	 int iteration = 0;
	 float setuprandom = 0;

	 char * b_string[17];
	 sprintf(b_string, "out_baker_%d.txt", bakerID);
	 opf = fopen(b_string, "w");

	 /* print my stuff */
	 fprintf(opf, "Baker #%d\n", bakerID);

	 /* random 0 - 1 */
	 setuprandom = (float) random() / RAND_MAX;

	 /* iterate */
	 for (iteration = 0; iteration < 10; ++iteration)
	 {    	      
	    donutID = 0;
	    int donutCount = 1;
	    int batchCounter = 0;
	    
	    if (setuprandom > 0.50)
	    {
	       usleep(Z * 1000);
	       setuprandom = 0;
	    }
	    
	    while(batchCounter < B)
	    {
	       int shelf_id = (int) ((float)numShelves * random() / (RAND_MAX + 1.0));
	       
	       struct sembuf sem_wbake = {shelf_id, -1, 0};
	       struct sembuf sem_sbake = {shelf_id, 1, 0};
	       
	       /* while not 10 in a row and not full */
	       while(donutCount < 11 && batchCounter < B
		     && ((sharedbaker_in[shelf_id] + 1) % numDonuts) != sharedbaker_out[shelf_id])
	       {		 	  
		  batchCounter++;
		  donutID++;
		  donutCount++;
		  
		  usleep(C * 1000);

		  fprintf(opf, "A donut is produced, Batch: %d; Donut: %d\n", batchID, donutID);

		  location = (shelf_id * numDonuts) + sharedbaker_in[shelf_id];
		      
		  if (semctl(baker, shelf_id, GETVAL) == 0)
		     fprintf(opf, "Waiting for the shelf to free.\n");

		  semop(baker, &sem_wbake, 1);
		  sharedbaker_shelf[location] = 1;
		  semop(baker, &sem_sbake, 1);

		  sharedbaker_in[shelf_id] = (sharedbaker_in[shelf_id] + 1) % numDonuts;

		  fprintf(opf, "A donut is put on the shelf, id: %d\n", donutID);
	       }
	       
	       donutCount = 0;
	    }
	    /* sleep after making a batch */
	    usleep(Z * 1000);
	    batchID++;
	 }
	 
	 if (shmdt(sharedbaker_shelf) == -1 || shmdt(sharedbaker_in) == -1 || shmdt(sharedbaker_out) == -1)
	    fprintf(stderr, "Child couldn't detach.\n");
	 
	 exit(0);
      }
   }
   
   /* begin forking students */
   int studentCount = 0;
   for (studentCount = 0; studentCount < U; ++studentCount)
   {
      pid = fork();
      if (pid < 0)
      {
	 fprintf(stderr, "Go fork yourself.\n");
	 exit(-2);
      }
      
      if (pid == 0)
      {
	 sharedstudent_in = (int *) shmat(segment_in_id, NULL, 0);
	 sharedstudent_out = (int *) shmat(segment_out_id, NULL, 0);
	 sharedstudent_shelf = (int * ) shmat(segment_shelf_id, NULL, 0);
	 if (sharedstudent_shelf < 0 || sharedstudent_in < 0 || sharedstudent_out < 0)
	 {
	    fprintf(stderr, "Child couldn't attach.\n");
	    exit(-3);
	 }
	 
	 /* set student vars */
	 int location = 0;
	 int sdonutID = 0;
	 int iteration = 0;
	 int donutCounter = 0;
	 int shelf_id = 0;
	 
	 char * s_string[19];
	 sprintf(s_string, "out_student_%d.txt", studentCount + 1);
	 opf = fopen(s_string, "w");

	 fprintf(opf, "Student ID: %d\n", studentCount + 1);

	 /* iterate */
	 for (iteration = 0; iteration < 10; ++iteration)
	 {
	    donutCounter = 0;
	    
	    while(donutCounter < H)
	    {
	       shelf_id = (int) ((float)numShelves * random() / (RAND_MAX + 1.0));
	       
	       struct sembuf sem_wstudent = {shelf_id, -1, 0};
	       struct sembuf sem_sstudent = {shelf_id, 1, 0};
	       
	       /* student never waits */
	       while(donutCounter < H 
		     && sharedstudent_in[shelf_id] != sharedstudent_out[shelf_id] 
		     && semctl(student, shelf_id, GETVAL) != 0)
	       {
		  donutCounter++;
		  sdonutID++;
		  usleep(E * 1000);
		  
		  location = (shelf_id * numDonuts) + sharedstudent_out[shelf_id];

		  semop(student, &sem_wstudent, 1);
		  sharedstudent_shelf[location] = 0;
		  semop(student, &sem_sstudent, 1);
		  fprintf(opf, "Donut eaten: %d\n", sdonutID);
		  
		  sharedstudent_out[shelf_id] = (sharedstudent_out[shelf_id] + 1) % numDonuts;
	       }
	    }
	    /* studying after eating H */
	    usleep(R * 1000);
	 }
	 
	 if (shmdt(sharedstudent_shelf) == -1 || shmdt(sharedstudent_in) == -1 || shmdt(sharedstudent_out) == -1)
	    fprintf(stderr, "Child couldn't detach.\n");
	 
	 exit(0);
      }
    }
   
   for(i = 0; i < (M + U); i++)
      wait(NULL);
   
   if (shmdt(shelves) == -1)
      fprintf(stderr, "Parent couldn't detach.\n");
   
   if (shmdt(producer) == -1)
      fprintf(stderr, "Parent couldn't detach.\n");
   
   if (shmdt(consumer) == -1)
      fprintf(stderr, "Parent couldn't detach.\n");
   
   shmctl(segment_shelf_id, IPC_RMID, NULL);
   shmctl(segment_in_id, IPC_RMID, NULL);
   shmctl(segment_out_id, IPC_RMID, NULL);
   
   semctl(baker, 0, IPC_RMID, 0);
   semctl(student, 0, IPC_RMID, 0);
   
   return 0;
}

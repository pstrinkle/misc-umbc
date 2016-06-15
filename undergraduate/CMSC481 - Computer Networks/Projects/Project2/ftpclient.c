/****************************************************
 ** File: ftpclient.c
 ** Author: Patrick Trinkle
 ** Date: 4/3/2006
 ** Email : tri1@umbc.edu
 **
 **
 ** This is the FTP Client
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <unistd.h>

#define COMPORT  3541
#define BUFSZE   4096

void commandprompt(int socket_id);

int  getmessage(int socket_id);
void sendmessage(int socket_id, char * message);

void put(int socket_id, char * filename);
void get(int socket_id, char * message);
void ls(int socket_id, char * filename);

int main(int argc, char * argv[])
{
   /* check commond-line arguments */
   if ( argc != 2 )
   {
      fprintf( stderr, "Proper usage: ftp.whatever.whatever\n" );
      exit(-1);
   }
   
   int hostname = 0;
   int port = COMPORT;

   hostname = 1;
      
   int s_socket;
   struct sockaddr_in server_address;
   struct hostent * server;
   
   /* create socket */
   s_socket = socket( AF_INET, SOCK_STREAM, 0 );
   if ( s_socket < 0 )
   {
      fprintf( stderr,"Could not create socket.\n" );
      exit(-2);
   }
   
   /* get server */
   server = gethostbyname( argv[hostname] );
   if ( server == NULL )
   {
      fprintf( stderr,"Host not found\n" );
      exit(-3);
   }
   
   /* clear values of struct */
   memset( (char *) &server_address, '\0', sizeof(server_address) );
   
   /* begin setting values */
   server_address.sin_family = AF_INET;
   
   /* setting s_address in in_addr struct */ 
   memcpy( (char *)&server_address.sin_addr.s_addr, (char *)server->h_addr, server->h_length );
   
   /* set server port */
   server_address.sin_port = htons(port);
   
   /* try to connect */
   int connection = 0;
   connection = connect(s_socket, (struct sockaddr *)&server_address, sizeof(server_address));
   if ( connection < 0 )
   {
      fprintf(stderr, "Could not connect.\n");
      exit(-3);
   }
   
   printf("Connected to %s\n", server -> h_name);
   
   /* begin command set function */
   
   commandprompt(s_socket);

   close( s_socket );
   
   return 0;
}

int getmessage(int socket_id)
{
   /* char message[BUFSZE]; */
   
   char code[4];
   int codenum = 0;
   char * message;
   message = (char *)malloc(sizeof(char) * BUFSZE);
   char value[4];
   char isMulti[2];

   int read_message = 0;

   memset( message, '\0', BUFSZE );
   memset( value, '\0', 4 );
   memset( isMulti, '\0', 2);
   memset( code, '\0', 4);

   /* initial read */

   read_message = recv( socket_id, message, BUFSZE, 0 );
   if ( read_message < 0 )
   {
      fprintf( stderr, "Could not read from socket.\n");
      exit( -6 );
   }

   printf("%s", message);

   isMulti[0] = message[3];

   strncpy(code, message, 3);
   codenum = atoi(code);

   /* if multiline, read until matched with space */
   if ( strcmp(isMulti, "-") == 0 )
   {
      strncpy(value, message, 3);

      memset( message, '\0', BUFSZE );

      /* run while not repeat number with following space */
      do
      {
         memset( message, '\0', BUFSZE );

         read_message = recv( socket_id, message, BUFSZE, 0 );
         if ( read_message < 0 )
         {
            fprintf( stderr, "Couldn't read from socket.\n");
            exit( -6 );
         }

         printf("%s", message );

	 isMulti[0] = message[3];
      }
      while( strncmp(message, value, 3) != 0 );

   }

   free(message);

   /* end read */
   return codenum;
}

void commandprompt(int socket_id)
{
   int code;
   char * input;
   char * cleaned;
   char * send;
   input = (char *) malloc(sizeof(char) * BUFSZE);
   cleaned = (char *) malloc(sizeof(char) * BUFSZE);
   send = (char *) malloc(sizeof(char) * BUFSZE);

   memset(input, '\0', BUFSZE);
   memset(cleaned, '\0', BUFSZE);
   memset(send, '\0', BUFSZE);

   code = getmessage(socket_id);

   /* Handle Commands */
   do
   {
      printf("ftp>");
      fgets(input, BUFSZE, stdin);

      if (strncasecmp(input, "PWD", 3) == 0)
      {
	 strncpy(input, "PWD", 3);
	 sendmessage(socket_id, input);
	 code = getmessage(socket_id);
      }
      else if (strncasecmp(input, "NOOP", 4) == 0)
      {
	 strncpy(input, "NOOP", 4);
	 sendmessage(socket_id, input);
	 code = getmessage(socket_id);
      }
      else if (strncasecmp(input, "CD", 2) == 0)
      {
	 strncpy(input, "CD", 2);
	 if ( strlen(input) > 3 )
	 {
	    sendmessage(socket_id, input);
	    code = getmessage(socket_id);
	 }
	 else
	    printf("Invalid Command, cd dirname\n");
      }
      else if (strncasecmp(input, "LS", 2) == 0)
      {
	 char cmd[4];
	 char filename[BUFSZE];

	 memset(filename, '\0', BUFSZE);

	 sscanf(input, "%s %s\n", cmd, filename);

	 if (strlen(filename) == 0)
	    strcpy(filename, " ");

	 ls(socket_id, filename);
      }
      else if (strncasecmp(input, "GET", 3) == 0)
      {
	 char cmd[4];
	 char getfilename[BUFSZE];

	 memset(getfilename, '\0', BUFSZE);

	 sscanf(input, "%s %s\n", cmd, getfilename);

         get(socket_id, getfilename);
      }
      else if (strncasecmp(input, "PUT", 3) == 0)
      {
	 char cmd[4];
	 char putfilename[BUFSZE];
	 
	 memset(putfilename, '\0', BUFSZE);

	 sscanf(input, "%s %s\n", cmd, putfilename);

	 put(socket_id, putfilename);
      }
      else if (strncasecmp(input, "QUIT", 4) == 0)
      {
	 strncpy(input, "QUIT", 4);
	 sendmessage(socket_id, input);
	 code = getmessage(socket_id);
      }
      else
      {
	 printf("Invalid command.\n");
      }
   }
   while(strncasecmp(input, "QUIT", 4) != 0);

   printf("\n");

   free(input);
   free(input);
   free(send);

   return;
}

void sendmessage(int socket_id, char * message)
{
   /* Sends message over socket */
   int read_write = 0;

   read_write = send( socket_id, message, strlen(message), 0 );

   if ( read_write < 0 )
   {
      fprintf( stderr, "Could not write to socket.\n");
      exit( -5 );
   }

   return;
}

void get(int socket_id, char * filename)
{
   /* executes get command */
   char * endoffile = "@$ EOF";
   
   int codenum = 0;

   char * fail = "500 Cancel Action.\n";
   char * okay = "200 Okay to send.\n";

   char * message;
   message = (char *)malloc(sizeof(char) * BUFSZE);

   char * localFilename;
   localFilename = (char *)malloc(sizeof(char) * (BUFSZE - 4));

   char * filenamestring;
   filenamestring = (char *)malloc(sizeof(char) * (BUFSZE - 4));

   if (message == NULL || localFilename == NULL || filenamestring == NULL)
   {
      fprintf(stderr, "Not Enough Memory\n");
      exit(-4);
   }

   strcpy(filenamestring, filename);

   int read_message = 0;

   memset( message, '\0', BUFSZE );

   FILE * opf = NULL;

   /* clean filename */
   /* this will get the filename even if it is
      buried within the file structure string */

   char delims[] = "/";
   char *directory = NULL;
   int filelen = strlen(filename);

   directory = strtok(filename, delims );

   if ( directory != NULL )
   {
      filelen -= ( strlen(directory) + 1 );

      while ( filelen > 0 )
      {
	 localFilename = strtok( NULL, delims );
	 filelen -= ( strlen(localFilename) + 1 );
      }
   }
   else
      strcpy(localFilename, filename);

   /* send command */

   fprintf(stderr, "Requesting: %s\n", filenamestring);
   fprintf(stderr, "Saving as: %s\n", filename);

   sprintf(message, "%s %s\n", "RETR", filenamestring);
   sendmessage(socket_id, message);
   
   codenum = getmessage(socket_id);
   
   if ( codenum == 200 )
   {
      memset(message, '\0', BUFSZE);
      
      fprintf(stderr, "Attempging to open: %s\n", filename);
      
      opf = fopen(filename, "w");
      if (opf == NULL)
      {
	 printf("Failed to open: %s\n", filename);
	 strcpy(message, fail);
      }
      else
	 strcpy(message, okay);
      
      sendmessage(socket_id, message);

      if (opf != NULL) {
	 do
	 {
	    memset(message, '\0', BUFSZE);
	    
	    read_message = recv( socket_id, message, BUFSZE, 0 );
	    if ( read_message < 0 )
	    {
	       fprintf( stderr, "Could not read from socket.\n");
	       exit( -6 );
	    }
	    
	    if ( strcmp(message, endoffile) != 0 )
	    fprintf(opf, "%s", message);
	 }
	 while( strcmp(message, endoffile) != 0 );
	 
	 fclose(opf);
      }
   }
   
   free(message);
   
   return;
}

void put(int socket_id, char * filename)
{
   /* executes put command */
   char * failed = "500 Failed to open ";
   char * endoffile = "@$ EOF";

   int codenum = 0;

   char * message;
   message = (char *)malloc(sizeof(char) * BUFSZE);
   memset( message, '\0', BUFSZE );

   char * cmd = "STOR ";

   FILE * ipf = NULL;
   ipf = fopen(filename, "r");

   unsigned int usecs = 10;

   /* send: Can I open the file to send? */
   if (ipf == NULL)
   {
      sprintf(message, "%s%s\n", failed, filename);
      printf("%s", message);
   }
   else
   {
      memset(message, '\0', BUFSZE );
      sprintf(message, "%s %s\n", cmd, filename);
      sendmessage(socket_id, message);

      memset( message, '\0', BUFSZE );

      /* can they open on their side? */
      codenum = getmessage(socket_id);

      if (codenum == 200)
      {

	 /* they can, send file */
         while ( fgets(message, BUFSZE, ipf) )
         {
            sendmessage(socket_id, message);

            memset( message, '\0', BUFSZE );

            usleep(usecs);
         }

	 /* send end of file */
         sendmessage(socket_id, endoffile);
      }

      fclose(ipf);
   }

   free(message);

   return;
}

void ls(int socket_id, char * filename)
{
   /* executes ls command */
   char * none = " ";
   char * message;
   int read_message = 0;
   char * endoffile = "@$ EOF";

   message = (char *)malloc(sizeof(char) * BUFSZE);
   memset(message, '\0', BUFSZE);

   if ( strcmp(filename, none) == 0 )
      sprintf(message, "%s %s\n", "NLST", ".");
   else
      sprintf(message, "%s %s\n", "NLST", filename);

   /* send initial command */
   sendmessage(socket_id, message);

   /* can they send data? */
   int codenum = getmessage(socket_id);
   
   if ( codenum == 200 )
   {
      do
      {
	 memset(message, '\0', BUFSZE);
	 
	 read_message = recv( socket_id, message, BUFSZE, 0 );
	 if ( read_message < 0 )
	 {
	    fprintf( stderr, "Could not read from socket.\n");
	    exit( -6 );
	 }
	 
	 if ( strcmp(message, endoffile) != 0 )
	    fprintf(stdout, "%s", message);
      }
      while( strcmp(message, endoffile) != 0 );
   }

   free(message);
   

   return;
}

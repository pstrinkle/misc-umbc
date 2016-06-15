/****************************************************
 ** File: ftpserver.c
 ** Author: Patrick Trinkle
 ** Date: 4/3/2006
 ** Email : tri1@umbc.edu
 **
 **
 ** The FTP Server for the special FTP Client
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <dirent.h>

#define BUFSZE 4096
#define PORT   3541

void   clienthandle(int socket_id);

char * getcommand(int socket_id);
void   sendmessage(int socket_id, char * message);

void   retr(int socket_id, char * filename);
void   stor(int socket_id, char * filename);
void   nlst(int socket_id, char * filename);

int    getmessage(int socket_id);

int main(int argc, char * argv[])
{
   int port = PORT;

   int s_socket;
   int new_socket;
   int client_addr_len;

   struct sockaddr_in server_address, client_address;

   /* create socket */

   s_socket = socket( AF_INET, SOCK_STREAM, 0 );
   if ( s_socket < 0 )
   {
      fprintf( stderr,"Could not create socket.\n" );
      exit( -2 );
   }

   /* get server */

   /* clear values of struct */
   memset( (char *) &server_address, '\0', sizeof(server_address) );

   /* begin setting values */
   server_address.sin_family = AF_INET;

   /* setting s_address in in_addr struct */ 
   server_address.sin_addr.s_addr = INADDR_ANY;

   /* set server port */
   server_address.sin_port = htons( port );

   int binding;

   /* bind to port */
   binding = bind( s_socket, (struct sockaddr *) &server_address, sizeof(server_address) );

   if ( binding < 0 )
   {
      fprintf( stderr, "Could not bind.\n" );
      exit( -3 );
   }
   
   /* backlog queue is 5 */
   listen( s_socket, 5 );
   
   client_addr_len = sizeof( client_address );
   
   new_socket = accept( s_socket, (struct sockaddr *) &client_address, &client_addr_len );
   
   if ( new_socket < 0 )
   {
      fprintf( stderr, "Could not accept\n" );
      exit( -4 );
   }

   clienthandle(new_socket);

   close( s_socket );

   return 0;
}

void clienthandle(int socket_id)
{
   char * message;
   char * results;
   char * received;

   results = (char *) malloc(sizeof(char) * BUFSZE);
   message = (char *) malloc(sizeof(char) * BUFSZE);
   received = (char *) malloc(sizeof(char) * BUFSZE);
   
   memset(results, '\0', BUFSZE);
   memset(message, '\0', BUFSZE);
   memset(received, '\0', BUFSZE);

   char * hello = "220 TrinkleFTP\n";
   char * goodbye = "221 Goodbye\n";
   char * pwd = "257 Current working directory is ";
   char * cd = "250 CWD Command successful, ";
   char * success = "200 Command successful.\n";
   char * fivehundred = "500 Syntax error, command unrecognized.\n";
   char * fivefifty = "550 Requested action not taken.\n";

   sendmessage(socket_id, hello);

   received = getcommand(socket_id);

   /* Handle commands */
   while(strncasecmp(received, "QUIT", 4) != 0 )
   {
      memset(message, '\0', BUFSZE);

      if ( strncasecmp(received, "NOOP", 4) == 0 )
      {
	 sendmessage(socket_id, success);
      }
      else if (strncasecmp(received, "PWD", 3) == 0 )
      {
	 if ( getcwd(results, BUFSZE) == NULL )
	    sendmessage(socket_id, fivehundred);
	 else
	 {
	    sprintf(message, "%s%s\n", pwd, results);
	    sendmessage(socket_id, message);
	 }
      }
      else if (strncasecmp(received, "CD", 2) == 0 )
      {
	 char delims[] = " ";
	 char *directory = NULL;
	 directory = strtok( received, delims );
	 /* now to get the directory */
	 directory = strtok( NULL, delims );
	 directory[strlen(directory) - 1] = '\0';
	 
	 if ( chdir(directory) != 0 )
	    sendmessage(socket_id, fivefifty);
	 else
	 {
	    sprintf(message, "%s%s\n", cd, directory);
	    sendmessage(socket_id, message);
	 }
      }
      else if (strncasecmp(received, "RETR", 4) == 0)
      {
	 char filename[BUFSZE];
	 char cmd[5];

	 memset(filename, '\0', BUFSZE);

	 sscanf(received, "%s %s\n", cmd, filename);

	 retr(socket_id, filename);
      }
      else if (strncasecmp(received, "STOR", 4) == 0)
      {
	 char filename[BUFSZE];
	 char cmd[5];

	 memset(filename, '\0', BUFSZE);
	 
	 sscanf(received, "%s %s\n", cmd, filename);

	 stor(socket_id, filename);
      }
      else if (strncasecmp(received, "NLST", 4) == 0)
      {
	 char filename[BUFSZE];
	 char cmd[5];

	 memset(filename, '\0', BUFSZE);
	 
	 sscanf(received, "%s %s\n", cmd, filename);

	 nlst(socket_id, filename);
      }

      received = getcommand(socket_id);
   }
  
   sendmessage(socket_id, goodbye);

   close( socket_id );

   free(results);
   free(message);
   free(received);

   return;
}

char * getcommand(int socket_id)
{
   /* Receives command from socket */
   int read_message = 0;

   char * message;
   message = (char *) malloc(sizeof(char) * BUFSZE);
   memset(message, '\0', BUFSZE);

   /* initial read */
   read_message = recv( socket_id, message, BUFSZE, 0 );
   if ( read_message < 0 )
   {
      fprintf( stderr, "Could not read from socket.\n");
      exit( -6 );
   }
   
   return message;
}

void sendmessage(int socket_id, char * message)
{
   /* Sends message over the wire */
   int read_write = 0;

   read_write = send( socket_id, message, strlen(message), 0 );

   if ( read_write < 0 )
   {
      fprintf( stderr, "Could not write to socket.\n");
      exit( -5 );
   }

   return;
}

int getmessage(int socket_id)
{
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

void retr(int socket_id, char * filename)
{
   /* Exectues RETR Command */
   char * okay = "200 Okay ";
   char * failed = "500 Failed to open ";
   char * endoffile = "@$ EOF";

   int codenum = 0;

   char * message;
   message = (char *)malloc(sizeof(char) * BUFSZE);
   memset( message, '\0', BUFSZE );

   FILE * ipf = NULL;
   ipf = fopen(filename, "r");

   if (ipf == NULL)
   {
      sprintf(message, "%s%s\n", failed, filename);
      sendmessage(socket_id, message);
   }
   else
   {
      memset(message, '\0', BUFSZE );
      sprintf(message, "%s%s\n", okay, filename);

      sendmessage(socket_id, message);

      memset( message, '\0', BUFSZE );

      codenum = getmessage(socket_id);

      if (codenum == 200)
      {

	 while ( fgets(message, BUFSZE, ipf) )
	 {
	    sendmessage(socket_id, message);
	    
	    memset( message, '\0', BUFSZE );
	    
	    usleep(10);
	 }

	 sendmessage(socket_id, endoffile);
      }

      fclose(ipf);
   }

   free(message);

   return;
}

void stor(int socket_id, char * filename)
{
   /* Executes STOR command */
   char * endoffile = "@$ EOF";

   char * fail = "500 Cancel Action.\n";
   char * okay = "200 Okay to send.\n";

   char * message;
   message = (char *)malloc(sizeof(char) * BUFSZE);

   if (message == NULL)
   {
      fprintf(stderr, "Not Enough Memory\n");
      exit(-4);
   }

   int read_message = 0;

   memset( message, '\0', BUFSZE );

   FILE * opf = NULL;

   memset(message, '\0', BUFSZE);

   opf = fopen(filename, "w");
   if (opf == NULL)
   {
      fprintf(stderr, "Failed to open %s\n", filename);
      strcpy(message, fail);
      
      /* I couldn't open file here */
      sendmessage(socket_id, message);
   }
   else
   {
      strcpy(message, okay);
      /* I opened file on my end */
      sendmessage(socket_id, message);
      
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
   
   free(message);
   
   return;
}

void nlst(int socket_id, char * filename)
{
   /* Executes NLST command */
   char * okay = "200 Directory Exists\n";
   char * fail = "500 Directory does not exist\n";
   char * endoffile = "@$ EOF";

   char * message;
   message = (char *)malloc(sizeof(char) * BUFSZE);
   memset(message, '\0', BUFSZE);

   DIR * directory;
   struct dirent * piece;

   directory = opendir(filename);

   if (directory == NULL)
   {
      sendmessage(socket_id, fail);
      free(message);
      return;
   }
   
   /* clearly not invalid */

   sendmessage(socket_id, okay);

   piece = readdir(directory);

   while( piece != NULL )
   {
      usleep(10);

      memset(message, '\0', BUFSZE);

      sprintf(message, "%s\n", piece->d_name);

      sendmessage(socket_id, message);

      piece = readdir(directory);
   }

   sendmessage(socket_id, endoffile);

   free(message);
   return;
}

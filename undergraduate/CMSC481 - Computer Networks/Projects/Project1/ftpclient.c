#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <unistd.h>

#define COMPORT  21
#define BUFSZE   4096

int  getmessage(int socket_id);
void commandprompt(int socket_id);
void sendmessage(int socket_id, char * message);

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
  
   do
   {
      printf("ftp>");
      fgets(input, BUFSZE, stdin);
      
      if (strncasecmp(input, "USER", 4) == 0)
      {
	 strncpy(input, "USER", 4);
	 sendmessage(socket_id, input);
	 code = getmessage(socket_id);
      }
      else if (strncasecmp(input, "PASS", 4) == 0)
      {
	 strncpy(input, "PASS", 4);
	 sendmessage(socket_id, input);
	 code = getmessage(socket_id);
      }
      else if (strncasecmp(input, "PWD", 3) == 0)
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
      else if (strncasecmp(input, "SYST", 4) == 0)
      {
	 strncpy(input, "SYST", 4);
	 sendmessage(socket_id, input);
	 code = getmessage(socket_id);
      }
      else if (strncasecmp(input, "QUIT", 4) == 0)
      {
	 strncpy(input, "QUIT", 4);
	 sendmessage(socket_id, input);
	 code = getmessage(socket_id);
      }
   }
   while(strncasecmp(input, "QUIT", 4) != 0);

   printf("\n");
   
   return;
}

void sendmessage(int socket_id, char * message)
{
   int read_write = 0;

   read_write = send( socket_id, message, strlen(message), 0 );

   if ( read_write < 0 )
   {
      fprintf( stderr, "Could not write to socket.\n");
      exit( -5 );
   }

   return;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <unistd.h>

#define BUFSZE 2048

int main(int argc, char * argv[])
{

   /* check commond-line arguments */
   if ( argc != 5 )
   {
      fprintf( stderr, "Thanks for using the Palindrome Client.\n");
      fprintf( stderr, "Written by Patrick Trinkle, tri1@umbc.edu\n\n");
      fprintf( stderr, "Proper usage: -h hostname -p port\n" );
      exit( -1 );
   }
   
   int i;
   int hostname;
   int port;
   
   /* i = 0 is program file */
   for ( i = 1; i < argc; i++ )
   {
      if ( strcmp( argv[i], "-h" ) == 0 )
      {
	 hostname = ( i + 1 );
	 i++;
      }
      else if ( strcmp( argv[i], "-p" ) == 0 )
      {
	 port = atoi( argv[i+1] );
	 i++;
      }
   }

   int s_socket;
   struct sockaddr_in server_address;
   struct hostent *   server;

   /* create socket */

   s_socket = socket( AF_INET, SOCK_STREAM, 0 );
   if ( s_socket < 0 )
   {
      fprintf( stderr,"Could not create socket.\n" );
      exit( -2 );
   }

   /* get server */

   server = gethostbyname( argv[hostname] );
   if ( server == NULL )
   {
      fprintf( stderr,"Host not found\n" );
      exit( -3 );
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
   connection = connect( s_socket, (struct sockaddr *)&server_address, sizeof(server_address) );
   if ( connection < 0 )
   {
      fprintf( stderr, "Could not connect.\n" );
      exit( -4 );
   }

   /* sending messaage */

   int read_write = 0;
   char message[BUFSZE];

   memset( message, '\0', BUFSZE );

   printf( "Input message\n" );
   fgets( message, BUFSZE, stdin );

   read_write = send( s_socket, message, strlen(message), 0 );

   if ( read_write < 0 )
   {
      fprintf( stderr, "Could not write to socket.\n");
      exit( -5 );
   }

   read_write = recv( s_socket, message, BUFSZE, 0 );

   if ( read_write < 0 )
   {
      fprintf( stderr, "Could not read from socket.\n");
      exit( -6 );
   }

   printf( "%s\n", message );

   close( s_socket );

   return 0;
}

/****************************************************
 ** File: proj1a.c
 ** Author: Patrick Trinkle
 ** Date: 2/16/2006
 ** Email : tri1@umbc.edu
 **
 ** This file contains all functions related to the
 ** functionality of the echo server.  I used my 
 ** palindrome checker from CMSC201.  Yay to keeping
 ** all working programs written!
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <pthread.h>
#include <unistd.h>

#define BUFSZE 2048

int StringPurge(char * string);
int IsPalindrome(char * temp, int numStart, int numEnd);
void * clientHandle(void * param);

int main(int argc, char * argv[])
{

   /* check commond-line arguments */
   if ( argc != 5 )
   {
      fprintf( stderr, "Thanks for using the Palindrome Server.\n");
      fprintf( stderr, "Written by Patrick Trinkle, tri1@umbc.edu\n\n");
      fprintf( stderr, "Proper usage: -p port -n maxnumconnections\n" );
      exit( -1 );
   }
   
   int n;
   int i;
   int port;
   
   /* i = 0 is program file */
   for ( i = 1; i < argc; i++ )
   {
      if ( strcmp( argv[i], "-p" ) == 0 )
      {
	 port = atoi( argv[i+1] );
	 i++;
      }
      if ( strcmp( argv[i], "-n") == 0 )
      {
	 n = atoi( argv[i+1] );
	 i++;
      }
   }

   /* create thread */
   pthread_t tid[n];
   pthread_attr_t attr;
   pthread_attr_init (&attr);

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

   printf( "Listening for %d connections on port: %d\n", n, port );

   int pthreadloop = 0;
   while( pthreadloop < n )
   {
   
      /* backlog queue is 5 */
      listen( s_socket, 5 );

      client_addr_len = sizeof( client_address );

      new_socket = accept( s_socket, (struct sockaddr *) &client_address, &client_addr_len );

      if ( new_socket < 0 )
      {
	 fprintf( stderr, "Could not accept\n" );
	 exit( -4 );
      }

      pthread_create( &tid[pthreadloop], &attr, &clientHandle, &new_socket );

      pthreadloop++;
   }

   int catching = 0;
   for ( catching = 0; catching < pthreadloop; catching++)
   {
      pthread_join(tid[catching], NULL);
   }

   close( s_socket );

   return 0;
}

int StringPurge(char * string)
{
   int i, j, strLen, isAlpha, numStart, numEnd, isPalindrome;
   char * temp;

   strLen = strlen(string);

   /* allocates the memory required for the strings */
   temp = (char *)malloc((strLen + 1) * sizeof(char));

   /* checks the memory availability */
   if (temp == NULL)
   {
      fprintf(stderr, "Not enough memory.\n");
      exit(-5);
   }

   /* copies the string into the temporary string */
   strcpy(temp, string);

   /* checks to see if it's a letter, if not then it removes and adjusts the string */
   for (i = 0; i < strLen; i++)
   {
      isAlpha = isalpha(temp[i]);

      if (isAlpha == 0)
      {
         for (j = i; j < strLen; j++)
         {
            temp[j] = temp[j+1];
         }
        
         strLen--;
         i--;
      }
   }

   numStart = 0;
   numEnd = strlen(temp) - 1;
   isPalindrome = 0;
   strLen = strlen(temp);

   /* converts all letters in string to be lower case */
   for (i = 0; i < strLen; i++)
   {
      temp[i] = tolower(temp[i]);
   }

   /* recursive palindrome function */
   isPalindrome = IsPalindrome(temp, numStart, numEnd);
 
   /* free memory allocated for purged string */
   free(temp);

   return isPalindrome;
}

int IsPalindrome(char * temp, int numStart, int numEnd)
{
   int isPalindrome;

   /* checks to see if the letters match */
   if ( numStart + 1 != numEnd && numStart != numEnd )
   {
      if ( temp[numStart] == temp[numEnd] )
      {
         IsPalindrome( temp, numStart+1, numEnd-1 );
      }
      else
      {
         isPalindrome = -1;
      }
   }

   return isPalindrome;
}

void * clientHandle(void * param)
{
   int socketid = *(int *)param;
   int read_write = 0;
   int isPalindrome = 0;

   const char isPal[18] = " is a palindrome.";
   const char isNot[22] = " is not a palindrome.";

   char message[BUFSZE];
   memset ( message, '\0', BUFSZE );

   read_write = recv( socketid, message, BUFSZE, 0 );

   if ( read_write < 0 )
   {
      fprintf( stderr, "Failed to receive.\n");
      exit( -5 );
   }

   char * newline = strchr( message, '\n' );
   if (newline != NULL)
      *newline = '\0';

   /* begin palindrome setup */
   isPalindrome = StringPurge(message);

   char * result;

   if ( isPalindrome == -1 )
   {
      result = strcat( message, isNot );
   }
   else
   {
      result = strcat( message, isPal );
   }

   read_write = send( socketid, result, BUFSZE, 0 );

   if ( read_write < 0 )
   {
      fprintf( stderr, "Could not write to socket.\n");
      exit( -6 );
   }

   close( socketid );

   pthread_exit(0);
}

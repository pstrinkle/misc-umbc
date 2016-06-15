Course: CMSC481
Date: 3/5/2006
Author: Patrick Trinkle
email: tri1@umbc.edu

FTP Client

file:ftpclient.c

To compile, run: `make`
To run: `./ftpclient ftpserveraddress`
   i.e. ./ftpclient ftp.gl.umbc.edu

Commands Implemented:
USER username
PASS password
PWD
SYST
NOOP
QUIT

FTP client written per RFC-959

---------------------------------------------------------

Echo Server

files: echo_client.c p_echo_server.c

To compile, run: `make`
To run: `./p_echo_server -p portnum -n maxconnectionshandled`
	`./echo_client -h hostaddrees -p port
   i.e. ./p_echo_server -p 2525 -n 3000
	./echo_client -h localhost -p 2525

   This will cause the server to list on port 2525, and run until it has handled 3000 clients.  When the client program is executed it will prompt for an input message.  Send to the server, and wait for a reply declaring whether or not the string sent was a palindrome or not.

   To test, choose an unused port over 1024.  To view ports in use, run: `netstat -an`.

   The Buffer size for this program is 2048.  This 2048 has to include either of the two following strings: 'is not a palindrome','is a palindrome'.


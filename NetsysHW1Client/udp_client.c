/*
 * udp_client.c
 *
 *  Created on: Sep 4, 2012
 *      Author: grebwerd
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>


#define MAXBUFSIZE 1000
int main(int argc, char *argv[])
{
   int sock, length, nbytes;
   struct sockaddr_in server, from;
   struct hostent *hp;
   char buffer[MAXBUFSIZE];

   //Make sure the user enters in the correct number of arguments
   if (argc != 3) {
	printf("Usage: <server> <port>\n");
	exit(1);
   }

   //create a IPv4 UDP socket
   sock = socket(AF_INET, SOCK_DGRAM, 0);


   //verify that we created a socket
   if (sock < 0) {
	printf("unable to create a socket \n");
	exit(1);
    }

   //make sure internet socket has the correct IP protocol: IPv4
   server.sin_family = AF_INET;

   //get IP of the server, in our example it is the local host 127.0.1.1
   hp = gethostbyname(argv[1]);

   //verify that we received a proper hostname
   if (hp==0){
	printf("Unable to resolve host address");
   }

   /*bcopy: copies memory regions of arbitrary length
	src is the hp->h_addr, dest is &server.sin_addr,
	and the length of memory to copy is hp->h_length)
   */

   bcopy((char *)hp->h_addr,
        (char *)&server.sin_addr,
         hp->h_length);

   /*resolve user's second entry as a port number using the function
    htons()
    htons(): converts a 16-bit quantity from host byte order to network byte order
 	atoi() converts string characters to integers.
   */
   server.sin_port = htons(atoi(argv[2]));


   length=sizeof(struct sockaddr_in);
   bzero(buffer,MAXBUFSIZE);
   nbytes=sendto(sock,"apple", MAXBUFSIZE,0,&server,length);
   if (nbytes < 0){
	printf("unable to send message\n");
   }
   nbytes = recvfrom(sock,buffer,MAXBUFSIZE,0,&from, &length); //works as &from and &server
   if (nbytes < 0) {
	printf("server didn't send ack \n");
   }
   printf("Got an ack: \n");
   printf("ack sent the message: %s\n", buffer);
}

/*
 * udp_client.c
 *
 *  Created on: Sep 4, 2012
 *      Author: grebwerd
 */


#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include "include/common.h"

/*==========================================
 * Function: main
 * Arguments: commandline arguments.
 * Purpose: entry point and socket code
 *=========================================*/
int main(int argc, char *argv[])
{
	struct sockaddr_in sAddr;
        int listensock;
        int newsock;
        char buffer[BUFFER_SIZE];
        int nchildren = PREFORKS;
        int result;
        int nread;
        int pid;
        int x;
        int val;
        int type = 0;
        int err;
	int i=0;	

       /* clean buffer */
        memset(buffer,0x00, sizeof(buffer));

	int port = GetIntConfigValue("HIPSTER:port");
	listensock = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);	

	val=1;
	result = setsockopt(listensock,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));
	if(result < 0)
        {
		perror("serrver");
		return -1;
	}	

	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(port);
	sAddr.sin_addr.s_addr = INADDR_ANY;	

	result = bind(listensock, (struct sockaddr *) &sAddr,sizeof(sAddr));		
	if(result < 0)
        {
		perror("server");	
		return -1;
	}

	result = listen(listensock,5);
	if(result < 0)
	{
		perror("server");
		return -1;
	}		

	for (x = 0; x < nchildren;x++)
	{
		if((pid = fork()) == 0)
		{
			while(1)
			{
				newsock = accept(listensock,NULL,NULL);
				printf("client connected to child process %i.\n",getpid());		
				
				nread = recv(newsock,buffer,sizeof(buffer),0);
				buffer[nread]= '\0';

				/* Forward connection here */
				
			       	close(newsock);
				printf("client disconnected from child process %i.\n",getpid()); 			
			}				
		}
	}

	wait(NULL);
	return 0;
}

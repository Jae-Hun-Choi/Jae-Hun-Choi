#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>


void ErrorHandler(char* message);
int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("Usage : %s <port>\n",argv[0]);
		ErrorHandler("arguments error\n");
	}
	int serv_sock=socket(AF_INET, SOCK_STREAM, 0);
	if(serv_sock ==-1)
	{
		ErrorHandler ("socket() error");
	}
	
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	int bflag = bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	if (bflag == -1)
	{
		ErrorHandler("bind() error");
	}

	int lflag = listen(serv_sock, 10);
	if (lflag == -1)
	{
		ErrorHandler("listen() error");
	}

	struct sockaddr client_addr;
	socklen_t client_addr_size = sizeof(client_addr);	
	int new_sock = accept(serv_sock,(struct sockaddr*)&client_addr, (socklen_t*) &client_addr_size);
	if (new_sock == -1)
	{
		ErrorHandler ("accept() error");
	}


	char buf[1024] = "Hello Socket!";
	write(new_sock, buf,sizeof(buf));
	
	close(new_sock);
	close(serv_sock);
	
	return 0;
}

void ErrorHandler(char* message)
{
	fputs(message,stderr);
	fputs("\n",stderr);
	exit(1);

}

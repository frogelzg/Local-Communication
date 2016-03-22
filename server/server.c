#include "../include/base.h"

#define PORT	5694
#define BACKLOG	10
#define BUFFSIZE	1024

int main(int argc, char *argv[])
{

	int ss,sc;
	int len;
	int ret;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	/*************** socket ********************/
	ss = socket(AF_INET, SOCK_STREAM, 0);
	if (ss < 0)
	{
		perror("ss socket error!");
		exit(1);
	}

	/************* initialization *************/
	len = sizeof(server_addr);
	memset(&server_addr, 0, len);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);
	
	/*************** bind *******************/
	ret = bind(ss, (const struct sockaddr *)&server_addr, len);
	if (ret < 0)
	{
		perror("bind error!");
		exit(1);
	}

	/*************** listen *******************/
	ret = listen(ss, BACKLOG);
	if (BACKLOG < 0)
	{
		perror("listen error!");
		exit(1);
	}
	
	/*************** accept *******************/
	socklen_t addrlen = sizeof(client_addr);
	for (;;)
	{
		sc = accept(ss , (struct sockaddr *)&client_addr, &addrlen);
		if (sc < 0)
		{
			perror("accept error this time!");
			continue;
		}
		else
		{
			printf("Server accept client: ip: %s , port: %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		}

		ssize_t size = 0;  
		char buffer[BUFFSIZE];  
		int num = 0;

		for(;;)  
		{  
		    	memset(buffer, 0, BUFFSIZE);  
				/*从fd中读取数据放到缓冲区buffer中*/  
				size = read(sc, buffer, BUFFSIZE); 
				if(size >  0)  
				{  
					printf("Received data: %s\n", buffer);
					//向服务器端写  
					ret = write(sc,buffer,strlen(buffer)+1); 
					if (ret < 0)
					{
						printf("Write failed! line: %\n", __LINE__);
						exit(1);
					}
  	
		     	    //等待读取到数据  
				    for(size = 0 ; size == 0 ; size = read(ss,buffer,BUFFSIZE) );  
  	
				    write(1,buffer,strlen(buffer)+1);   //向标准输出写  
				}  
				if ( num++ > 5)
					break;
    	}	

	}

	close(ss);
	close(sc);

	return 0;
}

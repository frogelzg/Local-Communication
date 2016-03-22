#include <stdio.h>  
#include <strings.h> 
#include <stdlib.h>
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <memory.h>  
#include <arpa/inet.h>  
#include <netinet/in.h>  
  
#define PORT    5694  
#define BUFFSIZE  1024  
#define IP		"192.168.1.102"

int main(int argc,char *argv[])  
{  
  
	int ss;
    struct sockaddr_in server_addr;  
    int ret;  

    /******************** socket() *********************/  
    ss= socket(AF_INET,SOCK_STREAM,0);  
    if(ss<0)  
    {  
        printf("client : create socket error\n");  
        exit(1);  
    }  
  
    /***************** initialization *******************/  
    //设置服务器地址结构，准备连接到服务器  
    memset(&server_addr,0,sizeof(server_addr));  
    server_addr.sin_family = AF_INET;  
    server_addr.sin_port = htons(PORT);  
    server_addr.sin_addr.s_addr = inet_addr(IP);  
  
    ret = connect(ss,(struct sockaddr *)&server_addr,sizeof(struct sockaddr));  
    if (ret == 0)  
    {   
        printf("client : connect to server\n");  
    }  
    else  
    {   
        printf("client : connect error\n");  
        exit(1);  
    }  

    //与服务器端进行通信  
    ssize_t size = 0;  
    char buffer[BUFFSIZE];  
  
    for(;;)  
	{  
		memset(buffer, '\0', BUFFSIZE);  
        /*从标准输入中读取数据放到缓冲区buffer中*/  
        size = read(0, buffer, BUFFSIZE);   // 0，被默认的分配到标准输入  1，标准输出  2，error  
        if(size >  0)  
 		{  
            //当向服务器发送 “quit” 命令时，服务器首先断开连
            write(ss,buffer,strlen(buffer)+1);   //向服务器端写  

            //等待读取到数据  
            for(size = 0 ; size == 0 ; size = read(ss,buffer,BUFFSIZE) );  
  
            write(1,buffer,strlen(buffer)+1);   //向标准输出写  
        }
	}	 
    close(ss);  

	return 0;
}  

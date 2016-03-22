#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>	/* for function: inet_ntoa */

/* define the file whoch archive on-line customer */
#define ONLINE_FILE "../database/base.h"

/*
 * self-define struct 
 * include ip address and port
 * for each customer
 */
typedef struct addr_s
{
	unsigned char ip[15];
	unsigned int  port;
}addr_s __attribute__((aligned(4))) ;

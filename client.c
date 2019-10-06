#include "myhead.h"
char ip_addr[16] = {};
int port;
int main(int argc,char *argv[])
{
    int ret;
    FILE *fp;
    int socket_fp;
    int send_message[100];
    struct sockaddr_in sock_addr;

    if(argc != 4)
    {
        printf("usage:%s <ipaddress> <port> <file name>\n",argv[0]);
        exit(1);
    }

    fp = fopen(argv[3],"r");
    if(fp == NULL)
    {
        perror("fopen");
    }

    socket_fp = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fp == -1)
    {
        perror("socket");
        exit(1);
    }

    sock_addr.sin_addr.s_addr = inet_addr(argv[1]); 
    sock_addr.sin_port = htons(atoi(argv[2]));
    sock_addr.sin_family = AF_INET;

    ret = connect(socket_fp, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
    if(ret == -1)
    {
        perror("connect");
        exit(1);
    }

    while(1)
    {
        memset(send_message, 0, sizeof(send_message));
        ret = fread(send_message, 1, 1, fp);
        if(ret == 0)
            break;
        ret = send(socket_fp, send_message, 1, 0);
        if(ret == -1)
            break;
    }
    close(socket_fp);
    return 0;
}
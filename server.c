#include "myhead.h"
char ip_addr[16] = {};
int port;
int main(int argc,char *argv[])
{
    int ret;
    int socket_fp;
    int fd;
    int recv_message[100];
    struct sockaddr_in sock_addr;

    if(argc != 3)
    {
        printf("usage:%s <ipaddress> <port>\n",argv[0]);
        exit(1);
    }

    fd = open("recv_file",O_WRONLY | O_CREAT);

    socket_fp = socket(AF_INET,SOCK_STREAM,0);
    if(socket_fp == -1)
    {
        perror("socket");
        exit(1);
    }

    sock_addr.sin_addr.s_addr = (inet_addr(argv[1])); 
    sock_addr.sin_port = htons(atoi(argv[2]));
    sock_addr.sin_family = AF_INET;
    ret = bind(socket_fp,(struct sockaddr *)&sock_addr,sizeof(sock_addr));
    if(ret == -1)
    {
        perror("bind");
        exit(1);
    }

    ret = listen(socket_fp,5);
    if(ret == -1)
    {
        perror("listen");
        exit(1);
    }

    struct sockaddr_in client;
    socklen_t sock_len = sizeof(client);
    int newfd;
    newfd = accept(socket_fp,(struct sockaddr *)&client,&sock_len);
    if(newfd == -1)
    {
        perror("accept");
        exit(1);
    }

    while(1)
    {
        memset(recv_message,0,sizeof(recv_message));
        ret = recv(newfd, recv_message, sizeof(recv_message), 0);
        if(ret < 0)
        {
            perror("recv");
        }
        else if(ret == 0)
            break;
        write(fd,recv_message,ret);
    }
    close(socket_fp);
    close(newfd);
    return 0;
}
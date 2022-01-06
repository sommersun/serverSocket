#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <thread>
#include <iostream>
#define PORT 7000
#define QUEUE 20//连接请求队列
int conn;
void thread_task()
{
}
 
int main()
{
   
    printf("%d\n",SOCK_STREAM);
    int ss = socket(AF_INET, SOCK_STREAM, 0);
    //printf("%d\n",ss);
    struct sockaddr_in server_sockaddr;
  
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);

    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);　
    if(bind(ss, (struct sockaddr* ) &server_sockaddr, sizeof(server_sockaddr))==-1)
    {
        perror("bind");
        exit(1);
    }
    if(listen(ss, QUEUE) == -1)
    {
        perror("listen");
        exit(1);
    }
 
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
   
    conn = accept(ss, (struct sockaddr*)&client_addr, &length);
   
    if( conn < 0 )
    {
        perror("connect");
        exit(1);
    }
 
    char buffer[1024];

    while(1)
    {

 
        memset(buffer, 0 ,sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer), 0);

        if(strcmp(buffer, "exit\n") == 0)
        {
            break;
        }
        printf("%s", buffer);
       
        send(conn, buffer, len , 0);
    }
    close(conn);
    close(ss);
    return 0;
}

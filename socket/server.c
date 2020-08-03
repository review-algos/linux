/*
 * reference: https://www.cnblogs.com/wangcq/p/3520400.html
 */

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int socket_fd;

void socket_init()
{
    int ret = socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (ret < 0)
    {
        perror("create socket failed!");
        exit(-1);
    }
}

void socket_close()
{
    close(socket_fd);
}

int main(int argc, char **argv)
{
    short port = 4096;
    int client_sockfd;
    char ip[32] = "127.0.0.1";
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    // Host to Network Short, reference: https://blog.csdn.net/zhuguorong11/article/details/52300680
    // https://blog.csdn.net/z_ryan/article/details/79134980
    addr.sin_port = htons(port);

    // bind socket and address 
    int ret = bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr));

    if (ret < 0)
    {
        perror("bind address failed!");
        exit(-1);
    }

    listen(socket_fd, 100);

    while (1)
    {
        struct sockaddr_in client_address;
        int client_len = sizeof(client_address);

        client_sockfd = accept(socket_fd, (struct sockaddr*)&client_address, (socklen_t *)&client_len); 
        if (client_sockfd < 0)
        {
            perror("connection error!");
        }
        else
        {            
          int keepAlive = 1;
          setsockopt(socket_fd, SOL_SOCKET, SO_KEEPALIVE, (void*)&keepAlive, sizeof(keepAlive));
          int keepIdle = 5;
          int keepInterval = 5;
          int keepCount = 5;
          setsockopt(socket_fd, SOL_TCP, TCP_KEEPIDLE, (void *)&keepIdle, sizeof(keepIdle));
          setsockopt(socket_fd, SOL_TCP,TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
          setsockopt(socket_fd,SOL_TCP, TCP_KEEPCNT, (void *)&keepCount, sizeof(keepCount));
        }


    }

    return 0;
}

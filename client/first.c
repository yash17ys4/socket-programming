#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#define PORT 8080

int main(int argc, char const * argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char * hello = "hello from client";
    char buffer[1024] = {0};
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    //convert IPv4 and IPv6 addresses from text to binary
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("Invalid address/ address not supported\n");
        return -1;
    }

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("connection failed\n");
        return -1;
    }

    send(sock, hello, strlen(hello), 0);
    printf("hello message sent\n");
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);

    close(sock);
    return 0;
}
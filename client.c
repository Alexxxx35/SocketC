// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char const *argv[])
{
    //create socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // char *hello = "Hello from client";
    // char buffer[1024] = {0};
    if (network_socket <= 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    //memset(&serv_addr, '0', sizeof(serv_addr));

    //specify address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);       //htons converts int to network representation
    server_address.sin_addr.s_addr = INADDR_ANY; //shortcut for 0.0.0.0 connection

    // Convert IPv4 and IPv6 addresses from text to binary form
    // if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    // {
    //     printf("\nInvalid address/ Address not supported \n");
    //     return -1;
    // }

    //binder  //attaching socket to 8080 port  //return int
    int connection_status = connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    //error checking
    if (connection_status < 0)
    {
        printf("\n CLIENT: Binder/Connection to the remote socket failed \n");
        return -1;
    }

    //define response and keep it
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);
    printf("The server sent:%s", server_response);

    // close the socket
    close(network_socket);

    // send(network_socket, hello, strlen(hello), 0);
    // printf("Hello message sent\n");
    // read(network_socket, buffer, 1024);
    // printf("%s\n", buffer);
    return 0;
}
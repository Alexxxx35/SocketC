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

    //define custom message
    // char *hello = "Hello from client";
    // char buffer[1024] = {0};
    if (network_socket <= 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    //specify address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT); //htons converts int to network representation
    //server_address.sin_addr.s_addr = INADDR_ANY; //shortcut for 0.0.0.0 connection instead of specify IP
    char address = "216.58.213.142";
    inet_aton(&address, &server_address.sin_addr.s_addr); //convert string address to network representation and store it into the struct

    //binder  //connect with socket to server listening on 8080 port  //return int
    int connection_status = connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    //error checking
    if (connection_status < 0)
    {
        printf("\n CLIENT: Binder/Connection to the network socket failed \n");
        return -1;
    }

    //define a request to send
    char request[] = "GET / HTTP/2.0\r\n\r\n";
    send(network_socket, request, sizeof(request), 0);

    //define response and keep it
    char server_response[4096];
    recv(network_socket, &server_response, sizeof(server_response), 0);
    printf("The server sent:%s\n", server_response);

    // close the socket
    close(network_socket);

    return 0;
}
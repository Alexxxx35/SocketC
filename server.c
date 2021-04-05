// Server side C program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
int main(int argc, char const *argv[])
{
    //define message
    char server_message[256] = "you have reached the server";

    //define server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket <= 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    // int server_fd, new_socket;
    // long valread;
    // int addrlen = sizeof(server_address);
    //     char *hello = "Hello from server";

    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);       //htons converts int to network representation
    server_address.sin_addr.s_addr = INADDR_ANY; //shortcut for 0.0.0.0 connection

    //memset(server_address.sin_zero, '\0', sizeof server_address.sin_zero);

    //binder  //attaching socket to 8080 port  //return int
    int connection_status = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    //error checking
    if (connection_status < 0)
    {
        printf("\n SERVER: Binder/Connection to the remote socket failed \n");
        return -1;
    }
    // Listening for other connections, the integer determines number of connections waiting
    int listener = listen(server_socket, 3);
    //error checking
    if (listener < 0)
    {
        printf("\n SERVER: Error in listening for other connections \n");
        return -1;
    }

    //define client socket (which is the result of new connection) to keep it and manipulate it
    //we can send & receive data from both sides
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);
     if (client_socket < 0)
    {
        printf("\n SERVER: Error in accepting new connections \n");
        return -1;
    }
    
    //send a message
    int sender;
    sender = send(client_socket, server_message, sizeof(server_message), 0);
     if (sender < 0)
    {
        printf("\n SERVER: Error in sending data to new connections \n");
        return -1;
    }

    //close the socket
    close(server_socket);

    // while (1)
    // {
    //     printf("\n+++++++ Waiting for new connection ++++++++\n\n");
    //     if ((new_socket = accept(server_fd, (struct sockaddr *)&server_address, (socklen_t *)&addrlen)) < 0)
    //     {
    //         perror("In accept");
    //         exit(EXIT_FAILURE);
    //     }

    //     char buffer[30000] = {0};
    //     valread = read(new_socket, buffer, 30000);
    //     printf("%s\n", buffer);
    //     write(new_socket, hello, strlen(hello));
    //     printf("------------------Hello message sent-------------------\n");
    //     close(new_socket);
    // }
    return 0;
}
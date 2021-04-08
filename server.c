#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
int main(int argc, char const *argv[])
{   //define file with html data to communicate (or json data)
    //if not stuck in stream when opening url
    FILE *html_data;
    html_data = fopen("index.html", "r");

    //reading elements until file ends and save content to char buffer
    char response_data[1024];
    fgets(response_data, 1024, html_data);

    //define http response with status code => header+data
    char http_header[2048] = "HTTP/2.0 200 OK\r\n\n";
    strcat(http_header, response_data);

    //define custom message for simple terminal communication
    char server_message[256] = "you have reached the server";

    //define server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket <= 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);       //htons converts int to network representation
    server_address.sin_addr.s_addr = INADDR_ANY; //shortcut for 0.0.0.0 connection

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
    //while loop used to keep the listening process open
    int client_socket;
    while (1)
    {
        client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0)
        {
            printf("\n SERVER: Error in accepting new connections \n");
            return -1;
        }
        //send http request header (contains the elements that describe the request itself)
        send(client_socket, http_header, sizeof(http_header), 0);
    }

    //send a simple custom message
    // int sender;
    // sender = send(client_socket, server_message, sizeof(server_message), 0);
    //  if (sender < 0)
    // {
    //     printf("\n SERVER: Error in sending data to new connections \n");
    //     return -1;
    // }

    //close the socket
    close(server_socket);

    return 0;
}
/*
Include dependencies:
- stdio.h for standard input/output functions.
- stdlib.h for memory allocation and process control.
- string.h for string manipulation functions.
- winsock2.h and ws2tcpip.h for network management, such as creating sockets (connection points in the network).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Main function starts
int main(){
        // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Failed to initialize Winsock.\n");
        return 1; // Exit if Winsock initialization fails
    }
    /*
    Declare variables and structures for the code:
    - char* ip: a string that stores the IP address as a string.
    - int port: stores the port number for connection as an integer value.

    - struct sockaddr_in: a structure defined in winsock2.h that contains information about the server's address (IP and port).
    - server_addr: used to get the server's IP and port for binding.
    - client_addr: will store details of the client that connects to the server after the bind is successful.

    - socklen_t: a typedef defined in winsock2.h for socket address length; addr_size will store the size of the client_addr structure.

    - char buffer[1204]: an array to store data for communication between the server and client (e.g., "Hello", "Hi", etc.).
    */

    char *ip = "127.0.0.1";
    int port = 5566;

    int server_sock, client_sock;

    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1204];
    int n;

    /*
    Creating a socket (connection point) for the server.
    The socket() function returns an integer value representing the socket.
    It takes three parameters: the address family (AF_INET for IPv4), the socket type (SOCK_STREAM for TCP), and the protocol (0 for default).
    If successful, it returns a value >= 0; otherwise, it returns a negative value.
    */

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket error!!");
        exit(1);
    }
    printf("Socket Created!!\n");

    /*
    Clearing the server_addr structure to remove any garbage values.
    memset initializes memory starting from the location of server_addr to zero.
    sizeof() is used to determine the size of the structure to ensure we clear all of it.
    After clearing, we assign the IP type in sin_family, the port in sin_port,
    and convert the IP string into a binary format with inet_addr() for sin_addr.s_addr.
    */

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port); // Use htons to ensure proper byte order
    server_addr.sin_addr.s_addr = inet_addr(ip);

    /*
    Binding the socket means telling the operating system to associate this specific socket with the specified IP and port.
    The bind() function takes three parameters: the socket identifier (server_sock),
    a pointer to the sockaddr structure (cast to (struct sockaddr*)&server_addr),
    and the size of the structure (sizeof(server_addr)).
    This allows the OS to know what type of connection the socket will handle.
    */

    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (n < 0) {
        perror("Bind Error!!");
        exit(1);
    }
    printf("Bind to the port number: %d\n", port);

    // Start listening for incoming connections. The backlog parameter specifies the maximum number of queued connections.
    listen(server_sock, 5);
    printf("Listening...\n");

    /*
    The while(1) loop keeps the server running and listening for client connections.
    The accept() function waits for an incoming connection on server_sock and, when a client connects,
    it returns a new socket (client_sock) for communication with that specific client.
    The function also populates client_addr with the client's address information and requires a pointer to addr_size to get the size of the client_addr.
    */

    while (1) {
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        printf("Client Connected!!\n");

        memset(buffer , 0 , sizeof(buffer));// cleanig the buffer variable
        recv(client_sock , buffer , sizeof(buffer), 0);
        printf("Client: %s\n",buffer);

        memset(buffer , 0 , sizeof(buffer));
        strcpy(buffer, "Hello, This is from the server..!");
        printf("Server : %s\n",buffer);
        send(client_sock, buffer , sizeof(buffer),0);

        closesocket(client_sock);
        printf("Client Disconnected...!\n\n");


    }

    return 0;
}

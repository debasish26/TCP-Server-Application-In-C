#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int main() {

    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Failed to initialize Winsock.\n");
        return 1; // Exit if Winsock initialization fails
    };


    char *ip = "127.0.0.1"; // IP address of the server (localhost)
    int port = 5566; // Port number to connect to the server
    int sock; // Variable to hold the socket descriptor

    struct sockaddr_in addr; // Structure to hold server address information
    socklen_t addr_size; // Variable to store the size of the address structure
    char buffer[1204]; // Buffer for sending/receiving data
    int n; // Variable for return values from functions

    /*
    Creating a socket (connection point) for the client.
    The socket() function returns an integer value representing the socket.
    It takes three parameters: the address family (AF_INET for IPv4),
    the socket type (SOCK_STREAM for TCP), and the protocol (0 for default).
    If successful, it returns a value >= 0; otherwise, it returns a negative value.
    */

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket error!!");
        exit(1);
    }
    printf("Socket Created!!\n");

    /*
    Clearing the addr structure to remove any garbage values.
    memset initializes memory starting from the location of addr to zero.
    sizeof() is used to determine the size of the structure to ensure we clear all of it.
    After clearing, we assign the IP type in sin_family, the port in sin_port,
    and convert the IP string into a binary format with inet_addr() for sin_addr.s_addr.
    */

    memset(&addr, '\0', sizeof(addr)); // Clear the addr structure
    addr.sin_family = AF_INET; // Set the address family to IPv4
    addr.sin_port = htons(port); // Use htons to ensure proper byte order for the port
    addr.sin_addr.s_addr = inet_addr(ip); // Convert IP address from string to binary format

    /*
    Connecting to the server.
    The connect() function attempts to establish a connection to the specified server address.
    It takes three parameters: the socket descriptor (sock), a pointer to the sockaddr structure (cast to (struct sockaddr*)&addr),
    and the size of the sockaddr structure (sizeof(addr)).
    If the connection is successful, the function returns 0; otherwise, it returns a negative value.
    */

    connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    printf("Connected to the server..!\n");

    memset(buffer , 0 , sizeof(buffer));
    strcpy(buffer,"HELLO, THIS IS CLIENT...!");
    printf("Client: %s\n", buffer);
    send(sock,buffer,strlen(buffer),0);

    memset(buffer , 0 , sizeof(buffer));
    recv(sock , buffer ,sizeof(buffer),0);
    printf("Server : %s",buffer);



    return 0;
}

# TCP Server Application in C

This project is a simple TCP server-client application written in C, demonstrating socket programming for client-server communication.

## Overview

The TCP Server Application allows a client to connect to the server, send messages, and receive responses. It showcases the basic principles of network communication using sockets, including socket creation, binding, listening, and accepting connections.

## Features

- **TCP Socket Communication**: Establishes a TCP connection between the server and client.
- **Message Exchange**: Enables sending and receiving messages between the client and server.
- **Cross-Platform Compatibility**: Works on Windows using the Winsock library.

## Prerequisites

To compile and run this project, you need:

- A C compiler (e.g., GCC)
- Winsock library (included with most C compilers on Windows)

## Getting Started

### Clone the Repository

```
git clone https://github.com/yourusername/TCP-Server-Application-In-C.git
cd TCP-Server-Application-In-C
```

## Compile the Code
Navigate to the directory containing the server and client code and use the following commands to compile:

For the server:
```
gcc server.c -o server -lws2_32
```

For the client:
```
gcc client.c -o client -lws2_32
```
## Running the Application
  1. Start the Server: Open a terminal and run the server executable:
```
./server.exe
```
  2. Start the Client: Open another terminal and run the client executable:
```
./client.exe
```
## Communication:

The client can send messages to the server.

The server will respond back, demonstrating bidirectional communication.

## Code Structure

  1. server.c: The code for the TCP server, which listens for incoming client connections.
     
  2. client.c: The code for the TCP client, which connects to the server and sends messages.

## Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request.

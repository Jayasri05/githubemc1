#include <stdio.h>
#include <winsock2.h>

int main() {
    WSADATA wsaData;
    SOCKET listenSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char buffer[1024];
    
    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    // Create a socket
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Setup server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345); // Port number
    
    // Bind the socket
    bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    // Listen for incoming connections
    listen(listenSocket, 5);
    
    printf("Server listening on port 12345...\n");
    
    // Accept a client connection
    clientSocket = accept(listenSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    
    printf("Client connected.\n");
    
    // Receive data from client
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("Received from client: %s\n", buffer);
    
    // Send response to client
    send(clientSocket, "Hello from server!", sizeof("Hello from server!"), 0);
    
    // Close the client socket
    closesocket(clientSocket);
    
    // Close the listening socket
    closesocket(listenSocket);
    
    // Cleanup Winsock
    WSACleanup();
    
    return 0;
}
#include <stdio.h>
#include <winsock2.h>

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    
    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Setup server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP
    serverAddr.sin_port = htons(12345); // Server port
    
    // Connect to the server
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    printf("Connected to server.\n");
    
    // Send data to server
    send(clientSocket, "Hello from client!", sizeof("Hello from client!"), 0);
    
    // Receive response from server
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("Received from server: %s\n", buffer);
    
    // Close the socket
    closesocket(clientSocket);
    
    // Cleanup Winsock
    WSACleanup();
    
    return 0;
}
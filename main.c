#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 2525
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    
    // Send greeting
    send(client_socket, "220 Simple Mail Server\r\n", 24, 0);

    // Receive commands from the client
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        recv(client_socket, buffer, BUFFER_SIZE, 0);

        // Print client command
        printf("Client: %s", buffer);

        // Simple responses to common SMTP commands
        if (strncmp(buffer, "HELO", 4) == 0) {
            send(client_socket, "250 Hello\r\n", 11, 0);
        } else if (strncmp(buffer, "MAIL FROM:", 10) == 0) {
            send(client_socket, "250 OK\r\n", 8, 0);
        } else if (strncmp(buffer, "RCPT TO:", 8) == 0) {
            send(client_socket, "250 OK\r\n", 8, 0);
        } else if (strncmp(buffer, "DATA", 4) == 0) {
            send(client_socket, "354 End data with <CR><LF>.<CR><LF>\r\n", 36, 0);
        } else if (strncmp(buffer, ".", 1) == 0) {
            send(client_socket, "250 Message accepted\r\n", 23, 0);
            break; // End communication
        } else if (strncmp(buffer, "QUIT", 4) == 0) {
            send(client_socket, "221 Bye\r\n", 9, 0);
            break; // Close connection
        } else {
            send(client_socket, "500 Command not recognized\r\n", 28, 0);
        }
    }

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        return 1;
    }
    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to the port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // Listen for connections
    if (listen(server_socket, 10) < 0) {
        perror("Listen failed");
        return 1;
    }

    printf("SMTP server listening on port %d...\n", PORT);

    // Accept and handle clients
    while (1) {
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }
        printf("Client connected.\n");

        // Handle client communication
        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}

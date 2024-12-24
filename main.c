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
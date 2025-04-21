#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main(int argc, char* argv[]) {
    // filling address struct
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    // socket declaration (socket descriptor)
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // connecting socket
    if (server_socket < 0) {
        perror("Failed to connect socket...");
        exit(EXIT_FAILURE);
    }

    // binding socket
    if (bind(server_socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Failed to bind socket...");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // listening socket
    if (listen(server_socket, 5) < 0) {
        perror("Failed to listen socket...");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    // client socket acception
    int client_socket = accept(server_socket, NULL, NULL);

    // accepting connection
    if (client_socket < 0) {
        perror("Failed to accept connection...");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Client connected!\n");

    // receiving data
    char buffer[256] = {};
    int valread = read(client_socket, buffer, 255);
    if (valread < 0) {
        perror("Failed to recive data from client...");
    } else printf("Received student info: %s\n", buffer);

    // closing sockets
    close(client_socket);
    close(server_socket);

    return EXIT_SUCCESS;
}
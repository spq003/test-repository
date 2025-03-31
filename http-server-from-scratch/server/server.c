#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

/* https://ri3n.tistory.com/92#TCP%--%EA%B-%AC%ED%--%--
*/

int main() {
    int err_handle;
    SOCKET server_socket, client_socket;
    long valread;
    struct sockaddr_in address, client_addr;
    char hello[] = "Hello from the server";

    WSADATA wsadata;
    err_handle = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (err_handle != 0) {
        perror("failed to init WSA");
        exit(EXIT_FAILURE);
    }

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);

    err_handle = bind(server_socket, (struct sockaddr*)&address, sizeof(address));
    if (err_handle < 0) {
        perror("In bind");
        exit(EXIT_FAILURE);
    }

    err_handle = listen(server_socket, 10);
    if (err_handle < 0) {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("\n++++++++ Waiting for new connection ++++++++\n\n");

        int client_addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
        if (client_socket == INVALID_SOCKET) {
            perror("In accept");
            continue;
        }

        char* client_ip = inet_ntoa(client_addr.sin_addr);
        int client_port = ntohs(client_addr.sin_port);
        printf("new client connected: %s:%d\n", client_ip, client_port);

        char buffer[1024] = { 0 };
        valread = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (valread > 0) {
            buffer[valread] = '\0';
            printf("Received: %s\n", buffer);
        }
        else {
            perror("In recv");
        }

        send(client_socket, hello, strlen(hello), 0);
        printf("-------- Hello message sent --------\n");

        closesocket(client_socket);
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}

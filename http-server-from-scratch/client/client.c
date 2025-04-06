#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib") //winsock2 라이브러리 링킹

#define PORT 8080
#define IP "127.0.0.1"

void clear(SOCKET sock);

int main() {
	int err_handle;
	WSADATA wsadata;
	SOCKET server_socket;
	struct sockaddr_in server_address;
	char recv_msg[1024] = { 0, };

	printf("init socket ...\n");

	err_handle = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (err_handle != NO_ERROR) {
		perror("failed to init WSA");
		exit(EXIT_FAILURE);
	}

	server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (server_socket == INVALID_SOCKET) {
		perror("In socket");
		clear(server_socket);
		exit(EXIT_FAILURE);
	}

	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	//server_address.sin_addr.s_addr = inet_addr(IP); //inet_addr(ip)비권장
	err_handle = inet_pton(AF_INET, IP, &(server_address.sin_addr)); //inet_pton 사용
	if (err_handle != 1) {
		perror("in inet addr");
		clear(server_socket);
		exit(EXIT_FAILURE);
	}

	err_handle = connect(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
	if (err_handle == SOCKET_ERROR) {
		perror("In socket");
		clear(server_socket);
		exit(EXIT_FAILURE);
	}
	printf("+++ connected to server +++\n");

	char buf[] = "this is client message";
	err_handle = send(server_socket, buf, strlen(buf), 0);
	if (err_handle == SOCKET_ERROR) {
		perror("in send");
		clear(server_socket);
		exit(EXIT_FAILURE);
	}
	printf("send msg result: %d\n", err_handle);

	err_handle = recv(server_socket, recv_msg, sizeof(recv_msg) - 1, 0);
	if (err_handle > 0) {
		printf("byte recived: %d\n", err_handle);
		printf("recived: %s\n", recv_msg);
	}
	else if (err_handle == 0)
		printf("connection closed\n");
	else
		printf("recv failed: %d\n", WSAGetLastError());

	clear(server_socket);
	return 0;
}

void clear(SOCKET sock) {
	closesocket(sock);
	WSACleanup();
}
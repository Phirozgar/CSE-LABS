#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int sockfd;

void *receive_handler(void *arg) {
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while(1) {
        bytes_read = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if(bytes_read <= 0) {
            printf("Connection closed by server.\n");
            exit(EXIT_FAILURE);
        }
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
        fflush(stdout);
    }
}

int main() {
    struct sockaddr_in server_addr;
    pthread_t recv_thread;
    char message[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("172.16.48.149");

    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    // Create thread to receive messages
    if(pthread_create(&recv_thread, NULL, receive_handler, NULL) != 0) {
        perror("pthread_create failed");
        exit(EXIT_FAILURE);
    }

    // Main thread: read user input and send to server
    while(1) {
        if(fgets(message, sizeof(message), stdin) != NULL) {
            if(send(sockfd, message, strlen(message), 0) < 0) {
                perror("send failed");
                break;
            }
        }
    }

    close(sockfd);
    return 0;
}


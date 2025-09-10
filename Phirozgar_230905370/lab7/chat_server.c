#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024

// Array of client sockets and GLOBAL VARIABLES
int clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

// Add client to clients array
void add_client(int client_sock) {
    pthread_mutex_lock(&clients_mutex);
    clients[client_count++] = client_sock;
    pthread_mutex_unlock(&clients_mutex);
}

// Remove client from clients array
void remove_client(int client_sock) {
    pthread_mutex_lock(&clients_mutex);
    for(int i = 0; i < client_count; ++i) {
        if(clients[i] == client_sock) {
            for(int j = i; j < client_count - 1; ++j) {
                clients[j] = clients[j+1];
            }
            client_count--;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

// Broadcast message to all clients except sender
void broadcast_message(char *message, int sender_sock) {
    pthread_mutex_lock(&clients_mutex);
    for(int i = 0; i < client_count; ++i) {
        int client_sock = clients[i];
        if(client_sock != sender_sock) {
            if(send(client_sock, message, strlen(message), 0) < 0) {
                perror("send");
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg) {
    int client_sock = *(int *)arg;
    free(arg);

    char buffer[BUFFER_SIZE];
    int bytes_read;

    while((bytes_read = recv(client_sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';
        printf("Received: %s", buffer);
        broadcast_message(buffer, client_sock);
    }

    if(bytes_read == 0) {
        printf("Client disconnected.\n");
    } else if(bytes_read == -1) {
        perror("recv");
    }

    close(client_sock);
    remove_client(client_sock);
    pthread_exit(NULL);
}

int main() {
    int server_sock, *new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sock == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Allow address reuse
    int opt = 1;
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if(bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if(listen(server_sock, 10) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while(1) {
        int client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len);
        if(client_sock < 0) {
            perror("accept failed");
            continue;
        }

        printf("New client connected.\n");

        add_client(client_sock);

        pthread_t tid;
        new_sock = malloc(sizeof(int));
        *new_sock = client_sock;

        if(pthread_create(&tid, NULL, handle_client, (void *)new_sock) != 0) {
            perror("pthread_create");
            free(new_sock);
        }

        pthread_detach(tid);  // Automatically reclaim thread resources when done
    }

    close(server_sock);
    return 0;
}


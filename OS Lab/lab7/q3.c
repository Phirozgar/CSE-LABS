#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*)0, 0);

    while (1) {
        printf("Enter your message: ");
        fgets(str, 100, stdin);
        str[strcspn(str, "\n")] = '\0';
        if (strcmp(str, "exit") == 0) break;
        while (strlen(str) > 0) sleep(1); // Wait for Display to clear
    }

    shmdt(str);
    return 0;
}




#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*)0, 0);

    while (1) {
        if (strlen(str) > 0) {
            printf("Display: %s\n", str);
            if (strcmp(str, "exit") == 0) break;
            str[0] = '\0'; // Clear message
        }
        sleep(1);
    }

    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}


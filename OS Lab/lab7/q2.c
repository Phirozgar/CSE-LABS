#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*)0, 0);

    if (fork() == 0) {
        // Child process
        sleep(1);
        char ch = str[0];
        ch = (ch == 'z') ? 'a' : ch + 1;
        str[0] = ch;
    } else {
        // Parent process
        char input;
        printf("Parent: Enter an alphabet: ");
        scanf(" %c", &input);
        str[0] = input;

        sleep(2);
        printf("Parent: Child replied with '%c'\n", str[0]);
        shmdt(str);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}


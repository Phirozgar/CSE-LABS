#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int isPalindrome(int n) {
    int rev = 0, temp = n;
    while (n > 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return temp == rev;
}

int main() {
    key_t key;
    int msgid;

    // Generate unique key
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    if (fork() == 0) {
        // Process A: Sender
        printf("Enter a number: ");
        int num;
        scanf("%d", &num);
        sprintf(message.msg_text, "%d", num);
        message.msg_type = 1;
        msgsnd(msgid, &message, sizeof(message), 0);
        printf("Process A: Sent number %d\n", num);
    } else {
        // Process B: Receiver
        sleep(1);
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        int num = atoi(message.msg_text);
        if (isPalindrome(num))
            printf("Process B: %d is a Palindrome.\n", num);
        else
            printf("Process B: %d is NOT a Palindrome.\n", num);

        msgctl(msgid, IPC_RMID, NULL); // delete queue
    }
    return 0;
}


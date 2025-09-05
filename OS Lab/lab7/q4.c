#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

char checkWinner(char *board) {
    int winCombos[8][3] = {
        {0,1,2},{3,4,5},{6,7,8}, // rows
        {0,3,6},{1,4,7},{2,5,8}, // cols
        {0,4,8},{2,4,6}          // diagonals
    };
    for (int i=0;i<8;i++) {
        if (board[winCombos[i][0]] != '-' &&
            board[winCombos[i][0]] == board[winCombos[i][1]] &&
            board[winCombos[i][1]] == board[winCombos[i][2]]) {
            return board[winCombos[i][0]];
        }
    }
    return '-';
}

void printBoard(char *board) {
    printf("\n");
    for (int i=0;i<9;i++) {
        printf(" %c ", board[i]);
        if ((i+1)%3==0) printf("\n");
    }
    printf("\n");
}

int main() {
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *board = (char*) shmat(shmid, (void*)0, 0);

    // Initialize
    for(int i=0;i<9;i++) board[i] = '-';
    board[9] = 'X'; // Turn indicator

    int move, turn = 0;
    while(1) {
        printBoard(board);
        printf("Player %c, enter position (0-8): ", board[9]);
        scanf("%d", &move);

        if (move <0 || move >8 || board[move] != '-') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        board[move] = board[9];
        char winner = checkWinner(board);
        if (winner != '-') {
            printBoard(board);
            printf("Player %c wins!\n", winner);
            break;
        }

        // Check draw
        int full = 1;
        for (int i=0;i<9;i++) if (board[i]=='-') full=0;
        if (full) {
            printBoard(board);
            printf("Game Draw!\n");
            break;
        }

        // Switch turn
        board[9] = (board[9]=='X') ? 'O' : 'X';
    }

    shmdt(board);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}


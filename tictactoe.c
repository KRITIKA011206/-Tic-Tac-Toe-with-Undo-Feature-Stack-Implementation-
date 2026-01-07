#include <stdio.h>
#include <stdlib.h>

#define SIZE 3
#define MAX_MOVES 9

typedef struct {
    int row, col;
    char player; // 'X' or 'O'
} Move;

Move moveStack[MAX_MOVES];
int top = -1;

char board[SIZE][SIZE];

// Initialize board
void initBoard() {
    int i, j;
    for(i = 0; i < SIZE; i++)
        for(j = 0; j < SIZE; j++)
            board[i][j] = ' ';
}

// Display board
void displayBoard() {
    int i;
    printf("\n");
    for(i = 0; i < SIZE; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if(i < SIZE-1) printf("---|---|---\n");
    }
    printf("\n");
}

// Check if a move is valid
int isValid(int row, int col) {
    return row >=0 && row < SIZE && col >=0 && col < SIZE && board[row][col] == ' ';
}

// Push move to stack
void pushMove(Move m) {
    moveStack[++top] = m;
}

// Pop move from stack
Move popMove() {
    return moveStack[top--];
}

// Undo last move
void undoMove() {
    if(top < 0) {
        printf("No moves to undo!\n");
        return;
    }
    Move last = popMove();
    board[last.row][last.col] = ' ';
    printf("Undo move at (%d, %d) by player %c\n", last.row, last.col, last.player);
}

// Check for winner
char checkWinner() {
    int i;
    // Rows and columns
    for(i = 0; i < SIZE; i++) {
        if(board[i][0] == board[i][1] && board[i][1]==board[i][2] && board[i][0]!=' ') return board[i][0];
        if(board[0][i] == board[1][i] && board[1][i]==board[2][i] && board[0][i]!=' ') return board[0][i];
    }
    // Diagonals
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!=' ') return board[0][0];
    if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!=' ') return board[0][2];
    return ' ';
}

int main() {
    int row, col, moves = 0;
    char player = 'X';
    int choice;

    initBoard();

    while(1) {
        displayBoard();
        printf("Player %c, choose:\n1. Make Move\n2. Undo Last Move\n3. Exit\nChoice: ", player);
        scanf("%d", &choice);

        if(choice == 1) {
            printf("Enter row(0-2) and col(0-2): ");
            scanf("%d %d", &row, &col);
            if(!isValid(row, col)) {
                printf("Invalid move! Try again.\n");
                continue;
            }
            board[row][col] = player;
            pushMove((Move){row, col, player});
            moves++;

            char winner = checkWinner();
            if(winner != ' ') {
                displayBoard();
                printf("Player %c wins!\n", winner);
                break;
            }
            if(moves == SIZE*SIZE) {
                displayBoard();
                printf("It's a draw!\n");
                break;
            }
            player = (player == 'X') ? 'O' : 'X'; // switch player
        }
        else if(choice == 2) {
            if(moves > 0) {
                undoMove();
                moves--;
                player = (player == 'X') ? 'O' : 'X'; // switch back
            } else {
                printf("No moves to undo!\n");
            }
        }
        else if(choice == 3) {
            printf("Exiting game.\n");
            break;
        }
        else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

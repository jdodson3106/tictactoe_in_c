#include <stdbool.h>
#include <stdio.h>

const char PLAYER_ONE_VALUE = 'X';
const char PLAYER_TWO_VALUE = 'O';

void initializeGameBoard(void);
void drawBoard(void);
void promptForNextMove(void);
bool makeMove(int x, int y);
bool checkIsWon(void);
void setCurrentPlayer(void);
void printWinner(void);


char board[3][3];
int currentPlayer = 1;

int main(void) {
    initializeGameBoard(); 
    bool isWon = false;
    while(!isWon) {
        drawBoard();
        promptForNextMove();
        isWon = checkIsWon(); 
        if(isWon) {
            printWinner();
        }
        setCurrentPlayer();
    }
    return 0;
}

void drawBoard(void) {
    printf("+-----------+\n");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(j == 2)
                printf("| %c |\n", board[i][j]);
            else
                printf("| %c ", board[i][j]);
        }
    }
    printf("+-----------+\n");
}

void initializeGameBoard(void) {
    int size = sizeof(board[0]) / sizeof(board[0][0]);
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
}

void setCurrentPlayer(void) {
    if(currentPlayer == 1) 
        currentPlayer = 2;
    else
        currentPlayer = 1;
}

void promptForNextMove() {
    printf("Player %d Move: \n", currentPlayer);
    int x, y;
    scanf("%d %d", &x, &y);
    bool goodMove = makeMove(x, y);
    if(!goodMove) {
        printf("Invalid move. Try Again\n");
        promptForNextMove();
    }
}

bool makeMove(int x, int y) {
    if((0 <= x && x <= 2) && (0 <= y && y <= 2)) {
        if(board[y][x] == ' ') {
            if(currentPlayer == 1)
                board[y][x] = PLAYER_ONE_VALUE;
            else
                board[y][x] = PLAYER_TWO_VALUE;
            return true;
        }
        return false;
    }
    return false;
}

bool checkIsWon() {
    
    // check cols
    for(int i = 0; i < 3; i++) {
        char toCheck = board[i][0];
        if(toCheck == ' ') break;
        if(toCheck == board[i+1][0] && toCheck == board[i + 2][0]) {
            return true;
        }
    }

    // check rows
    for(int i = 0; i < 3; i++) {
        char toCheck = board[0][i];
        if(toCheck == ' ') break;
        if(toCheck == board[0][i+1] && toCheck == board[0][i+2]) {
            return true;
        }
    }
    
    // check diag 
    char start = board[0][0];
    if(start != ' ') {
        if(start == board[1][1] && start == board[2][2]) 
            return true;
    }

    // check anti-diag
    start = board[2][0];
    if(start != ' ') {
        if(start == board[1][1] && start == board[0][2])
            return true;
    }
    return false;
}

void printWinner(void) {
    printf("!!! Player %d Wins !!!\n", currentPlayer);
}


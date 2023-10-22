#include <stdio.h>
#include <string.h>

char board[3][3];

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
    int count = 1;
    printf("\n\n\t  ");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d", count++);
            if (j < 2) {
                printf("  |  ");
            }
        }
        if (i < 2)
            printf("\n\t----------------\n\t  ");
    }
    printf("\n\n\n");
}

void showBoard() {
    printf("\n\n\t  ");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c", board[i][j]);
            if (j < 2) {
                printf("  |  ");
            }
        }
        if (i < 2)
            printf("\n\t----------------\n\t  ");
    }
    printf("\n\n\n");
}

int updateBoard(int cell, char playerSign) {
    int row = (cell - 1) / 3;
    int col = (cell - 1) % 3;
    int isValid = 1;

    if (board[row][col] != ' ') {
        printf("\nInvalid: Cell is already Filled!\n");
        isValid = 0;
    } else {
        board[row][col] = playerSign;
    }
    showBoard();

    return isValid;
}

int checkWinner(char sg) {
    if (board[0][0] == sg && board[0][1] == sg && board[0][2] == sg ||
        board[1][0] == sg && board[1][1] == sg && board[1][2] == sg ||
        board[2][0] == sg && board[2][1] == sg && board[2][2] == sg) {
        return 1;
    } else if (board[0][0] == sg && board[1][0] == sg && board[2][0] == sg ||
               board[0][1] == sg && board[1][1] == sg && board[2][1] == sg ||
               board[0][2] == sg && board[1][2] == sg && board[2][2] == sg) {
        return 1;
    } else if (board[0][0] == sg && board[1][1] == sg && board[2][2] == sg ||
               board[0][2] == sg && board[1][1] == sg && board[2][0] == sg) {
        return 1;
    }

    return 0;
}

void getPlayerNames(char *player1Name, char *player2Name, int twoPlayerMode) {
    printf("Enter Player 1's Name: ");
    scanf("%s", player1Name);

    if (twoPlayerMode) {
        printf("Enter Player 2's Name: ");
        scanf("%s", player2Name);
    } else {
        strcpy(player2Name, "Computer");
    }
}

void playTicTacToe(int twoPlayerMode) {
    int gameResult = 0;
    int cell = 0;
    int playCount = 0;
    int updationResult = 1;

    char player1Sign = 'F';
    char player2Sign = 'L';
    char player1Name[20], player2Name[20];

    getPlayerNames(player1Name, player2Name, twoPlayerMode);

    while (!gameResult && playCount < 9) {
        printf("\n%s [ %c ] : ", player1Name, player1Sign);
        scanf("%d", &cell);
        if (cell > 0 && cell < 10) {
            updationResult = updateBoard(cell, player1Sign);
            if (updationResult) {
                gameResult = checkWinner(player1Sign);
                if (gameResult) {
                    printf("\t *** %s Won!! ***\n", player1Name);
                    break;
                }
                playCount++;
            }

            if (playCount == 9) {
                printf("\n\t *** Draw...  ***\n");
                break;
            }

            if (twoPlayerMode) {
                printf("\n%s [ %c ] : ", player2Name, player2Sign);
                scanf("%d", &cell);
                if (cell > 0 && cell < 10) {
                    updationResult = updateBoard(cell, player2Sign);
                    if (updationResult) {
                        gameResult = checkWinner(player2Sign);
                        if (gameResult) {
                            printf("\t *** %s Won!! ***\n", player2Name);
                            break;
                        }
                        playCount++;
                    }
                }
            } else {
                // Computer's move (random for simplicity)
                int computerCell;
                do {
                    computerCell = 1 + rand() % 9;
                } while (!updateBoard(computerCell, player2Sign));
                gameResult = checkWinner(player2Sign);
                if (gameResult) {
                    printf("\t *** %s (Computer) Won!! ***\n", player2Name);
                    break;
                }
                playCount++;
            }
        } else if (cell == -1) {
            printf("\n\tGame Terminated\n");
            return;
        } else {
            printf("\nPlease Enter a valid cell value\n");
        }
    }

    printf("\n\t --- Game Over --- \n");
}

int main() {
    printf("-----Welcome to our game of:----- \n\n");

    char asciiArt[] =
        " ██▓    ▓█████  ▒█████   ███▄    █  ▄▄▄          ▄▄▄       ███▄    █ ▓█████▄      █████▒▄▄▄       ▄▄▄▄    ██▓ ▄▄▄       ███▄    █  ▒█████  \n"
        "▓██▒    ▓█   ▀ ▒██▒  ██▒ ██ ▀█   █ ▒████▄       ▒████▄     ██ ▀█   █ ▒██▀ ██▌   ▓██   ▒▒████▄    ▓█████▄ ▓██▒▒████▄     ██ ▀█   █ ▒██▒  ██▒\n"
        "▒██░    ▒███   ▒██░  ██▒▓██  ▀█ ██▒▒██  ▀█▄     ▒██  ▀█▄  ▓██  ▀█ ██▒░██   █▌   ▒████ ░▒██  ▀█▄  ▒██▒ ▄██▒██▒▒██  ▀█▄  ▓██  ▀█ ██▒▒██░  ██▒\n"
        "▒██░    ▒▓█  ▄ ▒██   ██░▓██▒  ▐▌██▒░██▄▄▄▄██    ░██▄▄▄▄██ ▓██▒  ▐▌██▒░▓█▄   ▌   ░▓█▒  ░░██▄▄▄▄██ ▒██░█▀  ░██░░██▄▄▄▄██ ▓██▒  ▐▌██▒▒██   ██░\n"
        "░██████▒░▒████▒░ ████▓▒░▒██░   ▓██░ ▓█   ▓██▒    ▓█   ▓██▒▒██░   ▓██░░▒████▓    ░▒█░    ▓█   ▓██▒░▓█  ▀█▓░██░ ▓█   ▓██▒▒██░   ▓██░░ ████▓▒░\n"
        "░ ▒░▓  ░░░ ▒░ ░░ ▒░▒░▒░ ░ ▒░   ▒ ▒  ▒▒   ▓▒█░    ▒▒   ▓▒█░░ ▒░   ▒ ▒  ▒▒▓  ▒     ▒ ░    ▒▒   ▓▒█░░▒▓███▀▒░▓   ▒▒   ▓▒█░░ ▒░   ▒ ▒ ░ ▒░▒░▒░ \n"
        "░ ░ ▒  ░ ░ ░  ░  ░ ▒ ▒░ ░ ░░   ░ ▒░  ▒   ▒▒ ░     ▒   ▒▒ ░░ ░░   ░ ▒░ ░ ▒  ▒     ░       ▒   ▒▒ ░▒░▒   ░  ▒ ░  ▒   ▒▒ ░░ ░░   ░ ▒░  ░ ▒ ▒░ \n"
        "  ░ ░      ░   ░ ░ ░ ▒     ░   ░ ░   ░   ▒        ░   ▒      ░   ░ ░  ░ ░  ░     ░ ░     ░   ▒    ░    ░  ▒ ░  ░   ▒      ░   ░ ░ ░ ░ ░ ▒  \n"
        "    ░  ░   ░  ░    ░ ░           ░       ░  ░         ░  ░         ░    ░                    ░  ░ ░       ░        ░  ░         ░     ░ ░  \n"
        "                                                                      ░                                ░                                    \n";
    printf("%s", asciiArt);
    printf("--------- Tic Tac Toe ----------\n\n");

    printf("\n* Instructions \n\n");
    printf("\tPlayer 1 sign = F\n");
    printf("\tPlayer 2 sign = L");
    printf("\n\tTo exit from the game, Enter -1\n");

    printf("\n\n* Cell Numbers on the Board\n");
    initializeBoard();

    char start = ' ';
    printf("\n> Press Enter to start...");

    scanf("%c", &start);

    if (start) {
        int userChoice = 1;
        int twoPlayerMode = 0;

        while (userChoice) {
            printf("\nChoose mode:\n");
            printf("1. Two-Player Mode\n");
            printf("2. Play against Computer\n");
            printf("0. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &userChoice);

            if (userChoice == 1) {
                twoPlayerMode = 1;
            } else if (userChoice == 2) {
                twoPlayerMode = 0;
            } else if (userChoice == 0) {
                break;
            } else {
                printf("Invalid choice. Please enter 1, 2, or 0.\n");
                continue;
            }

            playTicTacToe(twoPlayerMode);
            printf("\n* Menu\n");
            printf("Press 1 to Restart\n");
            printf("Press 0 for Exit\n\n");
            printf("Choice: ");
            scanf("%d", &userChoice);
            if (userChoice) {
                initializeBoard();
            }
            printf("\n");
        }
    }
    printf("\n :: Thanks for playing Tic Tac Toe game! :: \n");
    return 0;
}

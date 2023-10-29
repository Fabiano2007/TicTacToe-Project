#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];

int findBestMove(char playerSign);
int minimax(char playerSign);

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
    getchar(); // Consume the newline character
}


int findBestMove(char playerSign) {
    char opponentSign = (playerSign == 'F') ? 'L' : 'F';
    int bestMove = -1;
    int bestScore = -1000; // Initialize with a low value

    // Prioritize the center if it's available
    if (board[1][1] == ' ') {
        return 5;
    }

    // Prioritize corners (1, 3, 7, 9) if they are available
    int corners[] = {1, 3, 7, 9};
    for (int i = 0; i < 4; i++) {
        if (board[(corners[i] - 1) / 3][(corners[i] - 1) % 3] == ' ') {
            return corners[i];
        }
    }

    // Prioritize edges (2, 4, 6, 8) if they are available
    int edges[] = {2, 4, 6, 8};
    for (int i = 0; i < 4; i++) {
        if (board[(edges[i] - 1) / 3][(edges[i] - 1) % 3] == ' ') {
            return edges[i];
        }
    }

    // If all the above conditions are not met, choose an available cell
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                // The move is valid, so try it
                board[i][j] = playerSign;

                int score = -minimax(opponentSign);

                // Undo the move
                board[i][j] = ' ';

                if (score > bestScore) {
                    bestScore = score;
                    bestMove = 3 * i + j + 1;
                }
            }
        }
    }

    return bestMove;
}

int minimax(char playerSign) {
    char opponentSign = (playerSign == 'F') ? 'L' : 'F';

    int winner = checkWinner(playerSign);
    if (winner != 0) {
        return (winner == 1) ? 1 : -1;
    }

    int isTie = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                isTie = 0;
            }
        }
    }
    if (isTie) {
        return 0;
    }

    int bestScore = (playerSign == 'F') ? -1000 : 1000;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                // The move is valid, so try it
                board[i][j] = playerSign;

                int score = -minimax(opponentSign);

                // Undo the move
                board[i][j] = ' ';

                if ((playerSign == 'F' && score > bestScore) || (playerSign == 'L' && score < bestScore)) {
                    bestScore = score;
                }
            }
        }
    }

    return bestScore;
}

void computerMove(char playerSign) {
    int bestMove = findBestMove(playerSign);
    updateBoard(bestMove, playerSign);
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

    int userChoice;

    printf("\nPress 1 to start the game, or Press 0 to exit: ");
    scanf("%d", &userChoice);
    if (userChoice == 0) {
        return;
    }

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
                // Computer's move
                computerMove(player2Sign);
                gameResult = checkWinner(player2Sign);
                if (gameResult) {
                    printf("\t *** %s (Computer) Won!! ***\n", player2Name);
                    break;
                }
                playCount++;
            }
        } else if (cell == 0) {
            printf("\n\tGame Terminated\n");
            return;
        } else {
            printf("\nPlease Enter a valid cell value\n");
        }
    }

    printf("\n\t --- Game Over --- \n");
}


int main() {
    /*printf("-----Welcome to our game of:----- \n\n");

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
    printf("%s", asciiArt);*/

    printf("--------- Tic Tac Toe ----------\n\n");

    char showInstructions;
    printf("Do you want to see the instructions? (y/n): ");
    scanf(" %c", &showInstructions);

    if (showInstructions == 'y' || showInstructions == 'Y') {
        printf("\n* Instructions \n\n");
        printf("\tThe game is played on a grid that's 3 squares by 3 squares.\n");
        printf("\tYou are F, your friend (or the computer) is L.");
        printf("\tPlayers take turns putting their marks in empty squares.\n");
        printf("\tThe first player to get 3 of her marks in a row (up, down, across, or diagonally) is the winner.\n");
        printf("\tWhen all 9 squares are full, the game is over. If no player has 3 marks in a row, the game ends in a tie.\n");
    }

    printf("\n\n* Cell Numbers on the Board\n");
    initializeBoard();

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

    printf("\n :: Thanks for playing Tic Tac Toe game! :: \n");
    return 0;
}

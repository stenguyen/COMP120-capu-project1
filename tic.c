#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


/*
    initialize the board (3x3) squares to empty (' ')
*/
void init_board(char board[]){
    for(int i = 0; i < 9; i++){
        board[i] = ' ';
    }
}

/*
    print the board. empty squares show their number so the
    player can see which squares are still open
*/
void display_board(const char board[]){
    //value to store copy of array of size 9
    char c[9];

    for(int i = 0; i < 9; i++){
        //if empty, set the value to current value to i (as a char)
        if(board[i] == ' '){
            c[i] = '0' + i;
        }
        // set the taken square
        else{
            c[i] = board[i];
        }
    }

    //print the board
    printf("\n");
    printf(" %c | %c | %c\n", c[0], c[1], c[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", c[3], c[4], c[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", c[6], c[7], c[8]);
    printf("\n");
}

/*
    returns true if the player has three in a row
    (3 rows, 3 columns, 2 diagonals)
*/
bool is_winner(const char board[], char player){

    //the winning combinations
    const int wins[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},   // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},   // columns
        {0, 4, 8}, {2, 4, 6}               // diagonals
    };
    
    //loops through 2D array to check for winning combination for current player
    for(int i = 0; i < 8; i++){
        if (board[wins[i][0]] == player && board[wins[i][1]] == player && board[wins[i][2]] == player){
            return true;
        }
    }

    return false;
} 

/*
    returns the other player's symbol (O -> X, X -> O)
*/
char other_player(char player){
    if(player == 'O'){
        return 'X';
    }
    else{
        return 'O';
    }
}

/*
    keeps asking the player for a square until they enter a valid one
    returns the square number (0-8)
*/
int get_human_move(const char board[]){
    bool valid_move = false;
    int read;
    int next;
    int choice = -1;


    //loop until a valid move is found
    while(!valid_move){
        printf("Your turn (O). Enter a square number (0-8): ");

        //read the input (for an int)
        //read = 1 if a number is read, 0 if not
        //if 1, then choice holds the number from user input
        read = scanf("%d", &choice);

        //input ended (Ctrl+D or end of file), stop the program
        if(read == EOF){
            printf("\nNo more input. Exiting.\n");
            exit(0);
        }


        //check the character right after the number
        //if it isn't the end of the line, there was extra input so remove it to clear the buffer for the next input
        next = getchar();
        if(next != '\n'){
            while(getchar() != '\n' && !feof(stdin)){}
        }

        //determine if valid square
        if(read != 1 || next != '\n'){
            printf("  That is not a valid number. Enter a digit from 0 to 8.\n");
        } else if (choice < 0 || choice > 8) {
            printf("  %d is not a valid square. Enter a number from 0 to 8.\n", choice);
        } else if (board[choice] != ' ') {
            printf("  That square is already taken. Choose an empty one.\n");
        } else {
            valid_move = true;
        }
    }

    return choice;
}

/*
    picks a random empty square for the computer
    returns the square number (0-8)
*/
int get_computer_move(const char board[]){
    int choice;

    //pick a random square at least once, repeat until it is empty
    do {
        choice = rand() % 9;
    } while (board[choice] != ' ');

    return choice;
}

/*
    gets a move from the current player (human or computer)
    and places their symbol on the board
*/
void take_turn(char board[], char player){
    int choice;

    if(player == 'O'){
        choice = get_human_move(board);
    }
    else{
        printf("Computer (X) is thinking...\n");
        choice = get_computer_move(board);
        printf("Computer (X) chose square %d. Your move next!\n", choice);
    }

    board[choice] = player;
}

/*
    plays one full game until someone wins or the board is full
*/
void play_game(){
    char board[9];
    char player = 'O';
    bool finished = false;

    init_board(board);
    printf("You are O and you go first. The computer is X.\n");
    printf("On your turn, type the number of an empty square:\n");
    display_board(board);

    for(int i = 0; i < 9 && !finished; i++){
        take_turn(board, player);
        display_board(board);

        if(is_winner(board, player)){
            finished = true;

            if(player == 'O'){
                printf("The player (O) wins!\n");
            }
            else{
                printf("The computer (X) wins!\n");
            }
        }
        else{
            player = other_player(player);
        }
    }

    if(!finished){
        printf("A draw! You both lose. :(\n");
    }
}

/*
    asks if the player wants another game
    returns true for y/Y, false for q/Q
*/
bool play_again(){
    char choice;
    int next;
    bool valid = false;

    while(!valid){
        printf("\nPlay again (y) or quit (q)? ");

        //read input, stop the program if input ended
        if(scanf(" %c", &choice) == EOF){
            printf("\n");
            return false;
        }

        //check the character right after the letter
        //if it isn't the end of the line, there was extra input so remove it to clear the buffer for the next input
        next = getchar();
        if(next != '\n'){
            while (getchar() != '\n' && !feof(stdin)) { }
        }

        //valid only if the line is exactly one of y, q, Y, Q
        if (next == '\n' && (choice == 'y' || choice == 'q' || choice == 'Y' || choice == 'Q')) {
            valid = true;
        } else {
            printf("  Please type y or q.\n");
        }
    }

    if(choice == 'y' || choice == 'Y'){
        return true;
    }
    else{
        return false;
    }

}


int main(){

    //seed rand() with the current time so every run is different
    srand((unsigned) time(NULL));

    printf("=====================================\n");
    printf("        TIC-TAC-TOE vs COMPUTER\n");
    printf("=====================================\n");

    do {
        play_game();
    } while (play_again());

    printf("Thanks for playing!\n");
    return 0;
}
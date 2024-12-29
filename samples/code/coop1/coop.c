#include <stdio.h>
#include <stdlib.h>

int main() {
    char mymove = 'C'; // Initialize first move to 'C'
    char opponentMove; // Variable that carries opponent previous move
    int input;         // Input variable for reading opponent's move
    int i = 1;         // Counter for the number of rounds
    int counter = 0;   // Counter to track consecutive opponent 'D' moves
    int found = 0;     // Variable to fix Tit - For -Tat
    int playedD = 0;   // Flag to track whether 'D' has been played in the last 1000 moves
    int playedC = 1;   // Flag to track whether 'C' has been played in the last 1000 moves

    putchar(mymove);   // Print your initial move
    putchar('\n');
    fflush(stdout);

    while ((input = getchar()) != EOF) {
        if (input == 'C' || input == 'D') {
            opponentMove = input; // Store opponent's move
            i++;

            // Reset flags after every 1000 moves
            if (i % 1000 == 0){
                playedD = 0;
                playedC = 0;
            }

            // Check for at least one C and one D in 1000 rounds
            if (i % 1000 == 999 && (playedC == 0 || playedD == 0)){
                if (playedC == 0){
                    putchar('C');
                } else if (playedD == 0){
                    putchar('D');
                }
            } else {
                if ((mymove == 'C') && (opponentMove == 'D')) { // If opponent ruins Tit - For - Tat, forgive him once
                    found += 1;
                } else {
                    found = 0;
                }
                if ( opponentMove == 'D'){ //Count how many consecutive D's the opponent has played
                    counter += 1;
                } else {
                    counter = 0;
                }
                if (counter > 2){
                    mymove = putchar('D'); // Play 'D' if opponent played 'D' for more than 2 consecutive moves
                    playedD = 1;
                } else if (found == 1){
                    mymove = putchar('C'); // Play 'C' to fix Tit - For - Tat
                    playedC = 1;
                } else {
                    mymove = putchar(opponentMove);  // Play Tit - For - Tat
                    if (mymove == 'C'){
                        playedC = 1;
                    } else {
                        playedD = 1;
                    }
                }
            }

            putchar('\n'); //Print new line
            fflush(stdout); //Print the move to stdout
        }
    }
    return 0; //Porgramm returns with success code
}

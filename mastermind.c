#include "headers.h"

#include "constants.h"

typedef enum { false, true } bool;

bool isGuessCorrect(char *guessText, char *secretText, int *correct, int *wrong){
    int i, j;

    *correct = 0;
    *wrong = 0;

    for(i=0; i<SECRET_CODE_LENGTH; i++){

        if(guessText[i] == secretText[i]){
            (*correct)++;
        } else {
            for(j=0; j<SECRET_CODE_LENGTH; j++){
                if(guessText[i] == secretText[j]){
                    (*wrong)++;
                    break;
                }
            }
        }

    }
    return *correct == SECRET_CODE_LENGTH;
}

void constructCodeRandomly(char *placeholder){
    int i = 0;
    while (i < SECRET_CODE_LENGTH) {
        placeholder[i] = rand() % 9 + '0';
        i++;
    }
}



int main (int argc, char **argv){
    char secretCode[SECRET_CODE_LENGTH + 1] = {0};
    int guessAttempts = MAX_GUESS_ATTEMPTS;
    int i;
    srand(time(NULL));

    for(i=1; i<argc; i++){
        if(strcmp(argv[i], "-c") == 0 && i + 1 < argc){
            strncpy(secretCode, argv[i+1], SECRET_CODE_LENGTH);
            i++;
        } else if (strcmp(argv[i], "-t") == 0 && i+1 < argc){
            guessAttempts = atoi(argv[i+1]);
            i++;
        }
    }

    if(secretCode[0] == 0){
        constructCodeRandomly(secretCode);
    }

    printf("Please enter a valid guess");
    for(i=0; i<guessAttempts; i++){
        char guessedCode [GUESS_BUFFER_LENGTH] = {0};
        int correctlyPlaced, wronglyPlaced;
        printf("\nRound %d\n", i);
        if(read(0, guessedCode , GUESS_BUFFER_LENGTH) <= 0 ){
            printf("Program is Exiting... Ctrl + D command entered!");
            break;
        }

        if(((guessedCode [i] >= 'a' && guessedCode [i] <= 'z') || (guessedCode [i] >= 'A' && guessedCode [i] <= 'Z'))){
            printf("Program exiting... Invalid character entered!");
            break;
        }

        if(isGuessCorrect(guessedCode , secretCode, &correctlyPlaced, &wronglyPlaced)){
            printf("Congratz! You did it!\n");
            break;
        } else {
            printf("Well placed pieces: %d \n Misplaced pieces: %d \n", correctlyPlaced, wronglyPlaced);
        }
    }
    return 0;
}

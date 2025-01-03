#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_WORD_LENGTH 50
#define MAX_TRIES 6

// Struct to hold a word and its hint
struct wordWithHint {
    char word[MAX_WORD_LENGTH];
    char hint[MAX_WORD_LENGTH];
};

// Function prototypes
void displayWord(const char word[], const bool guessed[]);
void drawHangman(int tries);

int main() {
    srand(time(NULL)); // Generate random number

    // Array of words with hints
    struct wordWithHint wordList[] = {
        {"hindu", "sanatani man"},
        {"seoul", "South Korea is famous for K-drama"},
        {"beach", "Sandy shore by the sea"},
        {"Aura", "Virat Kohli"},
    };

    // Select a random word from the list
    int wordIndex = rand() % (sizeof(wordList) / sizeof(wordList[0]));
    const char *secretWord = wordList[wordIndex].word;
    const char *hint = wordList[wordIndex].hint;

    int wordLength = strlen(secretWord);
    char guessWord[MAX_WORD_LENGTH] = {0};
    bool guessedLetters[26] = {false};

    printf("Welcome to Hangman!\n");
    printf("Hint: %s\n", hint);

    int tries = 0;
    while (tries < MAX_TRIES) {
        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);  
        guess = tolower(guess);

        if (guessedLetters[guess - 'a']) {
            printf("You have already guessed that letter.\n");
            continue;
        }

        guessedLetters[guess - 'a'] = true;

        bool found = false;
        for (int i = 0; i < wordLength; i++) {
            if (secretWord[i] == guess) {
                found = true;
                guessWord[i] = guess;
            }
        }

        if (found) {
            printf("Good guess!\n");
        } else {
            printf("Wrong guess! Try again.\n");
            tries++;
            drawHangman(tries); // Show hangman drawing
        }

        displayWord(secretWord, guessedLetters); // Show current word state

        if (strcmp(secretWord, guessWord) == 0) {
            printf("Congratulations! You guessed the word: %s\n", secretWord);
            break;
        }
    }

    if (tries >= MAX_TRIES) {
        printf("Sorry, you ran out of tries. The word was: %s\n", secretWord);
    }

    return 0;
}

// Function to display the word with guessed letters and underscores for unguessed letters
void displayWord(const char word[], const bool guessed[]) {
    printf("Word: ");
    for (int i = 0; word[i] != '\0'; i++) {
        if (guessed[word[i] - 'a']) {
            printf("%c ", word[i]); // Display guessed letter
        } else {
            printf("_ "); // Display underscore for unguessed letter
        }
    }
    printf("\n");
}

// Function to draw the hangman based on the number of wrong tries
void drawHangman(int tries) {
    const char* hangmanParts[] = {
        "     _________",    // Head
        "    |         |",    // Body
        "    |         O",    // Head
        "    |        /|\\",  // Arms
        "    |        / \\",  // Legs
        "    |"              // Base
    };

    printf("\n");
    for (int i = 0; i <= tries; i++) {
        printf("%s\n", hangmanParts[i]);
    }
}

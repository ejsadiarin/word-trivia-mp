#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_WORDS 5
#define MAX_WORD_LENGTH 20

typedef struct {
    char wordName[MAX_WORD_LENGTH];
} Word;

int main() {
    Word wordsDatabase[NUM_WORDS];
    char usedWordTracker[NUM_WORDS][MAX_WORD_LENGTH]; // Track used words
    int numUsedWords = 0;

    // Populate some example words in the database
    strcpy(wordsDatabase[0].wordName, "apple");
    strcpy(wordsDatabase[1].wordName, "banana");
    strcpy(wordsDatabase[2].wordName, "orange");
    strcpy(wordsDatabase[3].wordName, "grape");
    strcpy(wordsDatabase[4].wordName, "pear");

    srand(time(NULL)); // Seed the random number generator

    // Generate random words from the database until all words are used
    while (numUsedWords < NUM_WORDS) {
        int randWordIndex = rand() % NUM_WORDS;
        int alreadyUsed = 0;

        // Check if the word has been used before
        for (int i = 0; i < numUsedWords; i++) {
            if (strcmp(wordsDatabase[randWordIndex].wordName, usedWordTracker[i]) == 0) {
                alreadyUsed = 1;
                break;
            }
        }

        if (!alreadyUsed) {
            // If not used before, print the word and mark it as used
            printf("Random word: %s\n", wordsDatabase[randWordIndex].wordName);
            strcpy(usedWordTracker[numUsedWords], wordsDatabase[randWordIndex].wordName);
            numUsedWords++;
        }
    }

    return 0;
}

#include <stdio.h>
#include <string.h>

typedef char Word20[21]; // data type of the answers
typedef char Relation30[31];

typedef struct {
  Relation30 relation;
  Relation30 relationValue;
} TriviaType;

typedef struct {
  Word20 word;
  TriviaType trivia;
} WordType;

// at most 10 trivia per word (so word struct?)
// there can be at most 150 entries/words (answers in the game), but a word can have at most 10 trivia/clues

// Determine if the player wins based on contents in the 2D array of characters (2D strings).
int checkWinningConditions() {
  // if 1 player wins, otherwise (0) not;
  // WINS: if player answered atleast 1 question for each row in 2D array of characters
  return 0;
}

// Determine if the game is over based on the contents in the 2D array of characters.
int IsGameOver() {

}

// Menu for the Admin Phase
// each word has at most 10 trivia (relations):
void AdminMenu() {
  printf("------------------\n");
  printf("----Relation----|-----Relation Value----\n");
  printf("----Relation----|-----Relation Value----\n");
  printf("----Relation----|-----Relation Value----\n");
  printf("----Relation----|-----Relation Value----\n");
  printf("----Relation----|-----Relation Value----\n");
  printf("----Relation----|-----Relation Value----\n");

  printf("------------------\n");
}

int main() 
{
  return 0;
}

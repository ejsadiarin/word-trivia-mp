/*********************************************************************************************************
 This is to certify that this project is my own work, based on my personal
 efforts in studying and applying the concepts learned. I have constructed the
 functions and their respective algorithms and corresponding code by myself. The
 program was run, tested, and debugged by my own efforts. I further certify that
 I have not copied in part or whole or otherwise plagiarized the work of other
 students and/or persons. Edwin M. Sadiarin Jr., DLSU ID#12323004
 *********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BOARD_SIZE 15
#define MIN_BOARD_SIZE 1

typedef char Word20[21]; // data type of the answers
typedef char Relation30[31];

typedef struct {
  Relation30 relation;
  Relation30 relationValue;
} TriviaType;

typedef struct {
  Word20 wordName;
  TriviaType trivia[10];
} WordType;

typedef WordType Entries[150];

// // TODO: the char array to be displayed
// struct Board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
// typedef struct {
//   Word20 wordName;
//   TriviaType trivia[10];
// } BoardInterface;

// typedef WordType Board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

char GenerateUniqueRandomLetter(char usedLetters[], int size) {
  int i;
  char letters[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char letter = letters[rand() % (sizeof(letters) - 1)];
  // check if the letter has already been used
  for (i = 0; i < size; i++) {
    if (usedLetters[i] == letter) {
      return GenerateUniqueRandomLetter(usedLetters, size);
    }
  }

  return letter;
}

char GenerateUniqueRandomLetter2(char usedLetters[]) {
  int i;
  char letters[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char letter;
  int letterIndex;
  int isLetterUsed;

  do {
    isLetterUsed = 0;
    letterIndex = rand() % (sizeof(letters) - 1);
    letter = letters[letterIndex];
    // check if the letter has already been used
    for (i = 0; i < strlen(usedLetters); i++) {
      if (usedLetters[i] == letter) {
        isLetterUsed = 1;
      }
    }
  } while (isLetterUsed == 1);

  return letter;
}

// TODO: call in createBoard()
// int findMultiples(int entries) {
//   int i, j;
//   for (i = 1; i <= entries; i++) {
//     for (j = i; j <= num; j++) {
//       if (i * j == num) {
//       }
//     }
//   }
// }

/*
 * Returns the index of the key, otherwise -1
 *
 * NOTE: (1) to be called when selecting letter from board, (2) searching if word (entry) exists in "database"
 * */
int Search() {
  return -1;
}


/*
 * Populates the board based on the entries in the file.
 * --> asks for dimension of the board
 * --> asks user for filename (loading text file of words and trivia)
 * --> generate random latters but unique for each row
 * --> make sure to have enough entries in database for the grid board
 * */
void createBoard(char board[][MAX_BOARD_SIZE], int *row, int *col) {
  int i, j;
  srand(time(NULL));
  char usedLetters[MAX_BOARD_SIZE];
  char uniqueLetter;

  // generate random letters for the board
  for (i = 0; i < *row; i++) {
    memset(usedLetters, 0, sizeof usedLetters); // clear usedLetters array
    for (j = 0; j < *col; j++) {
      uniqueLetter = GenerateUniqueRandomLetter2(usedLetters);
      usedLetters[j] = uniqueLetter;
      // push the letter to board if not yet used
      board[i][j] = uniqueLetter;
      // printf("%c ", board[i][j]);
    }
    // printf("\n");
  }
}

void DisplayBoard(char board[][MAX_BOARD_SIZE], int row, int col) {
  int i, j;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      printf("%c ", board[i][j]);
    }
    printf("\n");
  }
}



// at most 10 trivia per word (so word struct?)
// there can be at most 150 entries/words (answers in the game), but a word can
// have at most 10 trivia/clues

// Determine if the player wins based on contents in the 2D array of characters
// (2D strings).
int isWin(char board[][MAX_BOARD_SIZE], int row, int col) {
  // given the 2d array of characters (array of strings), search for *, if found
  // TODO: to be called every after game phase
  int i, j, winFlag;
  for (i = 0; i < row; i++) {
    winFlag = 0;
    for (j = 0; j < col; j++) {
      if (board[i][j] == '*') {
        winFlag = 1;
      }
    }
    if (!winFlag) {
      return 0;
    }
  }
  // returns 1 if player wins, otherwise (0);
  // WINS: if player answered atleast 1 question for each row in 2D array of
  // characters loop through each row and check if there is at least one *
  // (correct answer), if not, return 0 (not a win)

  return 1;
}

// Determine if the game is over based on the contents in the 2D array of
// characters. calls checkWinningConditions()
// TODO: to be called every after question answered
int checkRowStatus(char rowElems[], int *row) {
  // check if col == numOfWrong (which is '-');
  int i, canProceed = 0;
  for (i = 0; i < *row; i++) {
    if (rowElems[i] == '*') {
      canProceed = 1;
    }
  }

  return canProceed;
}


int QuestionAnswerPhase(Entries wordsDatabase, int numWords, Word20 usedWordTracker[], int *numUsedWords) {
  int i, randWordIndex, alreadyUsed;
  srand(time(NULL));

  // loop until random word is unique (not included in usedWordTracker)
  do {
    randWordIndex = rand() % numWords;
    alreadyUsed = 0;
    for (i = 0; i < *numUsedWords; i++) {
      if (strcmp(wordsDatabase[randWordIndex].wordName, usedWordTracker[i]) == 0) {
        alreadyUsed = 1;
        // break;
      }
    }
  } while (alreadyUsed);

  if (!alreadyUsed) {
    // START GAME: display a random clue/trivia (only 1) of the random word
    printf("\n");
    printf("TRIVIA: %s\n", wordsDatabase[randWordIndex].wordName);
    printf("--> %s\n", wordsDatabase[randWordIndex].wordName);

    // if word is not yet used, then push random word to usedWordTracker
    strcpy(usedWordTracker[i], wordsDatabase[randWordIndex].wordName);
    (*numUsedWords)++;
  }

  return randWordIndex;
}


void gamePhase() {
  int i = 0, j = 0; 
  // NOTE: for testing
  // int row = 10;
  // int col = 10;
  int row = 0, col = 0;
  // TODO: size of the board depends on the number of word entries in the "database"

  /******INITIALIZE*******/

  // ask for filename
  // make sure to have enough entries in database for the grid board

  // NOTE: uncomment if not testing
  printf("\nEnter row of the board (min is 3, max is 10): ");
  scanf("%d", &row);
  printf("\nEnter col of the board (max): ");
  scanf("%d", &col);
  // check if row and col are within the range (input validation)
  // while (row < MIN_BOARD_SIZE || row > MAX_BOARD_SIZE || col < MIN_BOARD_SIZE || col > MAX_BOARD_SIZE) {
  //   printf("Invalid board size. Please try again.\n");
  //   printf("\nEnter row of the board (min is 3, max is 10): ");
  //   scanf("%d", &row);
  //   printf("\nEnter col of the board (min is 3, max is 10): ");
  //   scanf("%d", &col);
  // }
  // TODO: make sure to have enough entries in database for the grid board
  // if (validEntriesFlag) {
  //   createBoard(board, &row, &col);
  // }
  char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
  createBoard(board, &row, &col);
  DisplayBoard(board, row, col);

  /******PLAYING PHASE*******/
  // TODO: select letter from board, then ask question (calls questionPhase())
  // --> questionPhase() has Q&A:
  // --> - then Search() if input char is in the current row in the board
  // --> - if yes, then proceed with the question (call database for word)
  // --> if answered correctly, replace the letter with '*', otherwise '-' (calls replaceLetter())
  //
  // TODO: check every row with checkRowStatus()

  /******CHECK GAME STATUS IF WIN OR LOSE*******/
  isWin(board, row, col);
}

// Menu for the Admin Phase
// each word has at most 10 trivia (relations):
void AdminMenu() {
  int input, exitFlagToMainMenu = 0;
  while (!exitFlagToMainMenu) {
    printf("\n--------------Admin Menu--------------\n");
    printf("[1] Add Word \n");
    printf("[2] Add Trivia\n");
    printf("[3] Modify Entry\n");
    printf("[4] Delete Word\n");
    printf("[5] Delete Clue\n");
    printf("[6] View Words\n");
    printf("[7] View Clues\n");
    printf("[8] Export Data to File\n");
    printf("[9] Import Data from a File\n");
    printf("[0] Go Back to Main Menu\n");
    printf("---------------------------------------\n");
    printf("\nEnter your choice: ");
    scanf("%d", &input);
    switch (input) {
    case 0:
      exitFlagToMainMenu = 1;
      break;
    case 1:
      // AddWord();
      break;
    case 2:
      // AddTrivia();
      break;
    case 3:
      // ModifyEntry();
      break;
    case 4:
      // DeleteWord();
      break;
    case 5:
      // DeleteClue();
      break;
    case 6:
      // ViewWords();
      break;
    case 7:
      // ViewClues();
      break;
    case 8:
      // ExportDataToFile();
      break;
    case 9:
      // ImportDataFromFile();
      break;
    default:
      break;
    }
  }
}

int main() {
  int input, exitFlag = 0;
  while (!exitFlag) {
    printf("\nWelcome to the Word Trivia!\n");
    printf("[1] Game Phase (Play)\n");
    printf("[2] Admin Menu Phase\n");
    printf("[0] Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d", &input);
    switch (input) {
    case 0:
      exitFlag = 1;
      break;
    case 1:
      // if empty words, then ask to go to admin phase
      // if (kj) {
      //
      // }
      gamePhase();
      break;
    case 2:
      AdminMenu();
      break;
    default:
      // handle character input?
      // if (expression) {
      // }
      printf("Invalid input. Please try again.\n");
      break;
    }
  }
  return 0;
}

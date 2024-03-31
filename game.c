/*
 *
 *
Game Phase
        If the user chooses Game Phase from the Main menu, the program then asks
the user what dimension the board (of letters) will be. Proceed by loading the
text file of words and trivia (ask the user for the filename). From this,
generate the letters to appear in the board. 

Make sure you have enough entries in the database for the grid. Meaning, if you only have 12 entries in the
database, then you can have at most a 3x4, 4x3, 5x2, 2x5, 6x2, or 2x6 board,
since the answers in the grid should be unique words. Note also that in a row,
the letters should be unique. Once the board is initialized, the user can start
to play.

         The player starts the game by choosing which letter from the topmost
row he wants. After which, the program randomly chooses and shows one trivia
(relation and relation value) to the player. The player is then supposed to give
the answer. If the answer is wrong, the player should choose another letter from
the same row. If the answer is correct, the player now chooses another letter
from the next row. The trivia that corresponds to the word answer is shown to
the player and the program waits for the player to input his answer. This
continues on until the game ends. The game ends when all letters in a row are
answered incorrectly. Here the player loses. The player can also choose to exit
the current game (anytime within the game). In which case, since the
player has not reached the end, he loses as well. Once the player correctly
answered the trivia in the last row, the player wins.

        After the current game ends (whether the player won, lost, or chose to
exit), the program should ask if the player wants to play another game. If the
player chooses yes, then the player is again asked what dimension of board he
wants and so on. If the player chooses no, the program reverts to the Main Menu
(where the options are Admin Phase, Game Phase, and Exit). If in the Main Menu,
the user chooses Admin Phase, the program reverts to show the features of Add
Word, Add Trivia, etc. If the user chooses Game Phase, the program asks the user
regarding the game board dimension, etc. If the user chooses to exit, the
program ends.
 *
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BOARD_SIZE 15
#define MIN_BOARD_SIZE 1
#define MAX_WORDS 150
#define MAX_CLUES 10

typedef char String20[21]; // data type of the answers
typedef char String30[31];

typedef struct {
  String30 relation;
  String30 relationValue;
} CluesType;

typedef struct {
  String20 wordName;
  CluesType clues[MAX_CLUES];
  int numOfClues;
} WordType;

typedef WordType Words[MAX_WORDS]; // this is the "database"

int SearchLetterIndex(char row[], int size, char *key) {
  int i;
  for (i = 0; i < size; i++) {
    if (row[i] == *key) {
      return i;
    }
  }
  return -1;
}

int SearchWordIndex(Words wordsDatabase, int *numWords, String20 key)
{
  int i;
  for (i = 0; i < *numWords; i++)
  {
    if (strcmp(key, wordsDatabase[i].wordName) == 0)
    {
      return i;
    }
  }
  return -1;
}

void Import(Words wordsDatabase, int *numWords) {
  FILE *file;
  String30 filename;
  char line[100];
  Words importedWordsDatabase;
  int importedNumWords = 0;
  int i = 0, j = 0, k, origIndex, willOverwrite = 0;
  char input;
  char *colon_pos;

  if (*numWords == MAX_WORDS)
  {
    printf("Database is full. Cannot add more words.\n");
    return;
  }

  // ask for filename
  printf("\nEnter the filename to import: ");
  scanf("%30s", filename);
  printf("\n");

  strcat(filename, ".txt");

  file = fopen(filename, "r");
  if (file == NULL) {
    printf("[ ERROR ]: File does not exist.\n");
    return;
  }

  importedWordsDatabase[i].numOfClues = 0;

  // HACK: STORING PHASE
  while (fgets(line, sizeof(line), file) != NULL) {

    // handle empty line (<nextline>), indicates that next line will be a word
    if (line[0] == '\0' || line[0] == '\n') {
      // reset
      i++;
      j = 0;
      importedWordsDatabase[i].numOfClues = 0;
      if (*numWords == MAX_WORDS)
      {
        printf("Database is full. Cannot add more words.\n");
        return;
      }
    } 
    else {
      // remove trailing '\n'
      line[strlen(line) - 1] = '\0';

      // if WORD
      if (strncmp(line, "Object", 6) == 0) {
        // find the colon position
        colon_pos = strchr(line, ':'); // returns the index of the ':'
        if (colon_pos != NULL) {
          // skip colon and initial space
          colon_pos += 2;
          // copy substring (colon_pos to end of line) to importedWordsDatabase[i].wordName
          strcpy(importedWordsDatabase[i].wordName, colon_pos);
          importedNumWords++;
        }
      }
      // if RELATION and RELATION VALUE
      else {
        if (importedNumWords == 0) {
          printf("Clues found before any word entry. Closing file...\n");
          fclose(file);
          return;
        }

        // find the colon position
        colon_pos = strchr(line, ':'); // returns the index of the ':'
        if (colon_pos != NULL) {
          // before colon (relation)
          strncpy(importedWordsDatabase[i].clues[j].relation, line, colon_pos - line);
          importedWordsDatabase[i].clues[j].relation[colon_pos - line] = '\0';
          // skip colon and initial space
          colon_pos += 2;
          // after colon (relation value)
          strcpy(importedWordsDatabase[i].clues[j].relationValue, colon_pos);
          importedWordsDatabase[i].numOfClues++;
          j++;
        }
      }
    }
  }
 
  fclose(file);

  // HACK: COMPARING PHASE, assigns what to be overwritten
  if (importedNumWords == 0) {
    printf("No words found in the file. Closing file...\n");
  }
  else {
    for (i = 0; i < importedNumWords; i++) {
        // check if word already exists in the database
      origIndex = SearchWordIndex(wordsDatabase, numWords, importedWordsDatabase[i].wordName);

      // if origIndex is not unique (already existing in main database)
      if (origIndex != -1) {
        printf("%s already exists in the database. Overwrite Entry? [y/n]: ", importedWordsDatabase[i].wordName);
        scanf(" %c", &input);
        if (input == 'y' || input == 'Y') {
          willOverwrite = 1;
        } else if (input == 'n' || input == 'N') {
          willOverwrite = 0;
        } else {
          willOverwrite = -1;
          printf("Invalid input.\n");
          printf("Current Word Entry: %s retained.\n", wordsDatabase[origIndex].wordName);
        }
      }
      // if unique word, if (origIndex == -1)
      else {
        willOverwrite = 0;
      }

      // HACK: OVERWRITING PHASE
      if (willOverwrite == 1) {
        if (importedWordsDatabase[i].numOfClues > MAX_CLUES) {
          printf("Clues maximum limit (10) reached. Skipping word entry.\n");
        } else {
          wordsDatabase[origIndex] = importedWordsDatabase[i];
          printf("Word successfully overwritten with new data.\n");
        }
      }
      else if (willOverwrite == 0 && origIndex != -1) {
          printf("Current Word Entry: %s retained.\n", wordsDatabase[origIndex].wordName);
      }
      // if not overwriting and word is unique (new word entry)
      else if (willOverwrite == 0 && origIndex == -1) {
        if (*numWords >= MAX_WORDS)
        {
          *numWords = MAX_WORDS;
          printf("Database is now full. Cannot add more words.\n");
          return;
        }

        // if max clues is reached (> 10 or < 0) then skip, but keep previous clues
        if (importedWordsDatabase[i].numOfClues > MAX_CLUES || importedWordsDatabase[i].numOfClues < 0) {
          printf("Clues maximum limit (10) reached. Skipping word entry.\n");
        }
        else {
          strcpy(wordsDatabase[*numWords].wordName, importedWordsDatabase[i].wordName);

          for (k = 0; k < importedWordsDatabase[i].numOfClues; k++) {
            strcpy(wordsDatabase[*numWords].clues[k].relation, importedWordsDatabase[i].clues[k].relation);
            strcpy(wordsDatabase[*numWords].clues[k].relationValue, importedWordsDatabase[i].clues[k].relationValue);
          }
          wordsDatabase[*numWords].numOfClues = importedWordsDatabase[i].numOfClues; // Update the number of clues
          (*numWords)++;
        }
      }
    }
  }
}

char generateUniqueRandomLetter2(char usedLetters[]) {
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

void CreateBoard(char board[][MAX_BOARD_SIZE], int *row, int *col) {
  int i, j;
  srand(time(NULL));
  char usedLetters[100];
  char uniqueLetter;

  // generate random letters for the board
  for (i = 0; i < *row; i++) {
    memset(usedLetters, 0, sizeof usedLetters); // clear usedLetters array
    for (j = 0; j < *col; j++) {
      uniqueLetter = generateUniqueRandomLetter2(usedLetters);
      // uniqueLetter = generateUniqueRandomLetter(usedLetters, j);
      usedLetters[j] = uniqueLetter;
      // push the letter to board if not yet used
      board[i][j] = uniqueLetter;
    }
  }
}

void DisplayBoard(char board[][MAX_BOARD_SIZE], int row, int col) {
  int i, j;
  printf("\n");
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      printf("%c ", board[i][j]);
    }
    printf("\n");
  }
}

/*
 * Returns 0 if losing condition is met, otherwise returns 1 - meaning player can proceed to next row
 * */
int CheckRowStatus(char currentRow[], int col) {
  // check if col == numOfWrong (which is '-');
  int i, counter, canProceed;
  for (i = 0; i < col; i++) {
    if (currentRow[i] == '-') {
      counter++;
    }
  }

  // losing condition
  if (counter == col) {
    canProceed = 0;
  } else {
    canProceed = 1;
  }

  return canProceed;
}

int isWin(char board[][MAX_BOARD_SIZE], int row, int col) {
  // given the 2d array of characters (array of strings), search for *, if found
  int i, j, winFlag;
  for (i = 0; i < row; i++) {
    winFlag = 0;
    j = 0;
    while (j < col) {
      if (board[i][j] == '*') {
        winFlag = 1;
      }
    }

    if (!winFlag) {
      // printf("You LOSE!\n");
      return 0;
    }
  }

  // starCount should be at least equal to row (starCount >= row)


  // printf("You WIN!\n");
  return 1;
}

void GamePhase(Words *wordsDatabase, int *numWords) {
  int i, j;
  int row = 0, col = 0;
  String20 usedWordTracker[150]; // to be used in the game phase (to check if
                                 // word has already been used in the game)
  int numUsedWords = 0;

  /******INITIALIZE*******/

  // ask user for dimensions of the board
  printf("\nEnter row of the board: ");
  scanf("%d", &row);
  printf("\nEnter col of the board: ");
  scanf("%d", &col);

  // limit the board size to be MIN: 1 and MAX: 15 to fit the screen
  while (row < MIN_BOARD_SIZE || row > MAX_BOARD_SIZE || col < MIN_BOARD_SIZE ||
         col > MAX_BOARD_SIZE) {
    printf("Invalid board size. Please try again.\n");
    printf("\nEnter row of the board: ");
    scanf("%d", &row);
    printf("\nEnter col of the board: ");
    scanf("%d", &col);
  }

  // ask for filename
  Import(*wordsDatabase, numWords);

  // check if the number of words in the database is enough to create the board
  if ((row * col) > *numWords || (row * col) <= 0) {
    printf("\nInsufficient number of words to create the board. Make sure the "
           "imported file has enough words to create the board.\n");
    // clear the database (covers if board creation fails because of
    // insufficient words)
    memset(wordsDatabase, 0, sizeof *wordsDatabase);
    *numWords = 0;
    return;
  }

  // only create board if all good
  char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
  CreateBoard(board, &row, &col);

  /******PLAYING PHASE*******/
  String20 userAnswerInput;
  char letterInput;
  int randWordIndex, randClueIndex, letterIndex, canProceedToNextRow = 0, gameStatus = 1;
  srand(time(NULL)); // seed for random number generator

  for (i = 0; i < row && gameStatus == 1; i++) {
    // check status of previous row
    j = 0;
    while (j < col && canProceedToNextRow == 0) {
      DisplayBoard(board, row, col);
      // input letter
      printf("Choose letter in board on row %d: ", i + 1);
      scanf("%c", &letterInput);
      letterIndex = SearchLetterIndex(board[i], col, &letterInput);
      while (letterIndex == -1) {
        printf("Letter not found in row %d. Please try again.", i + 1);
        scanf("%c", &letterInput);
        letterIndex = SearchLetterIndex(board[i], col, &letterInput);
      }
      // program chooses and shows one trivia
      randWordIndex = rand() % *numWords;
      randClueIndex = rand() % *numWords;
      printf("TRIVIA: %s\n", wordsDatabase[randWordIndex]->clues[randClueIndex].relation);
      printf("--> %s\n", wordsDatabase[randWordIndex]->clues[randClueIndex].relationValue);
      // input player answer
      printf("Enter your answer: ");
      scanf(" %s", userAnswerInput);
      // --> if wrong, choose another letter from same row (repeat)
      if (strcmp(userAnswerInput, wordsDatabase[randWordIndex]->wordName) != 0) {
        printf("Incorrect answer. Choose another letter from the same row.\n");
        board[i][letterIndex] = '-';
        canProceedToNextRow = 0;
        if (j == col - 1) {
          printf("You LOSE!\n");
          canProceedToNextRow = 1; // exit inner loop
          j = 0; // reset j
        } 
        else {
          j++;
        }
      }
      // --> if correct, choose another letter from next row (proceed)
      if (strcmp(userAnswerInput, wordsDatabase[randWordIndex]->wordName) == 0) {
        printf("Correct answer. Choose another letter from the next row.\n");
        board[i][letterIndex] = '*';
        canProceedToNextRow = 1;
        j = 0;
      }
      // wait for player input then evaluate
      // continue until game ends
      // game ends:
      // --> all letters in a row are answered incorrectly (lose)
      // --> all rows have atleast one '*' meaning answered correctly (win)
      // --> player can exit anytime (lose)
      
    } // j col
    gameStatus = CheckRowStatus(board[i], col);
    if (gameStatus == 0) {
      printf("You LOSE!\n");
    }
    // evaluate
    // if (i == row - 1 && gameStatus == 0) {
    //   isWin(board, row, col);
    // }
  } // i row

  /******CHECK GAME STATUS IF WIN OR LOSE*******/
  printf("Game ends.\n");
  // int winFlag;
  // isWin(board, row, col);
  // after end: ask if player wants to play another game
  // --> if yes, ask for board dimensions
  // --> if no, revert to main menu
}

int main() {
  int input, exitFlag = 0;
  int numWords = 0;
  Words wordsDatabase; // main database

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
      GamePhase(&wordsDatabase, &numWords);
      break;
    case 2:
      // AdminMenu(&wordsDatabase, &numWords);
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

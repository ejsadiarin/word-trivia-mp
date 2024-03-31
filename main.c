/*********************************************************************************************************
 This is to certify that this project is my own work, based on my personal
 efforts in studying and applying the concepts learned. I have constructed the
 functions and their respective algorithms and corresponding code by myself. The
 program was run, tested, and debugged by my own efforts. I further certify that
 I have not copied in part or whole or otherwise plagiarized the work of other
 students and/or persons.               Edwin M. Sadiarin Jr., DLSU ID#12323004
 *********************************************************************************************************/

#include "SADIARIN_wordTrivia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* #############################################
 * ################ GAME PHASE #################
 * #############################################
 */

/*
* Returns 1 if all letters in the array are unique, otherwise 0
 * */
int isUniqueLetter(char lettersContext[], int letterCountInRow) {
  int i, j, uniqueFlag;

  uniqueFlag = 1; // assume all words are unique

  for (i = 0; i < letterCountInRow; i++) {
    for (j = i + 1; j < letterCountInRow; j++) {
      if (lettersContext[i] == lettersContext[j]) {
        uniqueFlag = 0;
      }
    }
  }
  return uniqueFlag;
}

char generateUniqueRandomLetter(char usedLetters[], int size) {
  int i;
  char letters[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char letter = letters[rand() % (sizeof(letters) - 1)];
  // check if the letter has already been used
  for (i = 0; i < size; i++) {
    if (usedLetters[i] == letter) {
      return generateUniqueRandomLetter(usedLetters, size);
    }
  }

  return letter;
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

/*
 * Returns the index of the key, otherwise -1
 *
 * TODO: to be called when selecting letter from board
 * */
int SearchLetter(char row[], int size, char key) {
  int i;
  for (i = 0; i < size; i++) {
    if (row[i] == key) {
      return i;
    }
  }
  return -1;
}

/*
 * Populates the board based on the Words in the file.
 * --> generate random letters but unique for each row
 * */
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

// --> ensure word/answer is unique (not yet used in the game/grid) - push to usedWordTracker array
// --> if answered correctly, replace the letter with '*', otherwise '-'

/*
 * is responsible for generating unique question from wordsDatabase
 * check if question is unique (not yet used in the game/grid)
 * --> if unique, then proceed with the question
 * --> if not, then generate another question
 *  Returns the index of the random word, otherwise -1
 * */
int RandWordQuestion(Words wordsDatabase, int numWords, String20 usedWordTracker[], int *numUsedWords) {
  int i, j, randWordIndex, randClueIndex, alreadyUsed;

  // initialize usedWordTracker array
  for (int n = 0; n < MAX_WORDS; n++) {
    usedWordTracker[n][0] = '\0';
  }

  // loop until random word is unique or not already used (not included in usedWordTracker)
  do {
    randWordIndex = rand() % numWords;
    alreadyUsed = 0; // assume word is not yet used
    for (i = 0; i < *numUsedWords; i++) {
      if (strcmp(wordsDatabase[randWordIndex].wordName, usedWordTracker[i]) == 0) {
        alreadyUsed = 1;
        // break;
      }
    }

    // If the word has not been used, add it to the usedWordTracker array
    if (alreadyUsed == 0) {
      strcpy(usedWordTracker[*numUsedWords], wordsDatabase[randWordIndex].wordName);
      (*numUsedWords)++;
    }

  } while (*numUsedWords > MAX_WORDS || alreadyUsed == 1);

  if (alreadyUsed == 0) {
    // START GAME: display a random clue/trivia (only 1) of the random word
    randClueIndex = rand() % wordsDatabase[randWordIndex].numOfClues;
    printf("\n");
    printf("TRIVIA: %s\n", wordsDatabase[randWordIndex].clues[randClueIndex].relation);
    printf("--> %s\n", wordsDatabase[randWordIndex].clues[randClueIndex].relationValue);
    printf("CORRECT ANSWER FOR DEBUGGING: %s\n", wordsDatabase[randWordIndex].wordName);

    // if word is not yet used, then push random word to usedWordTracker
    // strcpy(usedWordTracker[i], wordsDatabase[randWordIndex].wordName);
    // (*numUsedWords)++;
    return randWordIndex;
  }

  return -1;
}

int RandWordQuestion2(Words wordsDatabase, int numWords, String20 usedWordTracker[], int *numUsedWords) {
  int i, j, randWordIndex, randClueIndex, alreadyUsed;

  // initialize usedWordTracker array
  // for (int n = 0; n < MAX_WORDS; n++) {
  //   usedWordTracker[n][0] = '\0';
  // }

  // loop until random word is unique or not already used (not included in usedWordTracker)
  // do {
  //   randWordIndex = rand() % numWords;
  //   alreadyUsed = 0; // assume word is not yet used
  //   for (i = 0; i < *numUsedWords; i++) {
  //     if (strcmp(wordsDatabase[randWordIndex].wordName, usedWordTracker[i]) == 0) {
  //       alreadyUsed = 1;
  //       // break;
  //     }
  //   }
  //
  //   // If the word has not been used, add it to the usedWordTracker array
  //   if (alreadyUsed == 0) {
  //     strcpy(usedWordTracker[*numUsedWords], wordsDatabase[randWordIndex].wordName);
  //     (*numUsedWords)++;
  //   }
  //
  // } while (*numUsedWords > MAX_WORDS || alreadyUsed == 1);

  // if (alreadyUsed == 0) {
    // START GAME: display a random clue/trivia (only 1) of the random word
    randWordIndex = rand() % numWords;
    randClueIndex = rand() % wordsDatabase[randWordIndex].numOfClues;
    printf("\n");
    printf("TRIVIA: %s\n", wordsDatabase[randWordIndex].clues[randClueIndex].relation);
    printf("--> %s\n", wordsDatabase[randWordIndex].clues[randClueIndex].relationValue);
    printf("CORRECT ANSWER FOR DEBUGGING: %s\n", wordsDatabase[randWordIndex].wordName);

    // if word is not yet used, then push random word to usedWordTracker
    // strcpy(usedWordTracker[i], wordsDatabase[randWordIndex].wordName);
    // (*numUsedWords)++;
    return randWordIndex;
  // }

  return -1;
}

/*
 * Determine if the player wins based on contents in the 2D array of characters (2D strings).
 * if player answered atleast 1 question for each row in 2D array of
 * characters loop through each row and check if there is at least one '*'
 * (correct answer), if not, return 0 (not a win)
 *
 * */
int isWin(char board[][MAX_BOARD_SIZE], int row, int col) {
  // given the 2d array of characters (array of strings), search for *, if found
  int i, j, winFlag;
  for (i = 0; i < row; i++) {
    winFlag = 0;
    for (j = 0; j < col; j++) {
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

// Determine if the game is over based on the contents in the 2D array of
// characters. calls checkWinningConditions()
// TODO: to be called every after question answered
int CheckRowStatus(char currentRow[], int col) {
  // check if col == numOfWrong (which is '-');
  int i, canProceed = 0;
  for (i = 0; i < col; i++) {
    if (currentRow[i] == '*') {
      canProceed = 1;
    }
  }

  return canProceed;
}

void GamePhase(Words *wordsDatabase, int *numWords) {
  int i = 0, j = 0;
  int row = 0, col = 0;
  String20 usedWordTracker[150]; // to be used in the game phase (to check if word has already been used in the game)
  int numUsedWords = 0;

  /******INITIALIZE*******/

  // ask user for dimensions of the board
  printf("\nEnter row of the board: ");
  scanf("%d", &row);
  printf("\nEnter col of the board: ");
  scanf("%d", &col);

  // limit the board size to be MIN: 1 and MAX: 15 to fit the screen
  while (row < MIN_BOARD_SIZE || row > MAX_BOARD_SIZE || col < MIN_BOARD_SIZE || col > MAX_BOARD_SIZE) {
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
    printf("\nInsufficient number of words to create the board. Make sure the imported file has enough words to create the board.\n");
    // clear the database (covers if board creation fails because of insufficient words)
    memset(wordsDatabase, 0, sizeof *wordsDatabase);
    *numWords = 0;
    return;
  }

  // only create board if all good
  char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
  CreateBoard(board, &row, &col);

  /******PLAYING PHASE*******/
  // TODO: select letter from board, then ask question (calls questionPhase())
  String20 userAnswerInput;
  char letterInput;
  int randWordIndex, letterIndex, canProceedToNextRow;

  for (i = 0; i < row; i++) {
    printf("\n---------------------------------------\n");
    DisplayBoard(board, row, col);
    canProceedToNextRow = 0;
    memset(userAnswerInput, 0, sizeof *userAnswerInput);
    do {
      for (j = 0; j < col && canProceedToNextRow == 0; j++) {

        // reset userAnswerInput
        memset(userAnswerInput, 0, sizeof *userAnswerInput);

        printf("[ ROW %d ] Choose the letter you want to guess in row %d: ", i + 1, i + 1);
        scanf(" %c", &letterInput);

        while (letterInput == '*' || letterInput == '-') {
          printf("\nInvalid input. Please try again.\n");
          printf("[ ROW %d ] Choose the letter you want to guess in row %d: ", i + 1, i + 1);
          scanf(" %c", &letterInput);
        }

        // convert letterInput to uppercase
        if (letterInput >= 'a' && letterInput <= 'z')
          letterInput = letterInput - 32;

        letterIndex = SearchLetter(board[i], col, letterInput);

        // if letter does not exist
        while (letterIndex == -1) {
          printf("Letter does not exist in the current row. Please try again.\n");
          printf("[ ROW %d ] Choose the letter you want to guess in row %d: ", i + 1, i + 1);
          scanf(" %c", &letterInput);
          letterIndex = SearchLetter(board[i], col, letterInput);
          // convert letterInput to uppercase
          if (letterInput >= 'a' && letterInput <= 'z')
            letterInput = letterInput - 32;
        }

        // if letter exists, then proceed with the question (call database for word)
        if (letterIndex != -1 && letterInput != '*' && letterInput != '-') {
          randWordIndex = RandWordQuestion2(*wordsDatabase, *numWords, usedWordTracker, &numUsedWords);

          printf("Enter your answer [enter 0 to exit game (auto lose)]: ");
          scanf("%20s", userAnswerInput);

          if (strcmp(userAnswerInput, "0") == 0) {
            printf("Exiting game...\n");
            return;
          }

          printf("before strcmp\n");
          printf("randWordIndex: %d\n", randWordIndex);
          printf("userAnswerInput: %s\n", userAnswerInput);

          if (strcmp(userAnswerInput, wordsDatabase[randWordIndex]->wordName) == 0) {
            printf("after strcmp\n");
            board[i][letterIndex] = '*'; // replace the letter with '*' if answered correctly
          }
          else {
            printf("after strcmp\n");
            board[i][letterIndex] = '-';
          }

          printf("proceed\n");
          canProceedToNextRow = CheckRowStatus(board[i], col);
          if (canProceedToNextRow == 0) {
            // display new board with the updated row that has '-'
            DisplayBoard(board, row, col);
            printf("\n");
            printf("Wrong answer! Choose another letter in the current row...\n");
          }  
          if (canProceedToNextRow == 1) {
            printf("Correct answer! Proceeding to the next row...\n");
          }
        } // if letter exists
      } // j col
    } while (canProceedToNextRow == 0);

  } // i row

  /******CHECK GAME STATUS IF WIN OR LOSE*******/
  int winFlag;
  isWin(board, row, col);
}

/* #############################################
 * ############### ADMIN PHASE ################
 * #############################################
 */

void SortEntriesAlphabetically(Words wordsDatabase, int *numWords)
{
  int i, j;
  WordType temp;
  for (i = 0; i < *numWords; i++)
  {
    for (j = i + 1; j < *numWords; j++)
    {
      if (strcmp(wordsDatabase[i].wordName, wordsDatabase[j].wordName) > 0)
      {
        temp = wordsDatabase[i];
        wordsDatabase[i] = wordsDatabase[j];
        wordsDatabase[j] = temp;
      }
    }
  }
}

void DisplayAllWords(Words wordsDatabase, int *numWords)
{
  int i;

  // handle case where there is no words
  if (*numWords == 0)
  {
    printf("No words in the database. Please add words first.\n");
    return;
  }

  SortEntriesAlphabetically(wordsDatabase, numWords);
  for (i = 0; i < *numWords; i++)
  {
    printf("%s\n", wordsDatabase[i].wordName);
  }
}

/*
 *
 * Returns the index of the word in the database, otherwise -1 (-1 means unique, does not yet exist)
 * */
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

int SearchClueIndex(CluesType clues[], int *numOfClues, String30 key)
{
  int i;
  for (i = 0; i < *numOfClues; i++)
  {
    if (strcmp(key, clues[i].relation) == 0)
    {
      return i;
    }
  }
  return -1;
}

/*
 * Assumes that word already exists in the database.
 * TODO: check if this is 'callable' in Import()
 * */
void OverwriteWord(Words wordsDatabase, int *numWords, String20 origWord, String20 newWord)
{
  int newWordIndex;

  newWordIndex = SearchWordIndex(wordsDatabase, numWords, newWord);
  // if unique, then overwrite
  if (newWordIndex == -1)
  {
    strcpy(origWord, newWord);
    printf("Word successfully overwritten/modified.\n");
  }
  else 
  {
    printf("Word already exists in the database. Exiting...\n");
  }
}

/*
 * Assume that we are operating on the clues of the current wordsDatabase[origIndex]->wordname
 * TODO: check if this is necessary to be called in ImportDataFromFile()
 * */
void OverwriteClue(CluesType clues[], int *numOfClues, String30 newClue, String30 newClueValue)
{
  int i, j, currentClueIndex;

  // check if newClue exists in the current word
  for (i = 0; i < *numOfClues; i++)
  {
    if (strcmp(newClue, clues[i].relation) == 0)
    {
      currentClueIndex = i;
    }
  }

  if (*numOfClues > MAX_CLUES)
  {
    printf("Clues maximum limit (10) reached.\n");
    return;
  }

  // if clue exists, then it will be overwritten
  if (currentClueIndex >= 0)
  {
    strcpy(clues[currentClueIndex].relation, newClue);
    strcpy(clues[currentClueIndex].relationValue, newClueValue);
    printf("Clues successfully overwritten/modified.\n");
  }
  else
  {
    printf("Clue does not exist in the database.\n");
  }
}

/*
 * Assume that the word already exists in the database.
 * */
void AddCluesAction(Words wordsDatabase, int wordIndex)
{
  int i, j, willRepeat = 0;
  char yn;
  String30 relation, relationValue;

  if (wordsDatabase[wordIndex].numOfClues >= MAX_CLUES)
  {
    printf("Clues maximum limit (10) reached.\n");
  } 
  else
  {
    // then add clues
    do
    {
      // add clues to the word
      printf("\n");
      printf("Enter relation: ");
      scanf("%30s", relation);
      printf("Enter relation value: ");
      scanf("%30s", relationValue);
      printf("\n");

      strcpy(wordsDatabase[wordIndex].clues[wordsDatabase[wordIndex].numOfClues].relation, relation);
      strcpy(wordsDatabase[wordIndex].clues[wordsDatabase[wordIndex].numOfClues].relationValue, relationValue);
      wordsDatabase[wordIndex].numOfClues++;

      printf("Added new clue to word %s!\n", wordsDatabase[wordIndex].wordName);

      // ask if user wants to add more clues
      printf("\nDo you want to add more clues? [y/n]: ");
      scanf(" %c", &yn);
      if (yn == 'y' || yn == 'Y')
      {
        if (wordsDatabase[wordIndex].numOfClues >= MAX_CLUES)
        {
          printf("Clues maximum limit (10) reached. Exiting...\n");
          willRepeat = 0;
        }
        else
        {
          willRepeat = 1;
        }
      }
      else if (yn == 'n' || yn == 'N')
      {
        willRepeat = 0;
      }
      else
      {
        printf("Invalid input. Exiting...\n");
        willRepeat = 0;
      }
    } while (willRepeat == 1);
  }
}

void AddCluesUI(Words wordsDatabase, int *numWords)
{
  int wordIndex;
  String20 input;

  if (*numWords == 0)
  {
    printf("No words in the database. Please add words first.\n");
  }
  else {
    DisplayAllWords(wordsDatabase, numWords);

    printf("\nEnter word to add clues to: ");
    scanf("%s", input);

    wordIndex = SearchWordIndex(wordsDatabase, numWords, input);
    // if word exists in the database
    if (wordIndex != -1)
    {
      // then add clues
      AddCluesAction(wordsDatabase, wordIndex);
    }
    else
    {
      printf("Word does not exist in the database. Cannot add clues.\n");
    }
  }
}

/*
 * Show a listing of all words before asking your user to type the word whose clues he wants to view.
 * The list of relations and relation values of the chosen word should be shown. Make sure
 * that garbage values are not displayed. Using the example table above, this is view:
 *     Object: Table
 *       Kind of: Furniture
 *       Part: Top
 *       Part: Leg
 *       Height: Meter
 *       Make: Wood, Plastic
 *       Color: Brown, White, Black
 *
 * */
void ViewClues(Words wordsDatabase, int *numWords)
{
  int i, index;
  String20 word;

  // printf("\n--------------------------------------------------------\n");
  DisplayAllWords(wordsDatabase, numWords);

  if (*numWords == 0)
  {
    printf("\nNo words in the database. Please add words first.\n");
    return;
  }

  printf("\n[0] - Go back to the menu\n");
  printf("[1] - Display all words again\n");
  printf("Enter the word you want to view the clues on: ");
  scanf("%s", word);
  printf("\n");

  if (strcmp(word, "0") == 0)
  {
    return;
  }

  index = SearchWordIndex(wordsDatabase, numWords, word);
  if (index >= 0)
  {
    printf("Object: %s\n", wordsDatabase[index].wordName);
    for (i = 0; i < wordsDatabase[index].numOfClues; i++)
    {
      printf("  %s: %s\n", wordsDatabase[index].clues[i].relation, wordsDatabase[index].clues[i].relationValue);
    }
  }
  else if (strcmp(word, "1") == 0)
  {
    DisplayAllWords(wordsDatabase, numWords);
  }
  else
  {
    printf("Word: %s does not exist in the database.\n", word);
  }
}

/*
    Provide a listing of all words (in alphabetical order). The list of trivia of each word should also be
    shown. Display each word one at a time until all entries have been displayed. Provide a way for
    the user to view the next or previous word or exit the view (i.e., press ‘N’ for next, ‘P’ for previous,
    ‘X’ to end the display and go back to the menu).
*/
void ViewWords(Words wordsDatabase, int *numWords)
{
  int i = 0, j, willRepeat = 1;
  char input;

  if (*numWords == 0)
  {
    printf("\nNo words in the database. Please add words first.\n");
    return;
  }

  SortEntriesAlphabetically(wordsDatabase, numWords);

  do
  {
    // show word (alphabetical order)
    printf("\n");
    printf("Object: %s\n", wordsDatabase[i].wordName);
    for (j = 0; j < wordsDatabase[i].numOfClues; j++)
    {
      printf("  %s: %s\n", wordsDatabase[i].clues[j].relation, wordsDatabase[i].clues[j].relationValue);
    }

    // options:
    printf("\n[N] - Next, [P] - Previous, [X] - Exit\n");
    printf("Enter your choice: ");
    scanf(" %c", &input);
    printf("\n");

    // handle next/previous options
    if ((input == 'N' || input == 'n'))
    {
      if (i < *numWords - 1)
        i++;
      else
        printf("End of the list.\n");
    }
    else if ((input == 'P' || input == 'p'))
    {
      if (i > 0)
        i--;
      else
        printf("Start of the list.\n");
    }
    else if (input == 'X' || input == 'x')
    {
      willRepeat = 0; // exit
    }
    else
    {
      printf("Invalid input. Please try again.\n");
    }
  } while (i < *numWords && willRepeat == 1);
}

/*
 * */
void AddWord(Words wordsDatabase, int *numWords)
{
  String20 input;
  int index;

  SortEntriesAlphabetically(wordsDatabase, numWords);

  // check if there is still space in the database
  if (*numWords == MAX_WORDS)
  {
    printf("Database is full. Cannot add more words.\n");
    return;
  }

  printf("\nEnter word to add: ");
  scanf("%s", input);

  // if word already exists in the database, exit
  index = SearchWordIndex(wordsDatabase, numWords, input);
  if (index != -1)
  {
    printf("\nWord already exists in the database. Exiting...\n");
    return;
  }

  // add new unique word
  strcpy(wordsDatabase[*numWords].wordName, input);
  // add clues to the new word
  AddCluesAction(wordsDatabase, *numWords);
  (*numWords)++;
}

void ModifyEntry(Words wordsDatabase, int *numWords)
{
  int i, j, origIndex, newWordIndex, choice = -1, newWordChoice, clueChoice;
  String20 input, newWord;
  String30 newClue, newClueValue;

  SortEntriesAlphabetically(wordsDatabase, numWords);

  if (*numWords == 0)
  {
    printf("No words in the database. Please add words first.\n");
    return;
  }

  DisplayAllWords(wordsDatabase, numWords);

  printf("\nEnter word to modify: ");
  scanf("%20s", input);

  // check if word exists in the database
  origIndex = SearchWordIndex(wordsDatabase, numWords, input);
  if (origIndex < 0)
  {
    printf("Word does not exist in the database.\n");
    return;
  }

  while (choice != 0)
  {
    // show selected entry to be modified:
    printf("\n---------------------------------------\n");
    printf("CHOSEN WORD: %s\n", wordsDatabase[origIndex].wordName);
    for (i = 0; i < wordsDatabase[origIndex].numOfClues; i++)
    {
      printf("  %s: %s\n", wordsDatabase[origIndex].clues[i].relation, wordsDatabase[origIndex].clues[i].relationValue);
    }

    printf("[1] - Modify the Word, [2] - Modify a Clue, [0] - Go back to Admin Menu.\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    printf("\n");

    if (choice == 1)
    {
      printf("Enter new word: ");
      scanf("%s", newWord);

      // overwrite original word with new word if newWord is unique
      OverwriteWord(wordsDatabase, numWords, wordsDatabase[origIndex].wordName, newWord);
    }
    // modify a clue in the selected word
    else if (choice == 2)
    {
      printf("\n---------------------------------------\n");
      printf("CHOSEN WORD: %s\n", wordsDatabase[origIndex].wordName);
      for (j = 0; j < wordsDatabase[origIndex].numOfClues; j++)
      {
        printf("[%d] %s: %s\n", j + 1, wordsDatabase[origIndex].clues[j].relation, wordsDatabase[origIndex].clues[j].relationValue);
      }
      printf("Choose the number of the clue to modify: ");
      scanf("%d", &clueChoice);
      if (clueChoice > wordsDatabase[origIndex].numOfClues || clueChoice < 1)
      {
        printf("Invalid number. Exiting...\n");
      }
      else {
        printf("Enter new clue (relation): ");
        scanf("%30s", newClue);
        printf("\nEnter new clue value (relation value): ");
        scanf("%30s", newClueValue);

        strcpy(wordsDatabase[origIndex].clues[clueChoice - 1].relation, newClue);
        strcpy(wordsDatabase[origIndex].clues[clueChoice - 1].relationValue, newClueValue);
        printf("Clues successfully overwritten/modified.\n");
      }
    }
    else if (choice == 0)
    {
      return;
    }
    else
    {
      printf("Invalid input.\n");
    }
  }
}

void DeleteWord(Words wordsDatabase, int *numWords)
{
  int i, index;
  String20 input;

  SortEntriesAlphabetically(wordsDatabase, numWords);

  DisplayAllWords(wordsDatabase, numWords);

  printf("\nEnter the word you want to delete: ");
  scanf("%s", input);

  index = SearchWordIndex(wordsDatabase, numWords, input);
  // if word does not exist (is Unique) in the database, exit
  if (index == -1)
  {
    printf("Word does not exist in the database.\n");
    return;
  }

  for (i = index; i < *numWords - 1; i++)
  {
    // shift left
    wordsDatabase[i] = wordsDatabase[i + 1];
  }

  (*numWords)--;

  printf("Word successfully deleted.\n");
}

void DeleteClue(Words wordsDatabase, int *numWords)
{
  int n, i, j, wordToDeleteIndex, indexClue, clueChoice;
  String20 input;
  String30 relation;

  // SortEntriesAlphabetically(wordsDatabase, numWords);
  DisplayAllWords(wordsDatabase, numWords);

  printf("\nEnter the word you want to delete a clue from: ");
  scanf("%s", input);

  wordToDeleteIndex = SearchWordIndex(wordsDatabase, numWords, input);
  // if wordToDeleteIndex exist/is not unique
  if (wordToDeleteIndex != -1)
  {
    // display
    printf("\n---------------------------------------\n");
    printf("FROM WORD: %s\n", wordsDatabase[wordToDeleteIndex].wordName);
    for (n = 0; n < wordsDatabase[wordToDeleteIndex].numOfClues; n++)
    {
      printf("[%d] %s: %s\n", n + 1, wordsDatabase[wordToDeleteIndex].clues[n].relation, wordsDatabase[wordToDeleteIndex].clues[n].relationValue);
    }
    printf("Choose the number of the clue to delete: ");
    scanf("%d", &clueChoice);
    if (clueChoice > wordsDatabase[wordToDeleteIndex].numOfClues || clueChoice < 1)
    {
      printf("Invalid number. Exiting...\n");
    }
    else {
      for (i = clueChoice - 1; i < wordsDatabase[wordToDeleteIndex].numOfClues - 1; i++)
      {
        // shift all clues to the left
        wordsDatabase[wordToDeleteIndex].clues[i] = wordsDatabase[wordToDeleteIndex].clues[i + 1];
      }
      wordsDatabase[wordToDeleteIndex].numOfClues--;
      printf("Clue successfully deleted.\n");
      return;
    }
  }
  else 
  {
    printf("Clue does not exist in the database.\n");
  }

}

/*
 */
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

void Export(Words wordsDatabase, int *numWords) {
  int i, j;
  FILE *file;
  String30 filename;

  if (*numWords == 0) {
    printf("No words in the database. Please add words first.\n");
    return;
  }

  if (*numWords > MAX_WORDS) {
    printf("Error: Cannot export data entries greater than 150.\n");
    return;
  }

  SortEntriesAlphabetically(wordsDatabase, numWords);

  printf("\nEnter the filename to save the data to: ");
  scanf("%30s", filename);

  strcat(filename, ".txt");

  file = fopen(filename, "w");

  for (i = 0; i < *numWords; i++) {
    fprintf(file, "Object: %s\n", wordsDatabase[i].wordName);
    for (j = 0; j < wordsDatabase[i].numOfClues; j++) {
      fprintf(file, "%s: %s\n", wordsDatabase[i].clues[j].relation, wordsDatabase[i].clues[j].relationValue);
    }
    fprintf(file, "\n");
  }

  fclose(file);
}

// Menu for the Admin Phase
void AdminMenu(Words *wordsDatabase, int *numWords)
{
  int input, i, j, exitFlagToMainMenu = 0;
  while (!exitFlagToMainMenu)
  {
    printf("\n--------------Admin Menu--------------\n");
    printf("[1] Add Word \n");
    printf("[2] Add Clues\n");
    printf("[3] Modify Entry\n");
    printf("[4] Delete Word\n");
    printf("[5] Delete Clue\n");
    printf("[6] View Words\n");
    printf("[7] View Clues\n");
    printf("[8] Export Data to File\n");
    printf("[9] Import Data from a File\n");
    printf("[0] Go Back to Main Menu\n");
    printf("---------------------------------------\n");
    printf("\nEnter the number of your choice: ");
    scanf("%d", &input);

    // validate input
    while (input < 0 || input > 9)
    {
      printf("\nInvalid input. Please try again.\n");
      printf("\nEnter the number of your choice: ");
      scanf("%d", &input);
    }

    switch (input)
    {
    case 0:
      // TODO: erase the database, since export is the only way to save
      memset(*wordsDatabase, 0, sizeof *wordsDatabase);
      *numWords = 0;
      exitFlagToMainMenu = 1;
      break;
    case 1:
      AddWord(*wordsDatabase, numWords);
      break;
    case 2:
      AddCluesUI(*wordsDatabase, numWords);
      break;
    case 3:
      ModifyEntry(*wordsDatabase, numWords);
      break;
    case 4:
      DeleteWord(*wordsDatabase, numWords);
      break;
    case 5:
      DeleteClue(*wordsDatabase, numWords);
      break;
    case 6:
      ViewWords(*wordsDatabase, numWords);
      break;
    case 7:
      ViewClues(*wordsDatabase, numWords);
      break;
    case 8:
      Export(*wordsDatabase, numWords);
      break;
    case 9:
      Import(*wordsDatabase, numWords);
      break;
    default:
      break;
    }
  }
}

int main()
{
  int input, exitFlag = 0;
  int numWords = 0;
  Words wordsDatabase; // main database

  while (!exitFlag)
  {
    printf("\nWelcome to the Word Trivia!\n");
    printf("[1] Game Phase (Play)\n");
    printf("[2] Admin Menu Phase\n");
    printf("[0] Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d", &input);
    switch (input)
    {
    case 0:
      exitFlag = 1;
      break;
    case 1:
      GamePhase(&wordsDatabase, &numWords);
      break;
    case 2:
      AdminMenu(&wordsDatabase, &numWords);
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

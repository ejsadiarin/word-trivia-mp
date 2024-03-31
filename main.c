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

/* SearchLetter searches for the key (letter) in the specified row
 *
 * @param row - array of characters representing a row in the board
 * @param size - size of the row
 * @param key - the letter to search in the row
 * @return the index of the letter in the row if found, otherwise -1
 * Pre-condition: row is not null, size > 0, key is a character
 * */
int 
SearchLetter(char row[], int size, char key)
{
  int i;
  for (i = 0; i < size; i++) {
    if (row[i] == key) {
      return i;
    }
  }
  return -1;
}

/* generateUniqueRandomLetter generates a random letter that has not yet been used or is unique
 *
 * @param usedLetters - array of characters, representing the used letters
 * @return a unique random letter that is not inside the parameter usedLetters
 * Pre-condition: usedLetters is not null, rand() is seeded
 * */
char 
generateUniqueRandomLetter(char usedLetters[])
{
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

/* CreateBoard populates the board based on specified dimensions
 * @param board - 2D array of characters representing the board
 * @param *row  - an int pointer to the number of rows of the board
 * @param *col - an int pointer to the number of columns of the board
 * Pre-condition: board is not null, row > 0, col > 0, srand() seeds the random number generator
 * */
void 
CreateBoard(char board[][MAX_BOARD_SIZE], int *row, int *col)
{
  int i, j;
  srand(time(NULL));
  char usedLetters[100];
  char uniqueLetter;

  // generate random letters for the board
  for (i = 0; i < *row; i++) {
    memset(usedLetters, 0, sizeof usedLetters); // clear usedLetters array
    for (j = 0; j < *col; j++) {
      uniqueLetter = generateUniqueRandomLetter(usedLetters);
      usedLetters[j] = uniqueLetter;
      // push the letter to board if not yet used
      board[i][j] = uniqueLetter;
    }
  }
}

/* DisplayBoard displays the board
 * @param board - 2D array of characters representing the board
 * @param row - number of rows of the board
 * @param col - number of columns of the board
 * Pre-condition: board is not null, row > 0, col > 0
 * */
void 
DisplayBoard(char board[][MAX_BOARD_SIZE], int row, int col)
{
  int i, j;
  printf("\n");
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      printf("%c ", board[i][j]);
    }
    printf("\n");
  }
}

/* QuestionAnswerPhase asks the question trivia based on the random word selected 
 * and modifies the board based on the correctness of the user's answer
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * @param usedWordTracker - an array of strings that tracks the used words in the game
 * @param *numUsedWords - an int pointer to the number of used words in the game
 * @param board - 2D array of characters representing the board
 * @param letterIndex - the index of the letter selected in the currentRow
 * @param currentRow - represents the current row of the board
 * @return 1 if the question trivia is answered correctly, otherwise 0. If user wants to exit the game, return -1
 * Pre-condition: wordsDatabase is not null, numWords > 0, usedWordTracker is not null, numUsedWords > 0, board is not null, letterIndex >= 0, currentRow >= 0, rand() is seeded
 * */
int 
QuestionAnswerPhase(Words wordsDatabase, int *numWords, String20 usedWordTracker[], int *numUsedWords, char board[][MAX_BOARD_SIZE], int letterIndex, int currentRow)
{
  int i, j, randWordIndex, randClueIndex, alreadyUsed;
  String20 userAnswerInput;

  // loop until random word is unique or not already used (not included in usedWordTracker)
  do {
    randWordIndex = rand() % *numWords;
    alreadyUsed = 0; // assume word is not yet used
    for (i = 0; i < *numUsedWords; i++) {
      if (strcmp(wordsDatabase[randWordIndex].wordName, usedWordTracker[i]) == 0) {
        alreadyUsed = 1;
      }
    }

    // If the word has not been used, add it to the usedWordTracker array
    if (alreadyUsed == 0) {
      strcpy(usedWordTracker[*numUsedWords], wordsDatabase[randWordIndex].wordName);
      (*numUsedWords)++;
    }

  } while (alreadyUsed == 1);


  // START GAME: display a random clue/trivia (only 1) of the random word
  if (alreadyUsed == 0) {
    randClueIndex = rand() % wordsDatabase[randWordIndex].numOfClues;
    printf("\n");
    printf("TRIVIA: %s\n", wordsDatabase[randWordIndex].clues[randClueIndex].relation);
    printf("--> %s\n", wordsDatabase[randWordIndex].clues[randClueIndex].relationValue);
    printf("CORRECT ANSWER FOR DEBUGGING: %s\n", wordsDatabase[randWordIndex].wordName);

    printf("Enter your answer [enter 0 to exit game (auto lose)]: ");
    scanf("%20s", userAnswerInput);

    if (strcmp(userAnswerInput, "0") == 0) {
      return -1;
    }

    if (strcmp(userAnswerInput, wordsDatabase[randWordIndex].wordName) == 0) {
      board[currentRow][letterIndex] = '*'; // replace the letter with '*' if answered correctly
      return 1;
    }
    else {
      board[currentRow][letterIndex] = '-';
      return 0;
    }
  }          

  return -1;
}

/* isWin determines if the player wins based on contents in the 2D array of characters (2D strings).
 * if player answered atleast 1 question for each row in 2D array of characters loop through each row 
 * and check if there is at least one '*' (correct answer), if not, return 0 (not a win)
 *
 * @param board - 2D array of characters representing the board
 * @param row - number of rows of the board
 * @param col - number of columns of the board
 * @return 1 if the player wins, otherwise 0
 * Pre-condition: board is not null, row > 0, col > 0
 * */
int 
isWin(char board[][MAX_BOARD_SIZE], int row, int col)
{
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
      return 0;
    }
  }

  return 1;
}

/* CheckRowStatus returns 1 if a row has at least one '*', meaning it can proceed to next row, otherwise 0
 *
 * @param currentRow - array of characters representing the current row
 * @param col - number of columns of the board, which represents the number of letters in the row
 * @return 1 if the currentRow array has at least one '*', otherwise 0
 * Pre-condition: currentRow is not null, col > 0
 * */
int 
CheckRowStatus(char currentRow[], int col)
{
  int i;
  for (i = 0; i < col; i++) {
    if (currentRow[i] == '*') {
      return 1;
    }
  }

  return 0;
}

/* GamePhase is the main function that handles the game phase of the program
 *
 * @param *wordsDatabase - the array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * Pre-condition: no entries in wordsDatabase before starting the game since the Import will populate the database, letterInput is in uppercase, appropriate data types of inputs are used/given
 * */
void 
GamePhase(Words *wordsDatabase, int *numWords)
{
  int i = 0, j = 0, row = 0, col = 0, numUsedWords = 0;
  int letterIndex = -1, canProceedToNextRow = 1, status = 0, winFlag, exitFlag = 0;
  String20 usedWordTracker[MAX_WORDS];  // to be used in the game phase (to check if word has already been used in the game)
  char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
  char letterInput, continueGame;

  // initialize usedWordTracker array
  for (int n = 0; n < MAX_WORDS; n++) {
    usedWordTracker[n][0] = '\0';
  }

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
    memset(*wordsDatabase, 0, sizeof *wordsDatabase);
    *numWords = 0;
    return;
  }

  // only create board if all good
  CreateBoard(board, &row, &col);

  /******PLAYING PHASE*******/
  i = 0;
  while (i < row && canProceedToNextRow == 1 && exitFlag == 0) {
    printf("\n---------------------------------------\n");
    DisplayBoard(board, row, col);
    canProceedToNextRow = 0;
    j = 0;
    status = 0;
      while (j < col && status == 0 && exitFlag == 0) {

        printf("\n[0] to exit the game.\n");
        printf("[ ROW %d ] Choose the letter you want to guess in row %d: ", i + 1, i + 1);
        scanf(" %c", &letterInput);
        printf("\n");

        if (letterInput == '0') {
          printf("Exiting game...\n");
          exitFlag = 1;
          canProceedToNextRow = 0;
        } 
        else {
          while (letterInput == '*' || letterInput == '-') {
            printf("\nInvalid input. Please try again.\n");
            printf("[ ROW %d ] Choose the letter you want to guess in row %d: ", i + 1, i + 1);
            scanf(" %c", &letterInput);
          }

          letterIndex = SearchLetter(board[i], col, letterInput);

          // if letter does not exist
          while (letterIndex == -1) {
            printf("Letter does not exist in the current row. Please try again.\n");
            printf("[ ROW %d ] Choose the letter you want to guess in row %d: ", i + 1, i + 1);
            scanf(" %c", &letterInput);
            if (letterInput >= 'a' && letterInput <= 'z')
              printf("Letter must be in uppercase.\n");
            letterIndex = SearchLetter(board[i], col, letterInput);
          }

          // if letter exists, then proceed with the question (call database for word)
          if (letterIndex != -1 && letterInput != '*' && letterInput != '-') {
            status = QuestionAnswerPhase(*wordsDatabase, numWords, usedWordTracker, &numUsedWords, board, letterIndex, i);
          } // if letter exists

          if (status == -1) {
            // clear the database
            printf("Exiting game...\n");
            exitFlag = 1;
            canProceedToNextRow = 0;
          }
          else if (status == 0) {
            // display new board with the updated row that has '-'
            DisplayBoard(board, row, col);
            printf("\n");
            printf("Wrong answer!\n");
            j++;
            if (j != col) {
              printf("Choose another letter in the current row...\n");
            }
          }  
          else if (status == 1) {
            printf("\n");
            printf("Correct answer!\n");
            if (i != row - 1) {
              printf("Proceeding to the next row...\n");
            }
          }
        } // exitFlag == 0

      } // j col

    canProceedToNextRow = CheckRowStatus(board[i], col);
    if (canProceedToNextRow == 1) {
      i++;
    }
    else {
      canProceedToNextRow = 0; // exits loop
    }

  } // i row

  /******CHECK GAME STATUS IF WIN OR LOSE*******/
  winFlag = isWin(board, row, col);
  if (winFlag == 1) {
    printf("\nYou WIN!\n");
  } else {
    printf("\nYou LOSE!\n");
  }

  /******POST GAME*******/
  printf("Do you want to play again? [y/n]: ");
  scanf(" %c", &continueGame);

  while (continueGame != 'y' && continueGame != 'Y' && continueGame != 'n' && continueGame != 'N') {
    printf("Invalid input. Please try again.\n");
    printf("Do you want to play again? [y/n]: ");
    scanf(" %c", &continueGame);
  }

  if (continueGame == 'y' || continueGame == 'Y') {
    // clear the database before starting the game again
    memset(*wordsDatabase, 0, sizeof *wordsDatabase);
    *numWords = 0;
    GamePhase(wordsDatabase, numWords);
  }
  else if (continueGame == 'n' || continueGame == 'N') {
    // clear the database
    memset(*wordsDatabase, 0, sizeof *wordsDatabase);
    *numWords = 0;
    return;
  }
}

/* #############################################
 * ############### ADMIN PHASE ################
 * #############################################
 */

/* SortEntriesAlphabetically sorts the words in the database alphabetically in ascending order
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * Pre-condition: wordsDatabase is not null, numWords > 0
 * */
void 
SortEntriesAlphabetically(Words wordsDatabase, int *numWords)
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

/* DisplayAllWords displays all the words in the database
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * Pre-condition: wordsDatabase is not null, numWords > 0
 * */
void 
DisplayAllWords(Words wordsDatabase, int *numWords)
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

/* SearchWordIndex returns the index of the word in the database, otherwise -1 (-1 means unique, does not yet exist)
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * @param key - the word to search in the database
 * @return the index of the word in the database if found, otherwise -1
 * Pre-condition: wordsDatabase is not null, numWords > 0, key is a string
 * */
int 
SearchWordIndex(Words wordsDatabase, int *numWords, String20 key)
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

/* OverwriteWord overwrites the original word with the new word if the new word is unique, retains the clues of the original word
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * @param origWord - the original word to be overwritten
 * @param newWord - the new word to overwrite the original word
 * Pre-condition: wordsDatabase is not null, numWords > 0, origWord is a string, newWord is a string, assumes that word already exists in the database.
 * */
void 
OverwriteWord(Words wordsDatabase, int *numWords, String20 origWord, String20 newWord)
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

/* AddCluesAction adds clues to the word in the database
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param wordIndex - the index of the word in the database
 * Pre-condition: wordsDatabase is not null, wordIndex >= 0
 * */
void 
AddCluesAction(Words wordsDatabase, int wordIndex)
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

/* AddCluesUI is the "UI" function that handles the addition of clues to a word in the database based on the user input
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * Pre-condition: wordsDatabase is not null, numWords > 0
 * */
void 
AddCluesUI(Words wordsDatabase, int *numWords)
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

/* ViewClues displays the clues of the word in the database
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * Pre-condition: wordsDatabase is not null, numWords > 0
 * */
void 
ViewClues(Words wordsDatabase, int *numWords)
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

/* ViewWords displays the words in the database with its corresponding clues in alphabetical order.
 * It also allows the user to interactively navigate through the entries
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * Pre-condition: wordsDatabase is not null, numWords > 0, SortEntriesAlphabetically() sorts alphabetically
*/
void 
ViewWords(Words wordsDatabase, int *numWords)
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
        printf("\n-------End of the list.-------\n");
    }
    else if ((input == 'P' || input == 'p'))
    {
      if (i > 0)
        i--;
      else
        printf("\n-------Start of the list.-------\n");
    }
    else if (input == 'X' || input == 'x')
    {
      willRepeat = 0; // exit
    }
    else
    {
      printf("\nInvalid input. Please try again.\n");
    }
  } while (i < *numWords && willRepeat == 1);
}

/* AddWord adds a entry (word and clues) to the database. It also checks if the word already exists in the database.
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * Pre-condition: wordsDatabase is not null, numWords > 0, MAX_WORDS is the maximum number of words that can be added, AddCluesAction() handles the addition of clues to the word
 * */
void 
AddWord(Words wordsDatabase, int *numWords)
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

/* ModifyEntry modifies the word and/or clues in the database. It allows the user to modify the word and/or clues interactively.
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * Pre-condition: wordsDatabase is not null, numWords > 0, OverwriteWord() overwrites the original word with the new word if the new word is unique
 * */
void 
ModifyEntry(Words wordsDatabase, int *numWords)
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

/* DeleteWord deletes a word in the database, including its corresponding clues.
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * Pre-condition: wordsDatabase is not null, numWords > 0
 * */
void 
DeleteWord(Words wordsDatabase, int *numWords)
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

/* DeleteClue deletes a clue in the word in the database interactively by selecting the number representing the specific
 * clues (relation and relation value).
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * Pre-condition: wordsDatabase is not null, numWords > 0
 * */
void 
DeleteClue(Words wordsDatabase, int *numWords)
{
  int n, i, j, wordToDeleteIndex, indexClue, clueChoice;
  String20 input;
  String30 relation;

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

/* Import imports a file that contains the words and clues to the database.
 * It handles the population of the main database with the words and clues from the given text file.
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * Pre-condition: the FILE to import is a text file, MAX_WORDS is the maximum number of words that can be added, MAX_CLUES is the maximum number of clues that can be added to a word
 */
void 
Import(Words wordsDatabase, int *numWords)
{
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

  // STORING PHASE
  while (fgets(line, sizeof(line), file) != NULL) {

    // handle empty line (<nextline> or \n), indicates that next line will be a word
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

  // COMPARING PHASE, assigns what to be overwritten
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

      // OVERWRITING PHASE
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

/* Export exports the data entries to a text file. It allows the user to save the data entries to a file.
 * The data entries are also sorted alphabetically before exporting.
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * Pre-condition: the FILE specified where the data will be saved is a text file, wordsDatabase is not null, numWords > 0, SortEntriesAlphabetically() sorts alphabetically
 * */
void 
Export(Words wordsDatabase, int *numWords)
{
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

/* AdminMenu is the main interface for the admin phase.
 *
 * @param wordsDatabase - an array that serves as the main database of words
 * @param *numWords - an int pointer to the number of words in the database
 * Pre-condition: the input is an integer from 0 to 9 only
 * */
void 
AdminMenu(Words *wordsDatabase, int *numWords)
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
      // erase the database, since export is the only way to save
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

int 
main()
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
      memset(wordsDatabase, 0, sizeof *wordsDatabase);
      numWords = 0;
      GamePhase(&wordsDatabase, &numWords);
      break;
    case 2:
      AdminMenu(&wordsDatabase, &numWords);
      break;
    default:
      printf("Invalid input. Please try again.\n");
      break;
    }
  }
  return 0;
}

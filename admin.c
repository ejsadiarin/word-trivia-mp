
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include "SADIARIN_wordTrivia.h"

#define MAX_BOARD_SIZE 10
#define MIN_BOARD_SIZE 3
#define MAX_WORDS 150
#define MIN_WORDS 9 // 9 to create the minimum 3x3 board
#define MAX_CLUES 10

typedef char String20[21]; // data type of the answers
typedef char String30[31];

typedef struct
{
  String30 relation;
  String30 relationValue;
} CluesType;

typedef struct
{
  String20 wordName;
  CluesType clues[MAX_CLUES];
  int numOfClues;
} WordType;

typedef WordType Words[MAX_WORDS]; // this is the "database"

typedef struct
{
  int row;
  int col;
  char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
} BoardType;

/******ADMIN PHASE*******/

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

    // Handle next/previous options
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

  // int i, j, index;
  // char input;
  // int exitFlag = 0;
  // if (*numWords == 0) {
  //   printf("No words in the database. Please add words first.\n");
  //   return;
  // }
  // SortEntriesAlphabetically(wordsDatabase, numWords);
  // for (i = 0; i < *numWords; i++) {
  //   printf("Object: %s\n", wordsDatabase[i]->wordName);
  //   for (j = 0; j < wordsDatabase[i]->numOfClues; j++) {
  //     printf("  %s: %s\n", wordsDatabase[i]->clues[j].relation, wordsDatabase[i]->clues[j].relationValue);
  //   }
  //   printf("\nPress [N] for next, [P] for previous, [X] to exit: ");
  //   scanf(" %c", &input);
  //   if (input == 'X' || input == 'x') {
  //     return;
  //   }
  // }
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
    printf("Enter the choice you want to modify: ");
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
 * TODO: The data in the text file is assumed to be in the format indicated in Export.
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

  // ask for filename
  printf("\nEnter filename of your words (should end with .txt): ");
  scanf("%30s", filename);
  printf("\n");

  file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening file while reading.\n");
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
          printf("Current Word Entry: %s retained.\n", wordsDatabase[origIndex].wordName);
        } else {
          willOverwrite = -1;
          printf("Invalid input.\n");
          printf("Current Word Entry: %s retained.\n", wordsDatabase[origIndex].wordName);
        }
      }
      // if unique word, if (origIndex == -1)
      else {
        // add new unique word and its associated clues
        willOverwrite = 0;
      }

      // HACK: OVERWRITING PHASE
      if (willOverwrite == 1) {

        if (importedWordsDatabase[i].numOfClues > MAX_CLUES) {
          printf("Clues maximum limit (10) reached. Skipping word entry.\n");
        } else {
          wordsDatabase[origIndex] = importedWordsDatabase[i]; // NOTE: do this instead of below?
          printf("Word successfully overwritten with new data.\n");
        }
      }
      // if not overwriting (new word entry)
      else { // willOverwrite == 0
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

void ExportDataToFile(Words wordsDatabase, int *numWords) {
  SortEntriesAlphabetically(wordsDatabase, numWords);
}

// Menu for the Admin Phase
void AdminMenu(Words *wordsDatabase, int *numWords)
{
  int input, exitFlagToMainMenu = 0;
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
      // ExportDataToFile();
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
  Words wordsDatabase; // main database that admins can manipulate

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
      // GamePhase(&wordsDatabase, &numWords);
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

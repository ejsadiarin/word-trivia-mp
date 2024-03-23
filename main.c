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

#define MAX_BOARD_SIZE 10
#define MIN_BOARD_SIZE 3
#define MAX_WORDS 150
#define MIN_WORDS 9 // 9 to create the minimum 3x3 board
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

typedef struct {
  int row;
  int col;
  char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
} BoardType;

int isUnique(Words *wordsDatabase) {
  int i, j, uniqueFlag, count;

  count = 0;      // have countWords in the Words struct array
  uniqueFlag = 1; // assume all words are unique

  for (i = 0; i < count; i++) {
    for (j = i + 1; j < count; j++) {
      if (strcmp(wordsDatabase[i]->wordName, wordsDatabase[j]->wordName) == 0) {
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

// TODO: call in createBoard()
// int findMultiples(int Words) {
//   int i, j;
//   for (i = 1; i <= Words; i++) {
//     for (j = i; j <= num; j++) {
//       if (i * j == num) {
//       }
//     }
//   }
// }

/*
 * Returns the index of the key, otherwise -1
 *
 * FIX: (1) to be called when selecting letter from board, (2) searching if word
 * (entry) exists in "database"
 * */
int Search(char array[], int size, char key) {
  int i;
  for (i = 0; i < size; i++) {
    if (array[i] == key) {
      return i;
    }
  }
  return -1;
}

/*
 * Populates the board based on the Words in the file.
 * --> asks for dimension of the board
 * --> asks user for filename (loading text file of words and clues)
 * --> generate random latters but unique for each row
 * --> make sure to have enough Words in database for the grid board
 * */
void createBoard(char board[][MAX_BOARD_SIZE], int *row, int *col) {
  char filename[50];
  int i, j;
  srand(time(NULL));
  char usedLetters[MAX_BOARD_SIZE];
  char uniqueLetter;

  // generate random letters for the board
  for (i = 0; i < *row; i++) {
    for (j = 0; j < *col; j++) {
      uniqueLetter = generateUniqueRandomLetter(usedLetters, j);
      usedLetters[j] = uniqueLetter;
      // push the letter to board if not yet used
      board[i][j] = uniqueLetter;
      printf("%c ", board[i][j]);
    }
    printf("\n");
  }
}

int getMaxBoardSize(int numWords) {}

/*
 * --> ask for input letter
 * --> call Search() to check if the letter exists in the current row in the
 * board
 * --> if exists, then proceed with the question (call database for word)
 * --> NOTE: this is to be called for each letter in the board
 * */
void rowQuestionPhase(char letters[], int numOfLettersInRow,
                      char letterTracker[]) {
  int i;
  char input;
  for (i = 0; i < numOfLettersInRow; i++) {
    printf("[ ROW %d ] Choose the letter you want to guess in row %d: ", i + 1,
           i + 1);
    scanf("%c", &input);
    // convert input to uppercase
    if (input >= 'a' && input <= 'z') {
      input = input - 32;
    }

    while (input == '*' || input == '-') {
      printf("\nInvalid input. Please try again.\n");
      rowQuestionPhase(letters, numOfLettersInRow, letterTracker);
    }

    if (letters[i] == input && letters[i] != letterTracker[i] && input != '*' &&
        input != '-') {
      // proceed with the question (call database for word)
      // TODO: generateUniqueQuestion() - if word exists in the board (current
      // game phase)
      letterTracker[i] = letters[i];
    } else {
      printf("Input does not exist in the current row. Please try again.\n");
    }
  }
}

// at most 10 clues per word (so word struct?)
// there can be at most 150 Words/words (answers in the game), but a word can
// have at most 10 clues

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
int checkRowStatus(char rowElems[], int *col) {
  // check if col == numOfWrong (which is '-');
  int i, canProceed = 0;
  for (i = 0; i < *col; i++) {
    if (rowElems[i] == '*') {
      canProceed = 1;
      return canProceed;
    }
  }

  return canProceed;
}

void GamePhase(Words *wordsDatabase, int *numWords) {
  int i = 0, j = 0;
  // NOTE: for testing
  // int row = 10;
  // int col = 10;
  int row;
  int col;
  String30 words_filename;
  String30 clues_filename;
  FILE *init_wordFile;
  FILE *init_cluesFile;
  char letterTracker[MAX_BOARD_SIZE]; // unique letter tracker (stores all
                                      // "used" letters in the row)
  String20 wordTracker[150]; // to be used in the game phase (to check if word
                             // has already been used in the game)

  /******INITIALIZE*******/
  // (ask for filename) - initial file
  // printf("\nEnter filename of your words (should end with .txt): ");
  // scanf("%s", words_filename);
  // printf("\n");
  // init_wordFile = fopen(words_filename, "r"); // or "append"? since admin can
  // have initial words already stored in wordsDatabase if (init_wordFile ==
  // NULL) {
  //   printf("Words File not found. Please try again.\n");
  //   GamePhase(wordsDatabase, numWords);
  // }

  // is clues file separated from the words file?
  printf("\nEnter filename of your clues (should end with .txt): ");
  scanf("%s", clues_filename);
  printf("\n");
  init_cluesFile = fopen(clues_filename, "r"); // or "append"? since admin can have initial words already stored in wordsDatabase
  if (init_cluesFile == NULL) {
    printf("clues File not found. Please try again.\n");
    GamePhase(wordsDatabase, numWords);
  }
  // TODO: do i need to check for the clues count? how?

  // FIX: then store it in the Words struct array (should be of type WordType) -
  // does the imported file have clues already included?
  // --> change condition to numWords < MAX_WORDS if using numWords++ inside
  // while loop numWords = current count of words in the database if already has
  // words in wordsDatabase, then fscanf starting from the current count of
  // words in the database
  while (*numWords < MAX_WORDS &&
         fscanf(init_wordFile, "%s", wordsDatabase[*numWords]->wordName) !=
             EOF) {
    numWords++; // make sure that numWords = 0 at the start
  }

  // make sure to have enough Words in database for the grid board
  // - should be max: 150 and min: 9 (to create the minimum 3x3 board)
  if (*numWords > MAX_WORDS || *numWords < MIN_WORDS) {
    printf("Invalid number of Words (MAX: 150, MIN: 1). Please try again.\n");
    // recursion - ask for filename again
    GamePhase(wordsDatabase, numWords);
  }

  // ask user for dimensions of the board
  // NOTE: uncomment if not testing
  printf("\nEnter row of the board (min is 3, max is 10): ");
  scanf("%d", &row);
  printf("\nEnter col of the board (min is 3, max is 10): ");
  scanf("%d", &col);
  // check if row and col are within the range (input validation)
  while (row < MIN_BOARD_SIZE || row > MAX_BOARD_SIZE || col < MIN_BOARD_SIZE ||
         col > MAX_BOARD_SIZE) {
    printf("Invalid board size. Please try again.\n");
    printf("\nEnter row of the board (min is 3, max is 10): ");
    scanf("%d", &row);
    printf("\nEnter col of the board (min is 3, max is 10): ");
    scanf("%d", &col);
  }

  char board[row][col];

  if (isUnique(wordsDatabase)) {
    createBoard(board, &row, &col);
  } else {
    printf("Words in the database are not unique (have duplicates). Please try "
           "again.\n");
    GamePhase(wordsDatabase, numWords);
  }

  /******PLAYING PHASE*******/
  // TODO: select letter from board, then ask question (calls questionPhase())

  for (i = 0; i < row; i++) {
    // --> loop the board rows
    // --> rowQuestionPhase(board[i], col, letterTracker
    // ) has Q&A:
    // --> - then Search() if input char is in the current row in the board
    // --> - if yes, then proceed with the question (call database for word)
    // --> ensure word/answer is unique (not yet used in the game/grid) - push
    // to wordTracker array
    // --> if answered correctly, replace the letter with '*', otherwise '-'
    // (calls replaceLetter())
  }
  // TODO: check every row with checkRowStatus()

  /******CHECK GAME STATUS IF WIN OR LOSE*******/
  isWin(board, row, col);
}

/******ADMIN PHASE*******/
  // b. Display all words
  // c. View Clues
  // d. View Words
  // e. Determine if word already exists in the array
  // f. Add Word
  // g. Add Clues
void SortAlphabetical(Words *wordsDatabase, int *numWords) {
  int i, j;
  WordType temp;
  for (i = 0; i < *numWords; i++) {
    for (j = i + 1; j < *numWords; j++) {
      if (strcmp(wordsDatabase[i]->wordName, wordsDatabase[j]->wordName) > 0) {
        temp = *wordsDatabase[i];
        *wordsDatabase[i] = *wordsDatabase[j];
        *wordsDatabase[j] = temp;
      }
    }
  }
}

void DisplayAllWords(Words *wordsDatabase, int *numWords) {
  int i;
  SortAlphabetical(wordsDatabase, numWords);
  for (i = 0; i < *numWords; i++) {
    printf("%s\n", wordsDatabase[i]->wordName);
    // printf("%s ", wordsDatabase[i]->wordName);
    // if (i == 3) {
    //   printf("\n");
    // }
  }
}

/*
 *
 * Returns the index of the word in the database, otherwise -1
 * */
int SearchWord(Words *wordsDatabase, int *numWords, char key[]) {
  int i;
  for (i = 0; i < *numWords; i++) {
    if (strcmp(key, wordsDatabase[i]->wordName) == 0) {
      return i;
    }
  }
  return -1;
}

/*
 * TODO: ViewClues()
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
 *
 * */
void ViewClues(Words *wordsDatabase, int *numWords) {
  int i, j, index, exitFlag = 0;
  char word[20];

  printf("\n--------------------------------------------------------\n");
  DisplayAllWords(wordsDatabase, numWords);

  do {
    printf("\n[0] - Go back to the menu\n");
    printf("\n[1] - Display all words again\n");
    printf("Enter the word you want to view the clues on: ");
    scanf("%s", word);
    printf("\n");

    if (strcmp(word, "0") == 0) {
      exitFlag = 1;
    }

    if (strcmp(word, "1") == 0) {
      DisplayAllWords(wordsDatabase, numWords);
    }
  
    index = SearchWord(wordsDatabase, numWords, word);
    if (index >= 0) {
      printf("Object: %s\n", wordsDatabase[index]->wordName);
      for (j = 0; j < wordsDatabase[index]->numOfClues; j++) {
        printf("  %s: %s\n", wordsDatabase[index]->clues[j].relation, wordsDatabase[index]->clues[j].relationValue);
      }
    } 
    else {
      printf("Word: %s does not exist in the database.\n", word);
    }

    // for (i = 0; i < *numWords; i++) {
    //   if (strcmp(word, wordsDatabase[i]->wordName) == 0) {
    //     printf("Object: %s\n", wordsDatabase[i]->wordName);
    //     for (j = 0; j < wordsDatabase[i]->numOfClues; j++) {
    //       printf("  %s: %s\n", wordsDatabase[i]->clues[j].relation, wordsDatabase[i]->clues[j].relationValue);
    //     }
    //   } else {
    //     printf("Word: %s does not exist in the database.\n", word);
    //   }
    // }

  } while (exitFlag == 0);

}

/*
    Provide a listing of all words (in alphabetical order). The list of trivia of each word should also be
    shown. Display each word one at a time until all entries have been displayed. Provide a way for
    the user to view the next or previous word or exit the view (i.e., press ‘N’ for next, ‘P’ for previous,
    ‘X’ to end the display and go back to the menu).
 * TODO: ViewWords()
*/
void ViewWords(Words *wordsDatabase, int *numWords) {
  int i = 0, j, exitFlag = 0;
  char input;

  SortAlphabetical(wordsDatabase, numWords);

  do {
    // show first word (alphabetical order)
    while (i < *numWords) {
      printf("Object: %s\n", wordsDatabase[i]->wordName);
      for (j = 0; j < wordsDatabase[i]->numOfClues; j++) {
        printf("  %s: %s\n", wordsDatabase[i]->clues[j].relation, wordsDatabase[i]->clues[j].relationValue);
      }

      // options:
      printf("\n[N] - Next, [P] - Previous, [X] - Exit\n");
      printf("Enter your choice: ");
      scanf(" %c", &input);
      printf("\n");

      // convert input to uppercase
      if (input >= 'a' && input <= 'z') {
        input = input - 32;
      }

      // handle invalid input
      while (input != 'N' && input != 'P' && input != 'X') {
        printf("Invalid input. Please try again.\n");
        printf("\n[N] - Next, [P] - Previous, [X] - Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &input);
      }

      // handle cases at start and end of the list
      while (i == 0 && input == 'P') {
        printf("\nNo previous word. Please try again.\n");
        printf("\n[N] - Next, [X] - Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &input);
      } 
      while (i == *numWords - 1 && input == 'N') {
        printf("\nNo next word. Please try again.\n");
        printf("\n[P] - Previous, [X] - Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &input);
      }
        

      if (input == 'N') {
        // continue
        i++;
      } 
      else if (input == 'P') {
        // continue
        i--;
      } 
      else if (input == 'X') {
        // exit
        exitFlag = 1;
      }
    }
  } while (exitFlag == 0 || i < *numWords);

}

void AddWord(Words *wordsDatabase, int *numWords) {
  String20 input;

  // check if there is still space in the database
  if (*numWords == MAX_WORDS) {
    printf("Database is full. Cannot add more words.\n");
    return;
  }

  printf("\nEnter word to add: ");
  scanf("%s", input);

  // check if word already exists in the database
  if (SearchWord(wordsDatabase, numWords, input) > 0) {
    printf("\nWord already exists in the database.\n");
    return;
  }

  strcpy(wordsDatabase[*numWords]->wordName, input);
  (*numWords)++;
}

void AddClues(Words *wordsDatabase, int *numWords) {
  int i, j, index, willRepeat = 0;
  char yn;
  String20 input;
  String30 relation;
  String30 relationValue;

  printf("\nEnter word to add clues to: ");
  scanf("%s", input);

  // check if word exists in the database
  index = SearchWord(wordsDatabase, numWords, input);
  if (index < 0) {
    printf("Word does not exist in the database.\n");
    return;
  }

  do {
    // add clues to the word
    printf("\nEnter relation: ");
    scanf("%30s", relation);
    printf("\nEnter relation value: ");
    scanf("%30s", relationValue);
    strcpy(wordsDatabase[index]->clues[wordsDatabase[index]->numOfClues].relation, relation);
    strcpy(wordsDatabase[index]->clues[wordsDatabase[index]->numOfClues].relationValue, relationValue);
    wordsDatabase[index]->numOfClues++;

    printf("Added new clue to word %s!\n", input);

    // ask if user wants to add more clues
    printf("\nDo you want to add more clues? [y/n]: ");
    scanf(" %c", &yn);
    if (yn == 'y' || yn == 'Y') {
      willRepeat = 1;
    } else if (yn == 'n' || yn == 'N') {
      willRepeat = 0;
    } else {
      printf("Invalid input. Exiting...\n");
      willRepeat = 0;
    }
  } while (willRepeat == 1);

}

void ModifyEntry(Words *wordsDatabase, int *numWords) {
  int i, index;
  String20 input;
  printf("\nEnter word to modify: ");
  scanf("%s", input);
  // check if word exists in the database
  index = SearchWord(wordsDatabase, numWords, input);
  if (index < 0) {
    printf("Word does not exist in the database.\n");
    return;
  }
  printf("\nEnter new word: ");
  scanf("%s", wordsDatabase[index]->wordName);
  printf("Word successfully modified.\n");
}

void DeleteWord(Words *wordsDatabase, int *numWords) {
  int i, index;
  String20 input;
  printf("\nEnter word to delete: ");
  scanf("%s", input);
  // check if word exists in the database
  index = SearchWord(wordsDatabase, numWords, input);
  if (index < 0) {
    printf("Word does not exist in the database.\n");
    return;
  }
  for (i = index; i < *numWords - 1; i++) {
    *wordsDatabase[i] = *wordsDatabase[i + 1];
  }
  (*numWords)--;
  printf("Word successfully deleted.\n");
}

void DeleteClue(Words *wordsDatabase, int *numWords) {
  int i, j, index, indexClue;
  String20 input;
  String30 relation;
  printf("\nEnter word to delete clue from: ");
  scanf("%s", input);
  // check if word exists in the database
  index = SearchWord(wordsDatabase, numWords, input);
  if (index < 0) {
    printf("Word does not exist in the database.\n");
    return;
  }
  printf("\nEnter relation to delete: ");
  scanf("%30s", relation);
  for (i = 0; i < wordsDatabase[index]->numOfClues; i++) {
    if (strcmp(relation, wordsDatabase[index]->clues[i].relation) == 0) {
      for (j = i; j < wordsDatabase[index]->numOfClues - 1; j++) {
        wordsDatabase[index]->clues[j] = wordsDatabase[index]->clues[j + 1];
      }
      wordsDatabase[index]->numOfClues--;
      printf("Clue successfully deleted.\n");
      return;
    }
  }
  printf("Clue does not exist in the database.\n");
}

/*
 * TODO:
 * The data in the text file is assumed to be in the format indicated in Export.
 */
void ImportDataFromFile(Words *wordsDatabase, int *numWords) {
  FILE *file;
  char filename[50];
  char line[100];
  WordType temp_entry;
  int i, willOverwrite = 0;
  char input;

  // ask for filename
  printf("\nEnter filename of your words (should end with .txt): ");
  scanf("%s", filename);
  printf("\n");

  file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening file while reading.\n");
    return;
  }

  while (fgets(line, sizeof(line), file) != NULL) {
    // remove trailing \n
    line[strlen(line) - 1] = '\0';

    // TODO:
    // add/"append" imported data to the wordsDatabase
    // if words already exist in wordsDatabase, then:
    // --> ask if want existing data to be overwritten
    //    - if yes, then overwrite word to the existing word in wordsDatabase.
    //    - if no, then retain word in wordsDatabase
    //    - if word from imported file is unique, then it will be
    //    added/"appended"

    // FIX: validate this: identify word
    if (strncmp(line, "Object:", 7) == 0) {
      // extract word as temporary for validation
      sscanf(line, "Object: %s", temp_entry.wordName);

      // check if already exists in wordsDatabase
      for (i = 0; i < *numWords; i++) {
        // if exist then options...
        if (strcmp(temp_entry.wordName, wordsDatabase[i]->wordName) == 0) {
          printf("%s already exists in the database. Override? [y/n]", temp_entry.wordName);
          scanf(" %c", &input);
          if (input == 'y' || input == 'Y') {
            willOverwrite = 1;
            // sscanf(line, "Object: %s", wordsDatabase[i]->wordName);
            strcpy(wordsDatabase[i]->wordName, temp_entry.wordName); // redundant?
            // also handle the overwriting of clues
            printf("Word successfully overwritten with new data.\n");
          } else if (input == 'n' || input == 'N') {
            printf("Current Word %s retained.\n", wordsDatabase[i]->wordName);
          } else {
            printf("Invalid input.\n");
            printf("Current Word %s retained.\n", wordsDatabase[i]->wordName);
          }
        }
      }

      // If word does not exist, then add it to actual wordsDatabase
      if (i == *numWords) {
        strcpy(wordsDatabase[*numWords]->wordName, temp_entry.wordName);
        (*numWords)++;
      }

    }
    // identify relation and relation value
    else {
      if (*numWords == 0) {
        printf("Clues found before any word entry. Closing file...\n");
        fclose(file);
        return;
      }

      // handle empty line (<nextline>)
      if (line[0] == '\0') {
        // printf("Empty line found. Skipping...\n");
        if (willOverwrite == 1) willOverwrite = 0;
        temp_entry.numOfClues = 0;
      } 
      // handle clues
      else {
        if (willOverwrite) {
          sscanf(line, "%s %s", temp_entry.clues->relation, temp_entry.clues->relationValue);
          temp_entry.numOfClues++;
          if (temp_entry.numOfClues > MAX_CLUES) {
            willOverwrite = 0;
            // printf("Clues count for the current word exceeds the maximum limit. Skipping current clue...\n");
          } 
          if (temp_entry.numOfClues <= MAX_CLUES) {
            printf("Clues successfully overwritten with new data.\n");
          }

        } 
        // if not overwriting (new word entry), then add its clues
        else {
          sscanf(line, "%s %s", temp_entry.clues->relation, temp_entry.clues->relationValue);
          temp_entry.numOfClues++;
          // if max clues is reached (> 10) then skip, but keep previous clues
          if (temp_entry.numOfClues <= MAX_CLUES) {
            strcpy(wordsDatabase[*numWords]->clues[wordsDatabase[*numWords]->numOfClues].relation, temp_entry.clues->relation);
            strcpy(wordsDatabase[*numWords]->clues[wordsDatabase[*numWords]->numOfClues].relationValue, temp_entry.clues->relationValue);
            wordsDatabase[*numWords]->numOfClues++;
          }
        }
      }
    }
  }
  fclose(file);
}

void ExportDataToFile() {}

// Menu for the Admin Phase
// each word has at most 10 clues (relations):
void AdminMenu(Words *wordsDatabase, int *numWords) {
  int input, exitFlagToMainMenu = 0;
  while (!exitFlagToMainMenu) {
    printf("\n--------------Admin Menu--------------\n");
    printf("[1] Add Word \n");
    printf("[2] Add clues\n");
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
      // AddClues();
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
  int numWords = 0;
  Words wordsDatabase; // main database that admins can manipulate
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
      AdminMenu(&wordsDatabase, &numWords); // have a temporary database for the admin phase then it will only be saved to the main database if it is "exported" (called Export() function)
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

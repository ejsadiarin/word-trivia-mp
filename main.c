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

typedef char String20[21]; // data type of the answers
typedef char String30[31];

typedef struct {
  String30 relation;
  String30 relationValue;
} TriviaType;

typedef struct {
  String20 wordName;
  TriviaType trivia[10];
} WordType;

typedef WordType Words[150]; // this is the "database"

typedef struct {
  int row;
  int col;
  char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
} BoardType;

int isUnique(Words words) {
  int i, j, uniqueFlag, count;

  count = 0; // have countWords in the Words struct array
  uniqueFlag = 1; // assume all words are unique

  for (i = 0; i < count; i++) {
    for (j = i + 1; j < count; j++) {
      if (strcmp(words[i].wordName, words[j].wordName) == 0) {
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
 * NOTE: (1) to be called when selecting letter from board, (2) searching if word (entry) exists in "database"
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
 * --> asks user for filename (loading text file of words and trivia)
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

int getMaxBoardSize(int numWords) {
}

/*
 * --> ask for input letter
 * --> call Search() to check if the letter exists in the current row in the board
 * --> if exists, then proceed with the question (call database for word)
* --> NOTE: this is to be called for each letter in the board
 * */
void rowQuestionPhase(char letters[], int numOfLettersInRow, char letterTracker[]) {
  int i;
  char input;
  for (i = 0; i < numOfLettersInRow; i++) {
    printf("[ ROW %d ] Choose the letter you want to guess in row %d: ", i, i);
    scanf("%c", &input);
    if (letters[i] == input && letters[i] != letterTracker[i] && input != '*' && input != '-') {
      // proceed with the question (call database for word)
      // TODO: generateUniqueQuestion() - if word exists in the board (current game phase)
      letterTracker[i] = letters[i];
    }
  }
}



// at most 10 trivia per word (so word struct?)
// there can be at most 150 Words/words (answers in the game), but a word can
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

void gamePhase() {
  int i = 0, j = 0; 
  // NOTE: for testing
  int numWords = 12;
  // int row = 10;
  // int col = 10;
  int row;
  int col;
  String30 filename;
  FILE *initialFile;
  char letterTracker[MAX_BOARD_SIZE]; // unique letter tracker (stores all "used" letters in the row)
  String20 uniqueWordTracker[150]; // store Words->wordName here
  Words wordsDatabase; // main database that admins can manipulate

  /******INITIALIZE*******/
  //  (ask for filename) - initial file
  printf("Enter filename of your words (should end with .txt): ");
  scanf("%s", filename);
  printf("\n");
  initialFile = fopen(filename, "r");
  if (initialFile == NULL) {
    printf("File not found. Please try again.\n");
    gamePhase();
  }
  // FIX: then store it in the Words struct array (should be of type WordType) - does the imported file have trivia already included?
  // --> change condition to numWords < MAX_WORDS if using numWords++ inside while loop
  while (i < MAX_WORDS && fscanf(initialFile, "%s", wordsDatabase[i].wordName) != EOF) {
    i++;
  // numWords++; // make sure that numWords = 0 at the start
  }
  numWords = i; // remove this if using numWords++ inside while loop

  // --> make sure to have enough Words in database for the grid board
  // - should be max: 150
  while (numWords > MAX_WORDS || numWords < MIN_WORDS) {
    printf("Invalid number of Words (MAX: 150, MIN: 1). Please try again.\n");
    // recursion - ask for filename again
    gamePhase();
  }


  // ask user for dimensions of the board
  // NOTE: uncomment if not testing
  printf("\nEnter row of the board (min is 3, max is 10): ");
  scanf("%d", &row);
  printf("\nEnter col of the board (min is 3, max is 10): ");
  scanf("%d", &col);
  // check if row and col are within the range (input validation)
  while (row < MIN_BOARD_SIZE || row > MAX_BOARD_SIZE || col < MIN_BOARD_SIZE || col > MAX_BOARD_SIZE) {
    printf("Invalid board size. Please try again.\n");
    printf("\nEnter row of the board (min is 3, max is 10): ");
    scanf("%d", &row);
    printf("\nEnter col of the board (min is 3, max is 10): ");
    scanf("%d", &col);
  }

  char board[row][col];

  // TODO: make sure to have enough Words in database for the grid board
  if (isUnique(words)) {
    createBoard(board, &row, &col);
  }

  /******PLAYING PHASE*******/
  // TODO: select letter from board, then ask question (calls questionPhase())

  for (i = 0; i < row; i++) {
    // --> ensure word/answer is unique (not yet used in the game/grid) - push to uniqueWordTracker array
    // --> rowQuestionPhase() has Q&A:
    // --> - then Search() if input char is in the current row in the board
    // --> - if yes, then proceed with the question (call database for word)
    // --> if answered correctly, replace the letter with '*', otherwise '-' (calls replaceLetter())
  }
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

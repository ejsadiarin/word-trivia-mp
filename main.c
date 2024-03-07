/*********************************************************************************************************
 This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
 learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
 program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
 otherwise plagiarized the work of other students and/or persons.
                                                                                  Edwin M. Sadiarin Jr., DLSU ID#12323004
 *********************************************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAX_BOARD_SIZE 10
#define MIN_BOARD_SIZE 3

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


// TODO: the char array to be displayed
struct Board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
// typedef struct {
//   Word20 wordName;
//   TriviaType trivia[10];
// } BoardInterface;



// typedef WordType Board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

/*
 * Populates the board based on the entries in the file.
 * --> asks for dimension of the board
 * --> asks user for filename (loading text file of words and trivia)
 * --> generate random latters but unique for each row
 * --> make sure to have enough entries in database for the grid board
 * */
void createBoard() {
  int row, col;
  char filename[50];

  printf("\nEnter row of the board (min is 3, max is 10): ");
  scanf("%d", &row);
  printf("\nEnter col of the board (min is 3, max is 10): ");
  scanf("%d", &col);

  // check if row and col are within the range
  while (row < MIN_BOARD_SIZE || row > MAX_BOARD_SIZE || col < MIN_BOARD_SIZE || col > MAX_BOARD_SIZE) {
    printf("Invalid board size. Please try again.\n");
    printf("\nEnter row of the board (min is 3, max is 10): ");
    scanf("%d", &row);
    printf("\nEnter col of the board (min is 3, max is 10): ");
    scanf("%d", &col);
  }

  // ask for filename
  // generate random letters in the row
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      
    }
  }
  // make sure to have enough entries in database for the grid board
  // have displayBoard() in the end
}

void generateRowLetters(WordType word[], int size) {
  int i, j;
  // word[0].wordName = "apple";


}
// at most 10 trivia per word (so word struct?)
// there can be at most 150 entries/words (answers in the game), but a word can have at most 10 trivia/clues

// Determine if the player wins based on contents in the 2D array of characters (2D strings).
int checkWinningConditions(Board) {
  // given the 2d array of characters (array of strings), search for *, if found

  // if 1 player wins, otherwise (0) not;
  // WINS: if player answered atleast 1 question for each row in 2D array of characters
  // loop through each row and check if there is at least one * (correct answer), if not, return 0 (not a win)

  return 0;
}

// Determine if the game is over based on the contents in the 2D array of characters.
// calls checkWinningConditions()
int IsGameOver() {

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

int main() 
{
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

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

// Game Phase Functions
int isUnique(Words *wordsDatabase);
char generateUniqueRandomLetter(char usedLetters[], int size);
int Search(char array[], int size, char key);
void createBoard(char board[][MAX_BOARD_SIZE], int *row, int *col);
int getMaxBoardSize(int numWords);
void rowQuestionPhase(char letters[], int numOfLettersInRow, char letterTracker[]);
int isWin(char board[][MAX_BOARD_SIZE], int row, int col);
int checkRowStatus(char rowElems[], int *col);
void GamePhase(Words *wordsDatabase, int *numWords);

// Admin Phase Functions
void SortAlphabetical(Words *wordsDatabase, int *numWords);
void DisplayAllWords(Words *wordsDatabase, int *numWords);
int SearchWord(Words *wordsDatabase, int *numWords, char key[]);
void ViewClues(Words *wordsDatabase, int *numWords);
void ViewWords(Words *wordsDatabase, int *numWords);
void AddWord(Words *wordsDatabase, int *numWords);
void AddClues(Words *wordsDatabase, int *numWords);
void ModifyEntry(Words *wordsDatabase, int *numWords);
void DeleteWord(Words *wordsDatabase, int *numWords);
void ImportDataFromFile(Words *wordsDatabase, int *numWords);
void ExportDataToFile(Words *wordsDatabase, int *numWords);
void AdminMenu(Words *wordsDatabase, int *numWords);

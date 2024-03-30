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

// Game Phase Functions
int isUniqueLetter(char lettersContext[], int letterCountInRow);
char generateUniqueRandomLetter(char usedLetters[], int size);
int SearchLetter(char array[], int size, char key);
void CreateBoard(char board[][MAX_BOARD_SIZE], int *row, int *col);
int RandWordQuestion(Words wordsDatabase, int numWords, String20 usedWordTracker[], int *numUsedWords);
int isWin(char board[][MAX_BOARD_SIZE], int row, int col);
int CheckRowStatus(char currentRow[], int col);
void GamePhase(Words *wordsDatabase, int *numWords);

// Admin Phase Functions
void SortEntriesAlphabetically(Words wordsDatabase, int *numWords);
void DisplayAllWords(Words wordsDatabase, int *numWords);
int SearchWordIndex(Words wordsDatabase, int *numWords, String20 key);
int SearchClueIndex(CluesType clues[], int *numOfClues, String30 key);
void OverwriteWord(Words wordsDatabase, int *numWords, String20 origWord, String20 newWord);
void OverwriteClue(CluesType clues[], int *numOfClues, String30 newClue, String30 newClueValue);
void AddCluesAction(Words wordsDatabase, int wordIndex);
void AddCluesUI(Words wordsDatabase, int *numWords);
void ViewClues(Words wordsDatabase, int *numWords);
void ViewWords(Words wordsDatabase, int *numWords);
void AddWord(Words wordsDatabase, int *numWords);
void ModifyEntry(Words wordsDatabase, int *numWords);
void DeleteWord(Words wordsDatabase, int *numWords);
void DeleteClue(Words wordsDatabase, int *numWords);
void Import(Words wordsDatabase, int *numWords);
void Export(Words wordsDatabase, int *numWords);
void AdminMenu(Words *wordsDatabase, int *numWords);

# 2024-03-26 17:12
`admin.c`:


# 2024-03-27 00:01

Import
- load text file --> input filename
- put data to importedWordDatabase
- if word from wordDatabase (main database) already exist then:
  - ask user if want to overwrite exisiting word:
    - if yes, overwrite current word of wordDatabase with word of importedWordDatabase (including trivia/clues) --> wordDatabase[i] = importedWordDatabase[i];
    - if no, retain current word of wordDatabase
- if word from importedWordDatabase is unique (== -1), then it will be added (call AddWord)
- format is same as export: 
Object: Table<next line>
Kind of: Furniture<next line>
Part: Top<next line>
Part: Leg<next line>
Height: Meter<next line>
Make: Wood, Plastic<next line>
Color: Brown, White, Black<next line>
<nextline>
Object: Picture Frame<nextline>
Kind of: Home Decor<nextline>
Make: Wood, Aluminum, Plastic, Glass<nextline>
Color: Assorted<nextline>
Height: Inch<nextline>
Width: Inch<nextline>
Contains: Picture<nextline>
<nextline>
<end of file>


IMPORT PLAN:
- load text file --> input filename
- put data to importedWordDatabase
- use fgets to read each line as string (char line[100], idk if 100 is limit for each line string) 
- then remove \n (replace with \0)
  - if empty line (line[i] == '\n') skip
- all string that comes BEFORE ":" (colon) is the RELATION
  - unless it is "Object"
  - when storing in importedWordDatabase or wordDatabase to save, "Object" is not included
- all string that comes AFTER ":" (colon) is the RELATION VALUE (exclude the space before the word)
  - if "Object" is relation then its relation value (word) is stored in importedWordDatabase[i].wordName
- if word from wordDatabase (main database) already exist (SearchWordIndex(wordDatabase, *numWords,
importedWordDatabase[i].wordName) != -1) then:
  - ask user if want to overwrite exisiting word:
    - if yes, overwrite current word of wordDatabase with word of importedWordDatabase (including trivia/clues) --> wordDatabase[i] = importedWordDatabase[i];
    - if no, retain current word of wordDatabase
- if word from importedWordDatabase is unique (SearchWordIndex(wordDatabase, *numWords,
importedWordDatabase[i].wordName) == -1), then it will be added (call AddWord)
- fgets until end of file (like feof)

EXPORT PLAN
- given the current state of the wordDatabase, use fprintf




# 2024-03-29 15:43

GAME PHASE PLAN

12 words (max entries)
- 1 2 3 4 6 12
2x6, 3x4, 1x12 --> 2x6, 3x4, 1x12
- all equates to 12
2x3 3x2
4x2 2x4
1x4 4x1
1x6 6x1
1x2 2x1
15x15=




// Menu for the Admin Phase
void AdminMenu(Words *wordsDatabase, int *numWords) {
  int input, exitFlagToMainMenu = 0;
  while (!exitFlagToMainMenu) {
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
    while (input < 0 || input > 9) {
      printf("\nInvalid input. Please try again.\n");
      printf("\nEnter the number of your choice: ");
      scanf("%d", &input);
    }

    switch (input) {
    case 0:
      exitFlagToMainMenu = 1;
      break;
    case 1:
      AddWord(wordsDatabase, numWords);
      break;
    case 2:
      AddCluesUI(wordsDatabase, numWords);
      break;
    case 3:
      ModifyEntry(wordsDatabase, numWords);
      break;
    case 4:
      DeleteWord(wordsDatabase, numWords);
      break;
    case 5:
      DeleteClue(wordsDatabase, numWords);
      break;
    case 6:
      ViewWords(wordsDatabase, numWords);
      break;
    case 7:
      ViewClues(wordsDatabase, numWords);
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

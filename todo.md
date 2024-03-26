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

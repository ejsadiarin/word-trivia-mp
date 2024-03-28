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



THOUGHTS:
can encompass entries in just 1 if else statement
- top level fgets have one if else statement: 
  - if "Object: " (strncmp(line, "Object:", 8) == 0) 
  - else Relation and Relation Value
    - don't include empty lines (line[i] == '\n' || line[i] == '\0')
    - relation is before colon
    - relation value is after colon (exclude initial space, like line[i] == " " and then shift left
    the relationValue string and decrement the length of the relationValue string)
- if overwrite (y) then add another fgets to read the relation and relation value (clues)
  - have inner fgets that if not "Object: " then it is a relation and relation value
- if overwrite (n) then retain current entry

SUGGESTION:
- store everything in importedWordDatabase first
- then compare wordDatabase and importedWordDatabase
- then perform overwrite or add word with clues



EXPORT PLAN
- given the current state of the wordDatabase, use fprintf

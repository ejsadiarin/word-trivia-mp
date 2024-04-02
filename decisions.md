# memset
```c
memset(*wordsDatabase, 0, sizeof *wordsDatabase);
*numWords = 0;
```
- i mainly used this to clear or reset the arrays
- so given a ptr to the array, it fills the first number of bytes of wordsDatabase with 0

# rand srand
- srand(time(NULL)); is used to seed the random number generator
  - this is important since removing this will generate the same random number every time
- rand() % 100; is used to get a random number from 0 to 99
  - by default, rand() generates a random number from 0 to RAND_MAX (2147483647)
    - 2147483647 is the maximum value of an int

# " %[^\n]s"
- used this to handle spaces in input
- this reads until it encounters a newline
- and based on what i found, the `%[^\n]` is a negation specifier that will read the whole line including the spaces
- the space before the `%[^\n]` is used to skip any leading whitespaces

# import
- for the import i have 3 phases which is: 
(1) storing phase
- just stores it in the temporary database (which is the importedWordsDatabase)
(2) comparing phase 
- just validates the file input
(3) overwriting phase
## strchr
- to get the colon position
- strchr returns a char * (string)
### TO GET RELATION
- since strchr returns a char * (a string) and char * points to the first element of the string or substring
  - this also means that in this program, it returns a pointer to the memory location of the colon ':'
  - and when we subtract it with "line" we are getting the distance, which are measured in bytes.
  - and since characters are 1 byte, it effectively acts like an integer and we get  the index of the colon character within the line string.
- then strncpy to get before the colon (relation): 
  - i subtracted colon_pos and line, which is like 7 - 0 or 6 - 0
### TO GET RELATION VALUE
- then i move the colon_pos by adding 2, so now it points to the first character of the relation value (after the colon)
- then i just used strcpy since it is already null-terminated
  - so from position of colon_pos to the end is copied
- then increment numClues


# strncmp
- to compare first n character (not index)

# Difficult moments
## SEGFAULT
- i even used gdb and valgrind, but mostly gdb to debug it
- i found out that the strcmp (as well as strcpy) has a quirk where it segfaults if compares a null pointer, which in some way the usedWordTracker is null at some times and full of garbage values at some times since it works with some words and segfaults at other
  - so instead i just passed input as arguments from the GamePhase then did every operation inside the QuestionAnswerPhase

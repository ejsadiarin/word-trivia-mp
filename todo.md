# 2024-03-26 17:12
`admin.c`:
- AddCluesUI works with its AddCluesAction
- ViewClues - works as intended
- DeleteWord - works as intended
- DeleteClue - works as intended

THOUGHTS:
- what if i add SortAlphabetical for every function

FIX: AddWord works with its AddCluesAction
- major bug: if latest word has 10 clues (maximum), then you add new word - it copies the latest word 10 clues

FIX: ViewWords
- it shows first entry alphabetically: good
- if entry is only 1, N and P and X: good

FIX: ModifyEntry
- enter 3: good
- enter word to modify: good
- entering 1 (modify the word itself)
  - new word should be unique (if not unique then go back to AdminMenu)
- entering 2 (modify a clue): 
  - first, it should ask for what clue (the number (index + 1) of clue starting from 1 to n ) to modify (add visual number ui or a table starting from 1)
    - should not show garbage values


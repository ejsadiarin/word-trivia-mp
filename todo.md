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

FIX: ModifyEntry
- enter 3: good
- enter word to modify: good
- entering 1 (modify the word itself)
  - new word should be unique (if not unique then go back to AdminMenu)
- entering 2 (modify a clue): 
  - first, it should ask for what clue (the number (index + 1) of clue starting from 1 to n ) to modify (add visual number ui or a table starting from 1)
    - should not show garbage values

```c
printf("\n---------------------------------------\n");
printf("CHOSEN WORD: %s\n", wordsDatabase[origIndex].wordName);
for (j = 0; j < wordsDatabase[origIndex].numOfClues; j++)
{
  printf("[%d] %s: %s\n", j + 1, wordsDatabase[origIndex].clues[j].relation, wordsDatabase[origIndex].clues[j].relationValue);
}
printf("Choose the number of the clue to modify: ");
scanf("%d", &clueChoice);
if (clueChoice > wordsDatabase[origIndex].numOfClues || clueChoice < 1)
{
  printf("Invalid number. Exiting...\n");
}
else {
  printf("Enter new clue (relation): ");
  scanf("%30s", newClue);
  printf("\nEnter new clue value (relation value): ");
  scanf("%30s", newClueValue);

  // search for the clue in the selected word
  strcpy(wordsDatabase[origIndex].clues[clueChoice - 1].relation, newClue);
  strcpy(wordsDatabase[origIndex].clues[clueChoice - 1].relationValue, newClueValue);
  printf("Clues successfully overwritten/modified.\n");
  // OverwriteClue(wordsDatabase[origIndex].clues, &wordsDatabase[origIndex].numOfClues, newClue, newClueValue);
}
```

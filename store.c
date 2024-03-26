void ViewWords(Words *wordsDatabase, int *numWords) {
  int i = 0, j, willRepeat = 1;
  char input;

  if (*numWords == 0) {
    printf("\nNo words in the database. Please add words first.\n");
    return;
  }

  SortAlphabetical(wordsDatabase, numWords);

  do {
    // show word (alphabetical order)
    printf("\n");
    printf("Object: %s\n", wordsDatabase[i]->wordName);
    for (j = 0; j < wordsDatabase[i]->numOfClues; j++) {
      printf("  %s: %s\n", wordsDatabase[i]->clues[j].relation, wordsDatabase[i]->clues[j].relationValue);
    }

    // options:
    printf("\n[N] - Next, [P] - Previous, [X] - Exit\n");
    printf("Enter your choice: ");
    scanf(" %c", &input);
    printf("\n");

    // Handle next/previous options
    if ((input == 'N' || input == 'n')) {
      if (i < *numWords - 1)
        i++;
      else
        printf("End of the list.\n");
    } 
    else if ((input == 'P' || input == 'p')) {
      if (i > 0)
        i--;
      else
        printf("Start of the list.\n");
    } 
    else if (input == 'X' || input == 'x') {
      willRepeat = 0; // exit
    }
    else {
      printf("Invalid input. Please try again.\n");
    }
  } while (i < *numWords && willRepeat == 1);
}

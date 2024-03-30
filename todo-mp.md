find a way to get first letter (char) in string wordName - do loop for each word in list

Board should be dynamic based on the word entries
- Board is continuously mutated (each character is mutated with either '*' or '-')


- unique letters each row

Game Phase looks like this (2D array of characters or array of strings):
[
  {'s', 'w', 't'},
  {'s', 'w', 't'},
  {'s', 'w', 't'},
  {'s', 'w', 't'},
]
or
[
  "swt",
  "swt",
  "swt",
  "swt",
]
or (prettify)
[
  S W T
  S W T
  S W T
  S W T
]

// [ ROW %d ] Choose the letter you want to guess in row %d: 
like:
[ ROW 1 ] Choose the letter you want to guess in row %d: 
Trivia/Clue:
  - "Relation": "Relation Value"
  - "Relation": "Relation Value"
  - "Relation": "Relation Value"
[ Guessing... ] Guess the word: 

--> if answer is correct then: (replace correct letter with *)
Correct! You guessed the word correctly! Moving on to the next row...
[ ROW 2 ] Choose the letter you want to guess in row %d: 

--> if answer is incorrect then: (replace wrong letter with -)
Wrong! You guessed the word incorrectly! Choose another letter in the same row...
[ ROW 1 ] Choose another letter you want to guess in row %d: 
- best to use a while loop and flag condition (like while (!isCorrect))

--> if on last row and is correct then:
Correct! You cleared every row in the board! You win!


Board (is the "virtual board")
- has letters

when a letter is "picked":
- gameLogic() is called -> displays Question and its Trivia/Clue


FLOW:
GamePhase -> CreateBoard() -> gameLogic() -> displayQuestion() -> displayTrivia() -> displayBoard()

Game is over if:
- all rows have at least one "*" on them (WIN)
- one row have all "-" on them (LOSE)

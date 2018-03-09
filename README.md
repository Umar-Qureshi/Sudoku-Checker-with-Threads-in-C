# Sudoku Checker with Threads in C
Checks If a Sudoku board is valid whether it has blank spaces (0) or not. It is coded in c, and uses threads to check. It will display which rows, columns, or sub grids are unvalid

Welcome to the Sudoku Checker!

**How to run:**

1. Run the command make
2. Run ./puzzle

**Text Files:**

puzzle.txt is what the c program reads.
cPuzzle.txt is a correct solution with no blanks.
wPuzzle.txt is an incorrect solution.
Feel free to copy paste the other 2 text files into puzzle.txt, or to edit puzzle.txt yourself.

**Information about the program:**

* 0 means a blank space
* Checks each row, column, and sub grid individually with threads (for a total of 27 threads)
* It will display which rows, columns, or sub grids are unvalid
* Last line states whether the whole sudoku puzzle is valid
* The programs threads check if a number appears twice in a row column or thread, if it does it returns a false

**Implementation**

This program ignores blank spaces(0), and checks if the same number appears twice. Due to those 2 features this is not only a solution checker but it can check the board at any given moment in the game while the user is playing. It can be implemented in a Sudoku game as a live checker to check at every move, or as a button for the user to check their puzzle at any moment

**Information about the puzzle Sudoku**

Sudoku is a popular puzzle game. The goal of the game is to get every row, column, and sub grid to contain the numbers from 1 to 9. No row, column, or subgrid can have the same number appear twice. The puzzle starts off with giving some numbers througout the puzzle, the more numbers it gives you in the start, the easier the puzzle is.

For more information about Sudoku, go here: http://www.sudoku.com/

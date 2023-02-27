# Sudoku-Solver-Multithreaded-cpp

This is a C++ program that solves Sudoku puzzles using a multi-threaded approach. The program reads a file containing unsolved Sudoku puzzles, solves them using multiple threads, and writes the solutions to an output file.

The input text file has multiple puzzles each with a grid name followed by the 9x9 puzzle (next line)

# Usage
To run the program, compile the source code using a C++ compiler and provide the input file as an argument when running the program. For example:

$ g++ main.cpp SudokuGrid.cpp -lpthread -o test 
$ ./test puzzles.txt

The program will dynamically determine the maximum number of threads that can run concurrently on your machine and use them to solve the puzzles. The solutions will be written to a file named SolvedPuzzlesOutput.txt in the current directory.

# Implementation Details

MULTITHREADING AND FILE I/O:

The program uses the std::thread and std::mutex libraries to implement multi-threading and synchronization.

1. The solveSudokuPuzzles function reads in unsolved Sudoku puzzles from the input file, solves them, and writes the solutions to the output file.

2. The main function spawns multiple threads to call solveSudokuPuzzles concurrently and waits for them to finish before exiting.

3. The program uses a do-while loop to read and solve puzzles until the end of the input file is reached.

4. Each thread acquires a lock on the input file, reads in one puzzle, and releases the lock.

5. The thread then solves the particular puzzle and acquires a lock on the output file to write its solution.

6. Once the solution is written, the thread releases the lock on the output file.

SUDOKU SOLVER LOGIC:

1. SudokuGrid class defines the sudoku grid and contains member functions to check if a cell is empty and if a number can be placed in a given row, column, or sub-grid.

2. solve() function uses backtracking to solve the sudoku puzzle by checking each empty cell for numbers ranging from 1 to 9 and placing the number that satisfies all three constraints.

3. operator>> and operator<< are overloaded functions to read/write the SudokuGrid object to/from a file stream.

Functions:

a. bool SudokuGrid::isEmptyCell(int& row, int& col): checks if a cell is empty (contains '0') and returns its row and column.

b. bool SudokuGrid::presentInRow(int row, char num): checks if num is present in the given row.

c. bool SudokuGrid::presentInCol(int col, char num): checks if num is present in the given column.

d. bool SudokuGrid::presentInSubGrid(int startRow, int startCol, char num): checks if num is present in the sub-grid starting at (startRow, startCol).

e. bool SudokuGrid::solve(): solves the sudoku puzzle using backtracking.

f. fstream& operator>>(fstream & os, SudokuGrid & gridIn): overloads the input operator to read SudokuGrid object from a file stream.

g. fstream& operator<<(fstream & os, const SudokuGrid & gridOut): overloads the output operator to write SudokuGrid object to a file stream.

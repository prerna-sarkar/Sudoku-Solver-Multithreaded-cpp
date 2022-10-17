/*
reference: https://www.tutorialspoint.com/sudoku-solver-in-cplusplus
*/
#include"SudokuGrid.h"

bool SudokuGrid::isEmptyCell(int& row, int& col)
{
	for (row = 0; row < 9; row++)
	{
		for (col = 0; col < 9; col++)
		{
			if (gridElement[row][col] == '0')
			{
				return true;
			}
		}
	}
	return false;

}

bool SudokuGrid::presentInRow(int row, char num)
{
	for (int c = 0; c < 9; c++)
	{
		if (gridElement[row][c] == num)
		{
			return true;
			break;
		}
	}
	return false;
}

bool SudokuGrid::presentInCol(int col, char num)
{
	for (int r = 0; r < 9; r++)
	{
		if (gridElement[r][col] == num)
		{
			return true;
			break;
		}
	}
	return false;
}

bool SudokuGrid::presentInSubGrid(int startRow, int startCol, char num)
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (gridElement[r + startRow][c + startCol] == num)
			{
				return true;
				break;
			}
		}
	}
	return false;
}

bool SudokuGrid::solve()
{
	int row, col;

	if (!isEmptyCell(row, col)) //if no cell empty, sudoku has been solved
	{
		return true;
	}

	for (int n = 1; n < 10; n++) //we check each empty position for numbers ranging from 1 to 9
	{
		char num = n + '0';
		
		//before writing num to an empty cell, we check all three constraints
		if (!presentInRow(row, num) && !presentInCol(col, num) && !presentInSubGrid(row - row % 3, col - col % 3, num)) //row-row%3 is done to determine the 'startRow' of the SubGrid to be checked for a given position (row,col) (from row 0 to 2 it should return 0, from row 3 to 5 it should return 3 and from row 6 to 8 it must return 6); similarly for 'startCol'
		{
			
			gridElement[row][col] = num;
			
			if (solve())
			{
				return true;
			}
			
			
				gridElement[row][col] = '0'; //if 'num' does not satisfy sudoku constraints, fill position with 0 and try for next iteration (num+1)
			
		}
	}
	return false; //if none out of 1 to 9 satisfy the puzzle, we return a false - puzzle is not solvable
}


	fstream& operator>>(fstream & os,  SudokuGrid & gridIn)
	{
		std::string str="";
		gridIn.m_strGridName = "";
		getline(os, gridIn.m_strGridName); //save the first line read to m_strGridName
		for (int r = 0; r < 9; r++)
		{
			std::getline(os, str, '\n'); //read one row 'r' as a string
			for (int c = 0; c < 9; c++)
			{
				gridIn.gridElement[r][c] = str[c]; //store the characters read in str to each column of row 'r'
			}
		}
		return os;
	}

	fstream& operator<<(fstream & os, const SudokuGrid & gridOut)
	{
		os << gridOut.m_strGridName;
		os << endl;
		for (int r = 0; r < 9; r++)
		{
			for (int c = 0; c < 9; c++)
			{
				os << gridOut.gridElement[r][c]; //write the characters one by one
			}
			os << endl; //go to new line after finishing printing out each row
		}
		return os;
	}
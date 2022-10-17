#pragma once
#include<fstream>
#include<string>
using namespace std;

class SudokuGrid
{
public:
	std::string m_strGridName;
	unsigned char gridElement[9][9];
	friend fstream& operator>>(fstream& os,  SudokuGrid& gridIn); // reads a single SudokuGrid object from a fstream file.
	friend fstream& operator<<(fstream& os, const SudokuGrid& gridIn); //writes the SudokuGrid object to a file in the same format that is used in reading in the object
	bool solve();
	bool presentInSubGrid(int startRow, int startCol, char num);
	bool presentInCol(int col, char num);
	bool presentInRow(int row, char num);
	bool isEmptyCell(int& row, int& col);
};

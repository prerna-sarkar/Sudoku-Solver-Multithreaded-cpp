#include<thread>
#include<mutex>
#include<string>
#include<vector>
#include "SudokuGrid.h"


std::mutex outFileMutex;
std::mutex inFileMutex;
std::fstream outFile;
std::fstream inFile;


void solveSudokuPuzzles()
{
	/*
	 The function needs to have a do-while loop to continue to read in and solve puzzles and then write out the solution until the end of the file is reached.
	 once the end of the file is reached the function should return.
	*/
	SudokuGrid grid;
	do
	{		
	    inFileMutex.lock();
		if (inFile.eof())
		{
			inFileMutex.unlock(); //if end of file has been reached, do not lock file and get out of the loop
			break;
		}
		inFileMutex.unlock();
		inFileMutex.lock();
		inFile >> grid; //lock inFile, read input puzzle, unlock inFile
		inFileMutex.unlock();

		grid.SudokuGrid::solve();

		outFileMutex.lock();
		outFile << grid;    //lock outFile, write solution to corresponding puzzle, unlock outFile
		outFileMutex.unlock();

	} while (!inFile.eof()); //if end of file has been reached, do not lock file and get out of the loop
}

int main(int argc, char** argv)
{
	std::string fileName = "";
	if (argc == 2)
	{
		fileName = argv[1];
	}
	else
	{
		printf("Please enter the path for your input file");
		return 1;
	}

	unsigned int numThreads = std::thread::hardware_concurrency(); //dynamically determine the max number of threads that can run concurrently
	printf("Num Threads = %d\n", numThreads);

	inFile.open(argv[1], ios_base::in);
	if (inFile.fail()) //failed to open file
	{
		printf("File not found\n");
		return 0;
	}

	outFile.open("SolvedPuzzlesOutput.txt", ios_base::app);

	/*
	main() function should then spawn (numThreads-1) threads calling the function solveSudokuPuzzles().
	*/

	std::vector<std::thread> threadsVector; //vector to store created threads
	for (int n = 1; n < numThreads; n++)
	{
		threadsVector.push_back(std::thread(solveSudokuPuzzles));
	}
	solveSudokuPuzzles();
	for (int n = 0; n < numThreads-1; n++) //main thread waits till all threads have finished their task
	{
		threadsVector[n].join();
	}
	inFile.close();
	outFile.close();
}

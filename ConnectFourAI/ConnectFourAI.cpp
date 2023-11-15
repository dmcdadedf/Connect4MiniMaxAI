//Project: Connect 4 MiniMax AI     Date:
//Authors: David McDade, Jared Rivard

// User is X
// Cpu is O

#include <iostream>
#include <chrono>

using namespace std::chrono;

const int sizeRow = 3;
const int sizeCol = 4;

int numOfNodesExplored = 0;

bool checkIfXWins(char* board[sizeRow]);
bool checkIfOWins(char* board[sizeRow]);
void printBoard(char* board[sizeRow]);
void initBoard(char* board[sizeRow]);
int findBestMove(char* board[sizeRow]);
int miniMax(char* board[sizeRow], int depth, bool isMaximizing);
int askUserMove(char* board[sizeRow]);
void makeMove(char* board[sizeRow], int colOfMove, bool isX);
bool isMovesLeft(char* board[sizeRow]);
void deleteBoard(char* board[sizeRow]);

int main(void) 
{
	bool userTurn = true;
	int colChoice = -1;

	auto start = high_resolution_clock::now();

	char** mainBoard = new char* [sizeRow];
	for (int i = 0; i < sizeRow; i++)
	{
		mainBoard[i] = new char[sizeCol];
	}
	initBoard(mainBoard);
	
	printBoard(mainBoard);

	while (isMovesLeft(mainBoard)) 
	{
		colChoice = askUserMove(mainBoard);
		makeMove(mainBoard, colChoice, true);
		printBoard(mainBoard);

		colChoice = askUserMove(mainBoard);
		makeMove(mainBoard, colChoice, false);
		printBoard(mainBoard);
	}	

	deleteBoard(mainBoard);

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);

	std::cout << "Runtime: " << duration.count() << " milliseconds\n";
	std::cout << "Number of Nodes Explored:" << numOfNodesExplored << "\n";

	return 0;
}

bool checkIfXWins(char* board[sizeRow])
{
	return false;
}

bool checkIfOWins(char* board[sizeRow])
{
	return false;
}

// Done
void printBoard(char* board[sizeRow])
{
	for (int i = 0; i < sizeRow; i++)
	{
		std::cout << "\n ";

		for (int j = 0; j < sizeCol; j++)
		{
			std::cout << board[i][j];
			if (j != sizeCol - 1)
			{
				std::cout << " | ";
			}
		}
		std::cout << "\n";
		for (int j = 0; j < sizeCol; j++)
		{
			if (i != sizeRow - 1)
			{
				std::cout << "----";
			}
		}
	}
	for (int j = 0; j < sizeCol; j++)
	{
		if (j != sizeCol)
		{
			std::cout << " " << j + 1 << "  ";
		}
	}
	std::cout << "\n";
	
}

// Done
void initBoard(char* board[sizeRow])
{
	for (int i = 0; i < sizeRow; i++)
	{
		for (int j = 0; j < sizeCol; j++)
		{
			board[i][j] = ' ';
		}
	}
}

int findBestMove(char* board[sizeRow])
{
	return 0;
}

int miniMax(char* board[sizeRow], int depth, bool isMaximizing)
{
	return 0;
}

// Done
int askUserMove(char* board[sizeRow])
{
	bool validMove = false;
	int userChoice = -1;

	while (!validMove)
	{
		userChoice = -1;
		while (userChoice < 1 || userChoice > sizeCol)
		{
			std::cout << "Choose a column to play in: \n";
			std::cin >> userChoice;

			if (userChoice < 1 || userChoice > sizeCol) {
				std::cout << "Please enter a valid number. \n";
			}
		}

		userChoice--;

		if (board[0][userChoice] == ' ') {
			validMove = true;
		}
		else 
		{
			std::cout << "Please enter a move in an empty space. \n";
		}
	}
	return userChoice;
}

// Done
void makeMove(char* board[sizeRow], int colOfMove, bool isX)
{
	bool moveMade = false;

	for (int i = 0; i < sizeRow; i++) 
	{
		if (i == sizeRow - 1 && moveMade == false) 
		{
			if (isX)
			{
				board[i][colOfMove] = 'x';
			}
			if (!isX)
			{
				board[i][colOfMove] = 'o';
			}
			moveMade = true;
		}
		if (moveMade == false) 
		{
			if (board[i + 1][colOfMove] != ' ')
			{
				if (isX)
				{
					board[i][colOfMove] = 'x';
				}
				if (!isX)
				{
					board[i][colOfMove] = 'o';
				}
				moveMade = true;
			}
		}
		
	}
}

// Done
bool isMovesLeft(char* board[sizeRow])
{
	for (int i = 0; i < sizeRow; i++)
	{
		for (int j = 0; j < sizeCol; j++)
		{
			if (board[i][j] == ' ') 
			{
				return true;
			}
		}
	}
	std::cout << "No Moves Left\n";
	return false;
}

// Done
void deleteBoard(char* board[sizeRow]) 
{
	for (int i = 0; i < sizeRow; i++) // Delete Arrays from Stack
		delete[] board[i];
	delete[] board;
}

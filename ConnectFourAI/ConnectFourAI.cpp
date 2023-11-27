//Project: Connect 4 MiniMax AI     Date:
//Authors: David McDade, Jared Rivard

// User is x
// Cpu is o
// x and o are lowercase

#include <iostream>
#include <chrono>

using namespace std::chrono;

const int sizeRow = 7;
const int sizeCol = 8;

int numOfNodesExplored = 0;

bool checkIfXWins(char* board[sizeRow]);
bool checkIfOWins(char* board[sizeRow]);
void printBoard(char* board[sizeRow]);
void initBoard(char* board[sizeRow]);
int findBestMove(char* board[sizeRow]);
int miniMax(char* board[sizeRow], int depth, int alpha, int beta, bool isMax);
int askUserMove(char* board[sizeRow]);
void makeMove(char* board[sizeRow], int colOfMove, bool isX);
bool isMovesLeft(char* board[sizeRow]);
void deleteBoard(char* board[sizeRow]);
int evaluateScore(char* board[sizeRow]);
bool evaluateBoard(char* board[sizeRow], bool isX, int numToCheck);
char** copyBoard(char* board[sizeRow]);

int main(void) 
{
	bool userTurn = true;
	int colChoice = -1;
	bool gameEnd = false;

	auto start = high_resolution_clock::now();

	char** mainBoard = new char* [sizeRow];
	for (int i = 0; i < sizeRow; i++)
	{
		mainBoard[i] = new char[sizeCol];
	}
	initBoard(mainBoard);
	
	printBoard(mainBoard);

	if (checkIfXWins(mainBoard)) 
	{
		std::cout << "\nX Wins\n";
	}

	while (!gameEnd)
	{
		colChoice = -1;
		if (userTurn) 
		{
			colChoice = askUserMove(mainBoard);
			makeMove(mainBoard, colChoice, !userTurn);
			printBoard(mainBoard);
		}
		
		if (!userTurn) 
		{
			colChoice = findBestMove(mainBoard);
			makeMove(mainBoard, colChoice, !userTurn);
			printBoard(mainBoard);
		}
		if (!isMovesLeft(mainBoard) || checkIfOWins(mainBoard) || checkIfXWins(mainBoard))
		{
			gameEnd = true;
		}
		

		if(userTurn)
			userTurn = false;
		else
			userTurn = true;
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
	int inARow = 0;
	//Diagonal 1
	for (int index = 3; index < (sizeRow - 1) + (sizeCol - 1) - 3; index++) 
	{
		for (int i = 0; i < sizeRow; i++) 
		{
			for (int j = 0; j < sizeCol; j++) 
			{
				if (i + j == index) 
				{
					if (board[i][j] == 'x') 
					{
						inARow++;
						if (inARow == 4) 
						{
							//std::cout << "X wins diag 1\n";
							return true;
						}
					}
					else
					{
						inARow = 0;
					}
				}
			}
		}
	}

	inARow = 0;

	//Diagonal 2
	for (int index = 3; index < (sizeRow - 1) + (sizeCol - 1) - 3; index++)
	{
		for (int i = 0; i < sizeRow; i++)
		{
			for (int j = 0; j < sizeCol; j++)
			{
				if ((sizeRow - 1 - i) + j == index)
				{
					if (board[i][j] == 'x')
					{
						inARow++;
						if (inARow == 4)
						{
							//std::cout << "X wins diag 2\n";
							return true;
						}
					}
					else
					{
						inARow = 0;
					}
				}
			}
		}
	}

	inARow = 0;

	//Horz
	for (int i = 0; i < sizeRow; i++)
	{
		for (int j = 0; j < sizeCol; j++)
		{
			if (board[i][j] == 'x')
			{
				inARow++;
				if (inARow == 4)
				{
					//std::cout << "X wins horz\n";
					return true;
				}
			}
			else
			{
				inARow = 0;
			}
		}
		inARow = 0;
	}

	inARow = 0;

	//Vert
	for (int i = 0; i < sizeCol; i++)
	{
		for (int j = 0; j < sizeRow; j++)
		{
			if (board[j][i] == 'x')
			{
				inARow++;
				if (inARow == 4)
				{
					//std::cout << "X wins vert\n";
					return true;
				}
			}
			else
			{
				inARow = 0;
			}
		}
		inARow = 0;
	}

	return false;
}


bool checkIfOWins(char* board[sizeRow])
{
	int inARow = 0;
	//Diagonal 1
	for (int index = 3; index < (sizeRow - 1) + (sizeCol - 1) - 3; index++)
	{
		for (int i = 0; i < sizeRow; i++)
		{
			for (int j = 0; j < sizeCol; j++)
			{
				if (i + j == index)
				{
					if (board[i][j] == 'o')
					{
						inARow++;
						if (inARow == 4)
						{
							//std::cout << "O wins diag 1\n";
							return true;
						}
					}
					else
					{
						inARow = 0;
					}
				}
			}
		}
	}

	inARow = 0;

	//Diagonal 2
	for (int index = 3; index < (sizeRow - 1) + (sizeCol - 1) - 3; index++)
	{
		for (int i = 0; i < sizeRow; i++)
		{
			for (int j = 0; j < sizeCol; j++)
			{
				if ((sizeRow - 1 - i) + j == index)
				{
					if (board[i][j] == 'o')
					{
						inARow++;
						if (inARow == 4)
						{
							//std::cout << "O wins diag 2\n";
							return true;
						}
					}
					else
					{
						inARow = 0;
					}
				}
			}
		}
	}

	inARow = 0;

	//Horz
	for (int i = 0; i < sizeRow; i++)
	{
		for (int j = 0; j < sizeCol; j++)
		{
			if (board[i][j] == 'o')
			{
				inARow++;
				if (inARow == 4)
				{
					//std::cout << "O wins horz\n";
					return true;
				}
			}
			else
			{
				inARow = 0;
			}
		}
		inARow = 0;
	}

	inARow = 0;

	//Vert
	for (int i = 0; i < sizeCol; i++)
	{
		for (int j = 0; j < sizeRow; j++)
		{
			if (board[j][i] == 'o')
			{
				inARow++;
				if (inARow == 4)
				{
					//std::cout << "O wins vert\n";
					return true;
				}
			}
			else
			{
				inARow = 0;
			}
		}
		inARow = 0;
	}

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

//done
int findBestMove(char* board[sizeRow])
{
	int bestVal = -10000;
	int bestMove;
	bool validMove = false;

	for (int i = 0; i < sizeCol; i++) {
		
				char** newBoard = copyBoard(board);
				makeMove(newBoard, i, true);
				int moveVal = miniMax(newBoard, 5, -10000, 10000, true);

				if (moveVal > bestVal) {
					bestVal = moveVal;
					bestMove = i;
				}
	}
	return bestMove;
}

//slight changes
int miniMax(char* board[sizeRow], int depth, int alpha, int beta, bool isMax) {
	if (checkIfOWins(board)) {
		return -10;
	}
	if (checkIfXWins(board)) {
		return 10;
	}
	
	if (isMovesLeft(board) == false) {
			return 0;
	}

	if (depth == 0) {
		return evaluateScore(board);
	}

	if (isMax) {
		bool validMove = false;
		int value = -100000;
		for (int i = 0; i < sizeCol; i++) {
			if (board[0][i] == ' ') {
				validMove = true;
			}
			char** newBoard = copyBoard(board);
			if (validMove = true) {
				makeMove(newBoard, i, true);
			}
			else {
				break;
			}
			int newValue = miniMax(newBoard, depth - 1, alpha, beta, false);
			if (newValue > value) {
				value = newValue;
			}
			alpha = std::max(alpha, value);
			if (alpha >= beta) {
				break;
			}
		}
		return value;
	}

		bool validMove = false;
		int value = 100000;
		for (int i = 0; i < sizeCol; i++) {
			if (board[0][i] == ' ') {
				validMove = true;
			}
			char** newBoard = copyBoard(board);
			if (validMove = true) {
				makeMove(newBoard, i, true);
			}
			int newValue = miniMax(newBoard, depth - 1, alpha, beta, true);
			if (newValue < value) {
				value = newValue;
			}
			beta = std::max(beta, value);
			if (alpha >= beta) {
				break;
			}
		}
		return value;
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

int evaluateScore(char* board[sizeRow]) {
	int score = 0;
	for (int i = 0; i < sizeRow; i++) {
		if (board[i][4] == 'x') {
			score += 3;
		}
		if (board[i][5] == 'x') {
			score += 3;
		}
		if (board[i][4] == 'o') {
			score -= 3;
		}
		if (board[i][5] == 'o') {
			score -= 3;
		}
	}

	if (evaluateBoard(board, true, 3)) {
		score += 7;
	}

	if (evaluateBoard(board, true, 2)) {
		score += 5;
	}

	if (evaluateBoard(board, false, 3)) {
		score -= 7;
	}
	if (evaluateBoard(board, false, 2)) {
		score -= 5;
	}

	return score;
}


// Done
void deleteBoard(char* board[sizeRow]) 
{
	for (int i = 0; i < sizeRow; i++) // Delete Arrays from Stack
		delete[] board[i];
	delete[] board;
}

bool evaluateBoard(char* board[sizeRow], bool isX, int numToCheck) {
	int inARow = 0;
	char c = 'x';
	//Diagonal 1
	for (int index = 3; index < (sizeRow - 1) + (sizeCol - 1) - 3; index++)
	{
		for (int i = 0; i < sizeRow; i++)
		{
			for (int j = 0; j < sizeCol; j++)
			{
				if (i + j == index)
				{
					if (board[i][j] == c)
					{
						inARow++;
						if (inARow == numToCheck)
						{
							return true;
						}
					}
					else
					{
						inARow = 0;
					}
				}
			}
		}
	}

	inARow = 0;

	//Diagonal 2
	for (int index = 3; index < (sizeRow - 1) + (sizeCol - 1) - 3; index++)
	{
		for (int i = 0; i < sizeRow; i++)
		{
			for (int j = 0; j < sizeCol; j++)
			{
				if ((sizeRow - 1 - i) + j == index)
				{
					if (board[i][j] == c)
					{
						inARow++;
						if (inARow == numToCheck)
						{
							return true;
						}
					}
					else
					{
						inARow = 0;
					}
				}
			}
		}
	}

	inARow = 0;

	//Horz
	for (int i = 0; i < sizeRow; i++)
	{
		for (int j = 0; j < sizeCol; j++)
		{
			if (board[i][j] == c)
			{
				inARow++;
				if (inARow == numToCheck)
				{
					return true;
				}
			}
			else
			{
				inARow = 0;
			}
		}
		inARow = 0;
	}

	inARow = 0;

	//Vert
	for (int i = 0; i < sizeCol; i++)
	{
		for (int j = 0; j < sizeRow; j++)
		{
			if (board[j][i] == c)
			{
				inARow++;
				if (inARow == numToCheck)
				{
					return true;
				}
			}
			else
			{
				inARow = 0;
			}
		}
		inARow = 0;
	}

	return false;
}

char** copyBoard(char* board[sizeRow]) {
	char** newBoard = new char* [sizeRow];
	for (int i = 0; i < sizeRow; i++)
	{
		newBoard[i] = new char[sizeCol];
	}
	for (unsigned int r = 0; r < sizeRow; r++) {
		for (unsigned int c = 0; c < sizeCol; c++) {
			newBoard[r][c] = board[r][c]; // just straight copy
		}
	}
	return newBoard;
}
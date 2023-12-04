//Project: Connect 4 MiniMax AI     Date:12-6-2023
//Authors: David McDade, Jared Rivard

// User is x
// Cpu is o
// x and o are lowercase

#include <iostream>
#include <chrono>

using namespace std::chrono;

const int sizeRow = 6;
const int sizeCol = 7;

int numOfNodesExplored = 0;
int numOfCompMoves = 0;

bool checkIfXWins(char* board[sizeRow]);
bool checkIfOWins(char* board[sizeRow]);
bool checkIfXWinsFinal(char* board[sizeRow]);
bool checkIfOWinsFinal(char* board[sizeRow]);
void printBoard(char* board[sizeRow]);
void initBoard(char* board[sizeRow]);
int findBestMove(char* board[sizeRow]);
int miniMax(char* board[sizeRow], int depth, bool isMaximizing);
int askUserMove(char* board[sizeRow], int moveCount);
void makeMove(char* board[sizeRow], int colOfMove, bool isX);
void unmakeMove(char* board[sizeRow], int colOfMove);
bool isMovesLeft(char* board[sizeRow]);
bool checkCol(char* board[sizeRow], int colOfMove);
void deleteBoard(char* board[sizeRow]);
bool checkIfWinPossibleVert(char* board[sizeRow], int colOfMove);

int main(void) 
{
	bool userTurn = true;
	int colChoice = -1;
	bool gameEnd = false;
	int moveCount = 0;

	auto start = high_resolution_clock::now();

	char** mainBoard = new char* [sizeRow];
	for (int i = 0; i < sizeRow; i++)
	{
		mainBoard[i] = new char[sizeCol];
	}
	initBoard(mainBoard);
	
	printBoard(mainBoard);

	while (!gameEnd)
	{
		colChoice = -1;
		if (userTurn) 
		{
			colChoice = askUserMove(mainBoard,moveCount);
			makeMove(mainBoard, colChoice, userTurn);
			moveCount++;
			printBoard(mainBoard);
		}
		
		if (!userTurn) 
		{
			colChoice = findBestMove(mainBoard);
			makeMove(mainBoard, colChoice, userTurn);
			numOfCompMoves++;
			moveCount++;
			printBoard(mainBoard);
		}
		if (!isMovesLeft(mainBoard) || checkIfOWins(mainBoard) || checkIfXWins(mainBoard))
		{
			if (!isMovesLeft(mainBoard)) 
			{
				std::cout << "Draw \n";
			}
			checkIfOWinsFinal(mainBoard);
			checkIfXWinsFinal(mainBoard);
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

// Done
bool checkIfXWins(char* board[sizeRow])
{
	int inARow = 0;
	//Diagonal 1
	for (int index = 3; index <= (sizeRow - 1) + (sizeCol - 1) - 3; index++) 
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
		inARow = 0;
	}

	inARow = 0;

	//Diagonal 2
	for (int index = 3; index <= (sizeRow - 1) + (sizeCol - 1) - 3; index++)
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
		inARow = 0;
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

bool checkIfXWinsFinal(char* board[sizeRow])
{
	int inARow = 0;
	//Diagonal 1
	for (int index = 3; index <= (sizeRow - 1) + (sizeCol - 1) - 3; index++)
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
							std::cout << "Human Wins Diagonal 1 Row:" << i << " Col:" << j << "\n";
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
		inARow = 0;
	}

	inARow = 0;

	//Diagonal 2
	for (int index = 3; index <= (sizeRow - 1) + (sizeCol - 1) - 3; index++)
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
							std::cout << "Human Wins Diagonal 2 Row:" << i << " Col:" << j << "\n";
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
		inARow = 0;
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
					std::cout << "Human Wins Horz Row:" << i << " Col:" << j << "\n";
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
					std::cout << "Human Wins Vert Row:" << i << " Col:" << j << "\n";
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
bool checkIfOWins(char* board[sizeRow])
{
	int inARow = 0;
	//Diagonal 1
	for (int index = 3; index <= (sizeRow - 1) + (sizeCol - 1) - 3; index++)
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
		inARow = 0;
	}

	inARow = 0;

	//Diagonal 2
	for (int index = 3; index <= (sizeRow - 1) + (sizeCol - 1) - 3; index++)
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
		inARow = 0;
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

bool checkIfOWinsFinal(char* board[sizeRow])
{
	int inARow = 0;
	//Diagonal 1
	for (int index = 3; index <= (sizeRow - 1) + (sizeCol - 1) - 3; index++)
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
							std::cout << "Comp Wins Diagonal 1 Row:" << i << " Col:" << j << "\n";
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
		inARow = 0;
	}

	inARow = 0;

	//Diagonal 2
	for (int index = 3; index <= (sizeRow - 1) + (sizeCol - 1) - 3; index++)
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
							std::cout << "Comp Wins Diagonal 2 Row:" << i << " Col:" << j << "\n";
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
		inARow = 0;
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
					std::cout << "Comp Wins Horz Row:" << i << " Col:" << j << "\n";
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
					std::cout << "Comp Wins Vert Row:" << i << " Col:" << j << "\n";
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
			if (j < 10) 
			{
				std::cout << " " << j + 1 << "  ";
			}
			else 
			{
				std::cout << " " << j + 1 << " ";
			}
			
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
	int bestVal = -100;
	int worstVal = 100;
	int bestMove = -1;
	
	for (int i = 0; i < sizeCol; i++) 
	{
		if (checkCol(board,i)) 
		{
			makeMove(board, i, false);
			int moveVal = miniMax(board, 0, false);
			unmakeMove(board, i);
			if (moveVal > bestVal) {
				bestVal = moveVal;
				bestMove = i;
			}
			if (moveVal < worstVal) 
			{
				worstVal = moveVal;
			}
		}
	}
	if (worstVal != -10 && bestVal != 10)
	{
		if (checkCol(board, sizeCol / 2) && checkIfWinPossibleVert(board, sizeCol / 2) && numOfCompMoves != 0)
		{
			bestMove = sizeCol / 2;
		}
		else if (checkCol(board, sizeCol - 1) && checkIfWinPossibleVert(board, sizeCol - 1) && numOfCompMoves != 0)
		{
			bestMove = sizeCol - 1;
		}
		else if(checkCol(board, 0) && checkIfWinPossibleVert(board, 0) && numOfCompMoves != 0)
		{
			bestMove = 0;
		}
		else if (checkCol(board, (sizeCol-1) / 4) && checkIfWinPossibleVert(board, (sizeCol-1) / 4)) 
		{
			bestMove = (sizeCol-1) / 4;
		}
	}
	return bestMove;
}

int miniMax(char* board[sizeRow], int depth, bool isMaximizing)
{
	numOfNodesExplored++;
	if (depth > 5) 
	{
		return 0;
	}
	if (checkIfXWins(board))
	{
		return -10;
	}
	if (checkIfOWins(board))
	{
		return 10;
	}
	if (!isMovesLeft(board))
	{
		return 0;
	}
	if (isMaximizing)
	{
		int bestVal = -1000;
		int val = -1000;
		for (int i = 0; i < sizeCol; i++)
		{
			
			if (checkCol(board,i))
			{
				makeMove(board, i, false);
				//printBoard(board);
				bestVal = std::max(bestVal, miniMax(board, depth + 1, false));
				unmakeMove(board, i);
				/*alpha = std::max(alpha, bestVal);
				if (alpha >= beta) {
					break;
				}*/
			}


		}
		return bestVal;
	}
	else
	{
		int bestVal = 1000;
		for (int i = 0; i < sizeCol; i++)
		{
			if (checkCol(board,i))
			{
				makeMove(board, i, true);
				//printBoard(board);
				bestVal = std::min(bestVal, miniMax(board, depth + 1, true));
				unmakeMove(board, i);
				/*beta = std::max(beta, bestVal);
				if (alpha >= beta) {
					break;
				}*/
			}
		}
		return bestVal;
	}
}

// Done
int askUserMove(char* board[sizeRow], int moveCount)
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
		if (moveCount > 1)
		{
			if (board[0][userChoice] == ' ') {
				validMove = true;
			}
			else
			{
				std::cout << "Please enter a move in an empty space. \n";
			}
		}
		else 
		{
			if ((userChoice != 0 && userChoice != sizeCol-1 && userChoice != sizeCol / 2))
			{
				validMove = true;
			}
			else 
			{
				std::cout << "Please enter a valid number. \n";
			}
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

void unmakeMove(char* board[sizeRow], int colOfMove)
{
	bool moveMade = false;

	for (int i = 0; i < sizeRow; i++)
	{
			if (board[i][colOfMove] != ' ')
			{
				board[i][colOfMove] = ' ';
				return;
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
	return false;
}

bool checkCol(char* board[sizeRow], int colOfMove)
{
	for (int i = 0; i < sizeRow; i++)
	{
		if (board[i][colOfMove] == ' ') 
		{
			return true;
		}
	}
	return false;
}

bool checkIfWinPossibleVert(char* board[sizeRow], int colOfMove)
{
	for (int i = 0; i < 4; i++)
	{
		if (board[i][colOfMove] == 'x')
		{
			return false;
		}
	}
	return true;
}

// Done
void deleteBoard(char* board[sizeRow]) 
{
	for (int i = 0; i < sizeRow; i++) // Delete Arrays from Stack
		delete[] board[i];
	delete[] board;
}

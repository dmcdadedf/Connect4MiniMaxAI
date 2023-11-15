//Project: Connect 4 MiniMax AI     Date:
//Authors: David McDade, Jared Rivard

#include <iostream>
#include <chrono>

using namespace std::chrono;

const int sizeX = 7;
const int sizeY = 8;

int numOfNodesExplored = 0;

bool checkIfXWins(char* board[sizeX]);
bool checkIfOWins(char* board[sizeX]);
void printBoard(char* board[sizeX]);
void initBoard(char* board[sizeX]);
int findBestMove(char* board[sizeX]);
int miniMax(char* board[sizeX], int depth, bool isMaximizing);
void makeMove(char* board[sizeX], int colOfMove);
bool isMovesLeft(char* board[sizeX]);

int main(void) 
{
	return 0;
}

bool checkIfXWins(char* board[sizeX]) 
{
	return false;
}

bool checkIfOWins(char* board[sizeX]) 
{
	return false;
}

void printBoard(char* board[sizeX]) 
{

}

void initBoard(char* board[sizeX]) 
{

}

int findBestMove(char* board[sizeX]) 
{
	return 0;
}

int miniMax(char* board[sizeX], int depth, bool isMaximizing) 
{
	return 0;
}

void makeMove(char* board[sizeX], int colOfMove)
{
	
}

bool isMovesLeft(char* board[sizeX]) 
{
	return false;
}

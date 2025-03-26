#include <iostream>
using namespace std;
#define N 10 // N-Queens size
int board[N][N] = { 0 };
int solutions = 0; // dem so cach giai

// check if a queen can be placed at board[row][col]
bool isSafe(int row, int col){
	for (int i = 0; i < row; i++)
		{
		if (board[i][col] == 1)
			return false; // Check col
		
			if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1)
			return false; // Check cheo trai
	
			if (col + (row - i) < N && board[i][col + (row - i)] == 1)
			 return false; // Check cheo phai
		}
	return true;
}
//backtracking place queens
void solveNQueens(int row){
	if (row == N) 
		{ // tat ca Queens da duoc dat-> tang solution
		solutions++;
		return;
		}
	for (int col = 0; col < N; col++) 
		{
		if (isSafe(row, col))
			{
			board[row][col] = 1; // Place queen
			solveNQueens(row + 1); // Recur for next row
			board[row][col] = 0; // Backtrack
			}
		}
}

int main(){
	solveNQueens(0);
	cout <<"Number of solutions ("<<N<<"x"<<N<< "): " << solutions << endl;
	return 0;
}


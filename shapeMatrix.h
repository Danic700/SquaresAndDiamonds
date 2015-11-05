#ifndef _MAT_H
#define _MAT_H

#include "definitions.h"
using namespace std;								//SquareMatrix is a new class, we added a matrix to our project so we could implement the diff procedure to prevent ריצודים 

class ShapeMatrix{
	char m_mat[MAX_ROWS+1][MAX_COLS+1];			
	void putDiamondInMatrixNext(int i_x, int i_y,int i_length, int i_level, char i_char);
public:
	ShapeMatrix(){initializeMatrix();}
	void initializeMatrix();
	void printMatrix();
	void putCharInMatrix(const char& i_char, const int& i_x, const int& i_y, const int& i_length);

	char getChar(const int& i_x, const int& i_y);

	
	
};

#endif
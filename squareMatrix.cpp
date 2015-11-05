#include "shapeMatrix.h"



void ShapeMatrix::initializeMatrix()
{
	for (int i = MIN_ROWS; i <= MAX_ROWS; i++)
	{
		for (int j = MIN_COLS; j <= MAX_COLS; j++)
		{
			m_mat[i][j] = ' ';
		}

	}
}

void ShapeMatrix::printMatrix()
{
	for (int i = MIN_ROWS; i <= MAX_ROWS; i++)
	{
		for (int j = MIN_COLS; j <= MAX_COLS; j++)
		{
			cout<<m_mat[i][j];
		}

	}
}

void ShapeMatrix::putCharInMatrix(const char& i_char, const int& i_x, const int& i_y, const int& i_length)
{
	if(i_char!='@')
	{
		for(int i=i_x; i<i_x+ i_length ;i++)
		{
			for(int j=i_y; j<i_y+i_length; j++)
			{
				if( (i==i_x || i== i_x + i_length-1) && ( i>=0 && i<=MAX_ROWS && j>=0 && j<=MAX_COLS) )
				{
					m_mat[i][j] = i_char;
				}
				else if( (j==i_y || j==i_y + i_length -1 ) && ( i>=0 && i<=MAX_ROWS && j>=0 && j<=MAX_COLS) )
				{
					m_mat[i][j] = i_char;
				}
				else if( i>=0 && i<=MAX_ROWS && j>=0 && j<=MAX_COLS)
				{
					m_mat[i][j] = ' ';
				}
			}
		}
	}
	else //if it's a diamond
	{
		int length = i_length;
		int level = 0;
		for(int i = 0; i<length+1; i++)
		{
			if( (i_x >= MIN_ROWS) && (i_x <= MAX_ROWS) && (i_y+i <=MAX_COLS) && (i_y >= MIN_COLS) ) 
				m_mat[i_x][i_y+i] = i_char;
			if( (i_x >= MIN_ROWS) && (i_x <= MAX_ROWS) && (i_y<=MAX_COLS) && (i_y-i >= MIN_COLS) ) 
				m_mat[i_x][i_y-i] = i_char;
		}
		
	//	length--;
		if(length!=0)
		{
			this->putDiamondInMatrixNext(i_x,i_y, length, level+1, i_char);
		}
	}
}


void ShapeMatrix::putDiamondInMatrixNext(int i_x, int i_y, int i_length, int i_level, char i_char)
{
	if( (i_x - i_level>= MIN_ROWS) && (i_x <= MAX_ROWS) && (i_y <=MAX_COLS) && (i_y >= MIN_COLS) ) 
		m_mat[i_x-i_level][i_y] = i_char;

	if( (i_x >= MIN_ROWS) && (i_x +i_level <= MAX_ROWS) && (i_y <=MAX_COLS) && (i_y >= MIN_COLS) ) 
		m_mat[i_x+i_level][i_y] = i_char;
	
	for(int i=1;i<i_length; i++)
	{
		if( (i_x>= MIN_ROWS) && (i_x + i_level <= MAX_ROWS) && (i_y+i<=MAX_COLS) && (i_y >= MIN_COLS) ) 
			m_mat[i_x+i_level][i_y+i] = i_char;

		if( (i_x >= MIN_ROWS) && (i_x + i_level <= MAX_ROWS) && (i_y<=MAX_COLS) && (i_y-i>= MIN_COLS) ) 
			m_mat[i_x+i_level][i_y-i] = i_char;

		if( (i_x - i_level >= MIN_ROWS) && (i_x <= MAX_ROWS) && (i_y+i<=MAX_COLS) && (i_y>= MIN_COLS) ) 
			m_mat[i_x-i_level][i_y+i] = i_char;

		if( (i_x - i_level >= MIN_ROWS) && (i_x <= MAX_ROWS) && (i_y<=MAX_COLS) && (i_y-i>= MIN_COLS) ) 
			m_mat[i_x-i_level][i_y-i] = i_char;
	}
	i_length--;
	if(i_length!=0)
		putDiamondInMatrixNext(i_x,i_y,i_length, i_level+1, i_char);
}


char ShapeMatrix::getChar(const int& i_x, const int& i_y)
{
	return m_mat[i_x][i_y];
}
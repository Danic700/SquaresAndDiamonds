#include "diamond.h"

void Diamond::getDateFromUser()	
{
	clrscr();
	int x, y, length;
	char ch;
	cout<<"please enter x, y and radius \n";
	cin>>x>>y>>length;
	m_x = x;
	m_y = y;
	m_length = length;
}

void Diamond::drawShape()		//Draw square draws our sqaure as requested 
{
	int level = 0;
	int length = m_length;
	for(int i = 0; i<m_length+1; i++)
	{
		if( (m_x >= MIN_ROWS) && (m_x <= MAX_ROWS) && (m_y+i <=MAX_COLS) && (m_y >= MIN_COLS) ) 
		{
			gotoxy(m_y+i, m_x);
			cout<<m_char;
		}
		if( (m_x >= MIN_ROWS) && (m_x <= MAX_ROWS) && (m_y<=MAX_COLS) && (m_y-i >= MIN_COLS) ) 
		{
			gotoxy(m_y-i, m_x);
			cout<<m_char;
		}
	}
	//length--;
	if(length!=0)
	{
		printNext(length , level +1);
	}
}

void Diamond::printNext(int i_length, int i_level)
{
	if( (m_x - i_level>= MIN_ROWS) && (m_x <= MAX_ROWS) && (m_y <=MAX_COLS) && (m_y >= MIN_COLS) ) 
	{
		gotoxy(m_y,m_x-i_level);
		cout<<m_char;
	}
	if( (m_x >= MIN_ROWS) && (m_x +i_level <= MAX_ROWS) && (m_y <=MAX_COLS) && (m_y >= MIN_COLS) ) 
	{
		gotoxy(m_y,m_x+i_level);
		cout<<m_char;
	}
	
	for(int i=1;i<i_length; i++)
	{
		if( (m_x>= MIN_ROWS) && (m_x + i_level <= MAX_ROWS) && (m_y+i<=MAX_COLS) && (m_y >= MIN_COLS) ) 
		{
			gotoxy(m_y+i,m_x+i_level);
			cout<<m_char;
		}
		if( (m_x >= MIN_ROWS) && (m_x + i_level <= MAX_ROWS) && (m_y<=MAX_COLS) && (m_y-i>= MIN_COLS) ) 
		{
			gotoxy(m_y-i, m_x+i_level);
			cout<<m_char;
		}

		if( (m_x - i_level >= MIN_ROWS) && (m_x <= MAX_ROWS) && (m_y+i<=MAX_COLS) && (m_y>= MIN_COLS) ) 
		{
			gotoxy(m_y+i,m_x-i_level);
			cout<<m_char;
		}

		if( (m_x - i_level >= MIN_ROWS) && (m_x <= MAX_ROWS) && (m_y<=MAX_COLS) && (m_y-i>= MIN_COLS) ) 
		{
			gotoxy(m_y-i, m_x-i_level);
			cout<<m_char;
		}
	}
	i_length--;
	if(i_length!=0)
		printNext(i_length, i_level+1);
	
}

void Diamond::drawElectedShape() 
{
	this->drawShape();
}

bool Diamond::isShapeLegal() 
{
	return m_bool;
}

void Diamond::getMovement()
{
	cout<<"please enter a movement (x) and (y), -1<=x|y<=1\n";
	cin>>m_movement.x;
	cin>>m_movement.y;
	while( m_movement.x>1 || m_movement.x<-1 || m_movement.y>1 || m_movement.y<-1 )
	{
		cout<<"wrong input. please enter a value x&y as -1<x<1. example: -1/0.5/-0.3 ...\n";
		cin>>m_movement.x;
		cin>>m_movement.y;
	}

	if(m_movement.x > 0)
	{
		m_compareEachMove.x = 1;
	}
	else
	{
		m_compareEachMove.x = -1;
	}

	if(m_movement.y >0)
	{
		m_compareEachMove.y = 1;
	}
	else
	{
		m_compareEachMove.y = -1;	
	}
	
	m_isGotMove = TRUE;
}

void Diamond::wallCollision(double& i_updateCountX, double& i_countX, double& i_updateCountY, double& i_countY)
{
	if(m_x+m_length==MAX_ROWS+1 || m_x-m_length==MIN_ROWS-1)
	{
		if(m_x+m_length==MAX_ROWS+1)
			decX();
		if (m_x-m_length==MIN_ROWS-1)
			incX();

		i_updateCountX *=0;
		i_countX *=0;
		m_movement.x*=-1;
	}
	if(m_y+m_length==MAX_COLS +1|| m_y-m_length==MIN_COLS-1)
	{
		if(m_y+m_length==MAX_COLS+1)
			decY();
		if(m_y-m_length==MIN_COLS-1)
			incY();

		i_updateCountY*=0;
		i_countY*=0;
		m_movement.y*=-1;
	}

}


void Diamond::updateShape(int i_flag)
{
	m_currMovmentMode.x += m_movement.x;

	if( ( m_currMovmentMode.x > 0 ) && (m_currMovmentMode.x >= m_compareEachMove.x) )
	{
		incX();
		m_compareEachMove.x++;
	}
	else if ( ( m_currMovmentMode.x < 0) && (m_currMovmentMode.x <= m_compareEachMove.x) )
	{
		decX();
		m_compareEachMove.x--;
	}

	m_currMovmentMode.y += m_movement.y;

	if( (m_currMovmentMode.y > 0) && (m_currMovmentMode.y >= m_compareEachMove.y) )
	{
		incY();
		m_compareEachMove.y++;
	}

	else if( ( m_currMovmentMode.y < 0) && (m_currMovmentMode.y <= m_compareEachMove.y) )
	{
		decY();
		m_compareEachMove.y--;
	}

	if(i_flag!=ADD_ANIME)
		wallCollision(m_compareEachMove.x, m_currMovmentMode.x, m_compareEachMove.y, m_currMovmentMode.y);
}
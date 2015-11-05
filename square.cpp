#include "square.h"

/*---------------------------------------------------
Square cpp has the functions which print the squares and recieves the user input and sets it into the sqauare node
-------------------------------------------------*/


void Square::getDateFromUser()		
{
	clrscr();
	int x, y, length;
	char ch;
	cout<<"please enter x, y, length and char\n";
	cin>>x>>y>>length>>ch;
	if(ch!='@')
	{
		m_x = x;
		m_y = y;
		m_length = length;
		m_char = ch;
		
	}
	else
	{
		clrscr();
		cout<<"the sqaure is illegal\n";
		Sleep(TWO_SECONDS);
		clrscr();
		m_bool=FALSE;
	}
}


bool Square::isShapeLegal() // checks if the data we recieved from user is legal and if it's not then we delete the sqaure
{
	return m_bool;
}


void Square::drawShape()		//Draw square draws our sqaure as requested 
{
	
	for(int i = m_x; i< m_x + m_length; i++)
	{
		for (int j = m_y; j < m_y + m_length; j++)
		{
			if( (i==m_x || i== m_x + m_length-1) && ( i>=0 && i<=MAX_ROWS && j>=0 && j<=MAX_COLS) )
			{
				gotoxy(j,i);
				cout<<m_char;
			}
			else if( (j==m_y || j==m_y + m_length -1 ) && ( i>=0 && i<=MAX_ROWS && j>=0 && j<=MAX_COLS) )
			{
				gotoxy(j,i); 
				cout<<m_char;
			}
			else if( i>=0 && i<=MAX_ROWS && j>=0 && j<=MAX_COLS)
			{
				gotoxy(j,i);
				cout<<" ";
			}
		}
	}	
}


void Square::drawElectedShape()  //when we want to move to the secondary menu we print the chosen square in '@'
{
	for(int i = m_x; i< m_x + m_length; i++)
	{
		for (int j = m_y; j < m_y + m_length; j++)
		{
			if( (i==m_x || i== m_x + m_length-1) && ( i>=0 && i<=MAX_ROWS && j>=0 && j<=MAX_COLS) )
			{
				gotoxy(j,i);
				cout<<"@";
			}
			else if( (j==m_y || j==m_y + m_length -1 ) && ( i>=0 && i<=MAX_ROWS && j>=0 && j<=MAX_COLS) )
			{
				gotoxy(j,i); 
				cout<<"@";
			}
			else if( i>=0 && i<=MAX_ROWS && j>=0 && j<=MAX_COLS)
			{
				gotoxy(j,i);
				cout<<" ";
			}
		}
	}	
}

void Square::getMovement()
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



void Square::wallCollision(double& i_updateCountX, double& i_countX, double& i_updateCountY, double& i_countY)
{
	if(m_x+m_length==MAX_ROWS+1 || m_x==MIN_ROWS-1)
	{
		if(m_x==MAX_ROWS+1)
			decX();
		if (m_x==MIN_ROWS-1)
			incX();

		i_updateCountX *=0;
		i_countX *=0;
		m_movement.x*=-1;
	}
	if(m_y+m_length==MAX_COLS +1|| m_y==MIN_COLS-1)
	{
		if(m_y==MAX_COLS+1)
			decY();
		if(m_y==MIN_COLS-1)
			incY();

		i_updateCountY*=0;
		i_countY*=0;
		m_movement.y*=-1;
	}

}


void Square::updateShape(int i_flag)
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
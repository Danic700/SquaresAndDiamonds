
#ifndef _SHAPE_H
#define _SHAPE_H

#include "definitions.h"
using namespace std;

typedef struct Move{
	double x;
	double y;
}move;


class Shape
{
protected:
	int m_length;
	int m_x;
	int m_y;
	char m_char;
	Move m_movement;
	Move m_currMovmentMode;
	Move m_compareEachMove;
	bool m_isGotMove;
public:
	Shape():m_isGotMove(FALSE){m_currMovmentMode.x=0; m_currMovmentMode.y=0;}
	virtual ~Shape(){cout<<"(base) DIS'\n"; Sleep(1500);};
	double getXmove(){return m_movement.x;}
	double getYmove(){return m_movement.y;}
	int get_x(){return m_x;}
	int get_y(){return m_y;}
	int get_length(){return m_length;}
	char get_char(){return m_char;}

	void incX(){m_x++;}  
	void incY(){m_y++;}
	void decX(){m_x--;}
	void decY(){m_y--;}

	bool isGotMove(){return m_isGotMove;}
	virtual void getDateFromUser()=0;  //v
	virtual void drawShape()=0;		//v
	virtual void drawElectedShape()=0;  //v
	virtual void getMovement()=0;    //v
	virtual bool isShapeLegal()=0; //v

	virtual void wallCollision(double& i_updateCountX, double& i_countX, double& i_updateCountY, double& i_countY)=0; //v
	virtual void updateShape(int i_flag)=0;  //v
};



#endif
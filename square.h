#ifndef _SQUARE_H
#define _SQUARE_H

#include "shape.h"
//#include "definitions.h"
using namespace std;


class Square: public Shape
{
	bool m_bool;
public:
	Square(){}
	~Square(){cout<<"deleting (derived) square\n";Sleep(1500);}
	//virtual bool isGotMove(){return ;
	virtual void getDateFromUser();  //v
	virtual void drawShape();		//v
	virtual void drawElectedShape();  //v
	virtual void getMovement();    //v

	virtual void wallCollision(double& i_updateCountX, double& i_countX, double& i_updateCountY, double& i_countY); //v
	virtual void updateShape(int i_flag);  //v
	virtual bool isShapeLegal();
};


/*-------------------therealsquare------------------

typedef struct Move{
	double x;
	double y;
}move


class Square
{
	bool m_bool;
	int m_x;  //-
	int m_y;  //-
	int m_length; //-
	char m_char;  //-
	Move m_movement; //-
	Move m_currMovmentMode; //-
	Move m_compareEachMove; //-
	bool m_isGotMove; //-

public:
	Square():m_bool(TRUE), m_isGotMove(FALSE) {m_currMovmentMode.x=0; m_currMovmentMode.y=0;}
	~Square(){}

	double getXmove(){return m_movement.x;} //-
	double getYmove(){return m_movement.y;}  //-
	int get_x(){return m_x;} //-
	int get_y(){return m_y;} //-
	int get_length(){return m_length;} //-
	char get_char(){return m_char;} //-
	bool isSquareLegal();
	bool isGotMove(){return m_isGotMove;}; //-

	void getDateFromUser();  //v
	void drawSquare();		//v
	void drawElectedSquare();  //v
	void getMovement();    //v
	void incX(){m_x++;}  
	void incY(){m_y++;}
	void decX(){m_x--;}
	void decY(){m_y--;}
	void wallCollision(double& i_updateCountX, double& i_countX, double& i_updateCountY, double& i_countY); //v
	void updateSquare(int i_flag);  //v
	//void drawTry();



};
*/



#endif

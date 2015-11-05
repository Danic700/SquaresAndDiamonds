
#ifndef _DIAMOND_H
#define _DIAMOND_H

#include "shape.h"
//#include "definitions.h"
using namespace std;

class Diamond: public Shape
{
	bool m_bool;
public:
	Diamond(){m_char = '@';}
	virtual ~Diamond(){};
	//virtual bool isGotMove(){return ;
	virtual void getDateFromUser();  //v
	virtual void drawShape();		//v
	virtual void drawElectedShape();  //v
	virtual void getMovement();    //v

	virtual void wallCollision(double& i_updateCountX, double& i_countX, double& i_updateCountY, double& i_countY); //v
	virtual void updateShape(int i_flag);  //v
	virtual bool isShapeLegal();

	void printNext(int i_length, int i_level);
};

#endif;
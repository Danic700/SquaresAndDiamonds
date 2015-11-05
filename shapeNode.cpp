#include "shapeNode.h"
using namespace std;
/*---------------------------------------------------
A square can check whether or not it is intersecting
with another square which is drawn on the screen
with this function
-------------------------------------------------*/

bool ShapeNode::isShapeNodeFound(int i_x ,int i_y) 	
{
	int i; i = this->m_shape->get_x();
	int x; x = this->m_shape->get_x();
	int j; j = this->m_shape->get_y();
	int y; y = this->m_shape->get_y();
	int length = this->m_shape->get_length()-1;
	
	for (i=x; i<x+length+1 ; i++)								
	{
		for(j=y; j<y+length+1; j++)
		{
			if(i_x == i && i_y == j) //checks if pixels from one square are intersecting with another square
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

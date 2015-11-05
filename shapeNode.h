#ifndef _SQN_H
#define _SQN_H

#include "definitions.h"
#include "shape.h"
using namespace std;

class ShapeNode{
public:
	ShapeNode* next;
	ShapeNode* prev;
	Shape* m_shape;

	bool isShapeNodeFound(int i_x ,int i_y);

	~ShapeNode()
	{
		next = NULL;
		prev = NULL;
		delete next;
		delete prev;

		delete m_shape;	//switched
		m_shape = NULL;
		
	}
};

#endif
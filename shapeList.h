#ifndef _LIST_H
#define _LIST_H

#include "shape.h"
#include "definitions.h"
#include "shapeNode.h"
#include "shapeMatrix.h"
#include "square.h"
#include "diamond.h"
using namespace std;


class ShapeList{
	int m_counter;
	ShapeMatrix* m_beforeMatrix;         //we've added these matrixes here to the list, we'll always move the current positions of squares to the matrix and check to see in the next movement where there's been a difference and we'll know what to print and by doing this we prevent ריצודים
	ShapeMatrix* m_afterMatrix;
	ShapeMatrix* m_temp;

public:
	ShapeNode* m_head;
	ShapeNode* m_tail;
	ShapeList(): m_counter(0), m_head(NULL), m_tail(NULL), m_temp(NULL){m_beforeMatrix = new ShapeMatrix, m_afterMatrix = new ShapeMatrix;}
	~ShapeList()
	{
		m_head = NULL; 
		m_tail = NULL;
		delete m_head;
		delete m_tail;
	}

	ShapeNode* findShapeNode(const int& i_x, const int& i_y);
	ShapeNode* findShapeNodeParticular(const ShapeNode& i_curr, const int& i_x, const int& i_y);
	int getCounter()const {return m_counter;}
	int whichMergeForMovements(ShapeNode* i_curr, ShapeNode* i_curr2);

	void initialize_list();
	void addShape(int& shape);
	void deleteShapeNode();
	void moveShapeNodeToEndOfList(ShapeNode* i_curr);
	void drawShapes();
	void incCounter();
	void decCounter();
	void merge(ShapeNode* i_node, int i_x, int i_y);
	void whichMerge(ShapeNode* i_smallNode, ShapeNode* i_bigNode);
	void putListInMatrix(const int& i_status);
	void printThruMatrixComapre();
	void swapMatrixes();
	void moveShapeNodeToHeadOfList(ShapeNode* i_node);
	void deleteMovementsShapes(ShapeNode* i_curr, ShapeNode* i_curr2, int axis);
	void putListInMatrixSpecial(const int& i_status);
	void drawAllSquaresWithMovements();
	void printThruMatrixComapreForSingleAnime();


	
};

#endif
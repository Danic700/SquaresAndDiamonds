#include "shapeList.h"

/*---------------------------------------------------
Squarelist CPP has all the functions regarding the secondary menu along with some other things such as square counter and add square
We decided to use a doubly linked list, this helped us go over the list from tail to head in order to do things as requested
-------------------------------------------------*/


void ShapeList::incCounter()
{
	m_counter++;
}


void  ShapeList::decCounter()
{
	m_counter--;
}


void  ShapeList::addShape(int& shape)				//Add square adds a new square node to the list and makes sure it's set properly and also increases our square counter
{
	if(m_head==NULL)
	{
		ShapeNode* newNode  = NULL;
		if(shape==SQUARE)
		{
			newNode = new ShapeNode;
			newNode->m_shape = new Square; ////---
		}
		else if(shape == DIAMOND)
		{
			newNode = new ShapeNode;
			newNode->m_shape = new Diamond; ////---
		}
		newNode->m_shape->getDateFromUser();  ////---
		m_head = newNode;
		m_tail = newNode;
		newNode->next=NULL;
		newNode->prev=m_head;
	}
	else
	{
		ShapeNode* currNode = m_head;
		while(currNode->next)
		{
			currNode = currNode ->next;
		}
		currNode->next = new ShapeNode;
		if(shape==SQUARE)
		{
			currNode->next->m_shape = new Square;
		}
		else if(shape==DIAMOND)
		{
			currNode->next->m_shape = new Diamond;
		}
		currNode->next->m_shape->getDateFromUser();
		m_tail = currNode->next;
		m_tail->next=NULL;
		m_tail->prev = currNode;
	}
	incCounter();
}


void  ShapeList::deleteShapeNode() //Delete square does exactly the opposite
{
	if(m_tail != m_head)
	{
		ShapeNode* curr = m_tail;
		m_tail = m_tail->prev;
		m_tail->next = NULL;
		delete curr;
	}
	else if (m_tail == m_head)
	{
		ShapeNode* curr = m_tail;
		delete curr;
		m_tail = NULL;
		m_head = NULL;
	}
	decCounter();
}


ShapeNode*  ShapeList::findShapeNode(const int& i_x, const int& i_y)
{
	ShapeNode* curr = m_tail;
	while(!curr->isShapeNodeFound(i_x , i_y) && curr!=m_head) //curr!=m_tail) noooooo
	{
		curr = curr->prev;
	}

	if(curr!=m_head ) //curr!=m_head onlyyyy
	{
		return curr;
	}
	else
	{
		if(!curr->isShapeNodeFound(i_x , i_y))
			return NULL;
		else
			return curr;
	}

}


void ShapeList::moveShapeNodeToEndOfList(ShapeNode* i_curr)
{
	if(m_head == m_tail || i_curr == m_tail)
	{
		return;
	}
	else if(i_curr != m_head)
	{
		ShapeNode* helper = i_curr->prev;
		helper->next = i_curr->next;
		helper->next->prev = helper;
		m_tail->next = i_curr;
		m_tail->next->prev = m_tail;
		i_curr->next = NULL;
		m_tail = i_curr;
	}
	else //if (i_curr==m_head)
	{
		ShapeNode* helper = i_curr->next;
		helper->prev = m_head;
		m_head = helper;
		i_curr->prev = m_tail;
		m_tail->next = i_curr;
		m_tail = i_curr;
		m_tail ->next = NULL;
	}
}


void ShapeList::moveShapeNodeToHeadOfList(ShapeNode* i_node)    //we've added a move to head of list function for when we want to print out stationary squares that dont move so that they'll have the highest priority and they wont get run over by squares that move 
{
	ShapeNode* helper;
	if(m_head == m_tail || i_node == m_head)
	{
		return;
	}

	else if(i_node != m_head && i_node != m_tail)
	{
		
		helper = m_head;
		i_node->prev->next = i_node->next;
		i_node->next->prev = i_node->prev;		
		i_node->prev = NULL;
		i_node->next = NULL;
		
		m_head = i_node;
		m_head->next = helper;
		helper->prev = m_head;
		helper = NULL;
	}
	else if(i_node == m_tail)
	{
		i_node->prev->next = NULL;
		m_tail = i_node->prev;

		helper = m_head;
		m_head = i_node;
		i_node->next = helper;
		helper->prev = m_head;
		helper = NULL;
	}

}


void ShapeList::drawShapes()
{
	clrscr();
	cout<<"the number of existing squares is: "<<m_counter<<endl;
	Sleep(1500);
	clrscr();

	ShapeNode* curr = m_head; 
	while(curr)
		{
			curr->m_shape->drawShape();
			curr=curr->next;
		}
}


void ShapeList::merge(ShapeNode* i_node, int i_x, int i_y)
{
	bool isInside = FALSE;
	clrscr();
	ShapeNode* secShapeNode;
	int firstSquareLengeth, secondeSquareLength, secSqaureX, secSquareY, firstSquareX, firstSquareY, area1, area2;
	firstSquareX = i_node->m_shape->get_x();
	firstSquareY = i_node->m_shape->get_y();
	firstSquareLengeth = i_node->m_shape->get_length();  //getting the length of the first square
	area1 = firstSquareLengeth*firstSquareLengeth; //calculating the area of square1
	cout<<"please enter x anf y for second square: \n";
	cin>> secSqaureX>> secSquareY;
	clrscr();


	secShapeNode = this->findShapeNodeParticular(*i_node,secSqaureX, secSquareY);
	if(secShapeNode)
	{
		secondeSquareLength = secShapeNode->m_shape->get_length(); //getting the length of the second square
		secSqaureX = secShapeNode->m_shape->get_x();  //getting the x of the second square 
		secSquareY = secShapeNode->m_shape->get_y(); //getting the y of the second square
		area2 = secondeSquareLength*secondeSquareLength; //calculating the area of square2

		if(firstSquareLengeth > secondeSquareLength)
		{
			this->whichMerge(secShapeNode, i_node);
		}
		else
		{
			this->whichMerge(i_node , secShapeNode);
		}

	}
		
	else
	{
		cout<<"there is no sqaure in this position!\n";
		Sleep(TWO_SECONDS);
	}
}


void ShapeList::whichMerge(ShapeNode* i_smallNode, ShapeNode* i_bigNode) // in order to find out what merge we need to do (because there are 3 different scenarios) we used a bucket which is the size of the smaller square area to help us calculate
{                                                                           //how this works is we take the smaller of both squares and we scan it to see how many pixels intersect with the other square, and the bucket can return to us 3 different options
	int smallSquareX = i_smallNode->m_shape->get_x();                        // if all the elements in bucket are 0 this means that both squares are not intersecting at all, if there is at least one element which has 1 in the bucket that means there is an intersection and lastly if all the elements in bucket are 1 then the smaller square is contained inside the bigger one
	int smallSquareY = i_smallNode->m_shape->get_y();
	int BucketCounter=0;
	int length = i_smallNode->m_shape->get_length();
	int* HitBucket = new int[length*length];
	for(int i=0; i<length*length; i++)
	{
		HitBucket[i]=0;
	}

	int Bucketindex=0;

	for(int i=smallSquareX; i<smallSquareX+length; i++)
		{
			for(int j=smallSquareY; j<smallSquareY+length; j++)
			{
				HitBucket[Bucketindex] = i_bigNode->isShapeNodeFound(i,j);
				Bucketindex++;
			}
		}

	for (int i = 0; i < length*length; i++)
		{
			if(HitBucket[i]==1)
			{
				BucketCounter++;
			}
		}
	
	if(BucketCounter==0 || BucketCounter==length*length)
		{
			this->moveShapeNodeToEndOfList(i_smallNode);
			this->deleteShapeNode();
			cout<<"establish\n";
			Sleep(ONE_SECOND);
		}

	else
		{
			this->moveShapeNodeToEndOfList(i_bigNode);
			this->deleteShapeNode();
			cout<<"establish\n";
			Sleep(ONE_SECOND);
		}
}


ShapeNode* ShapeList::findShapeNodeParticular(const ShapeNode& i_curr, const int& i_x, const int& i_y)
{
	ShapeNode* curr = m_tail;
	while(curr != m_head)
	{
		if(curr->isShapeNodeFound(i_x, i_y) && curr!= &i_curr)
		{
			return curr;
		}
		else
		{
			curr=curr->prev;
		}
	}

	if(curr == m_head)
	{
		if(curr->isShapeNodeFound(i_x, i_y) && curr!= &i_curr)
		{
			return curr;
		}
		else
		{
			return NULL;
		}
	}

}

 // in order to find out what merge we need to do (because there are 3 different scenarios) we used a bucket which is the size of the smaller square area to help us calculate
//how this works is we take the smaller of both squares and we scan it to see how many pixels intersect with the other square, and the bucket can return to us 3 different options
// if all the elements in bucket are 0 this means that both squares are not intersecting at all, if there is at least one element which has 1 in the bucket that means there is an intersection and lastly if all the elements in bucket are 1 then the smaller square is contained inside the bigger one
	


int ShapeList::whichMergeForMovements(ShapeNode* i_curr, ShapeNode* i_curr2)           //this function takes care of which square do we want to delete when we have two squares moving on our screen, it works by checking collision on the X or Y axis as needed depending on how they hit.
{	

	ShapeNode *smallShape, *bigShape;
	if(i_curr->m_shape->get_length() > i_curr2->m_shape->get_length() )
	{
		smallShape = i_curr2;
		bigShape = i_curr;
	}
	else
	{
		smallShape = i_curr;
		bigShape = i_curr2;
	}

	int x1, x1WithLength;
	int y1, y1WithLength;
	int x2, x2WithLength;
	int y2, y2WithLength;
	
	x1 = i_curr->m_shape->get_x();
	x1WithLength = x1 + i_curr->m_shape->get_length();
	y1 = i_curr->m_shape->get_y();
	y1WithLength = y1 + i_curr->m_shape->get_length();

	x2 = i_curr2->m_shape->get_x();
	x2WithLength = x2 + i_curr2->m_shape->get_length();
	y2 = i_curr2->m_shape->get_y();
	y2WithLength = y2 + i_curr2->m_shape->get_length();

	
	if( abs(x1-x2) == 0 )
	{
		if(! ( ( smallShape->m_shape->get_y() + smallShape->m_shape->get_length() < bigShape->m_shape->get_y() ) || ( smallShape->m_shape->get_y() >  bigShape->m_shape->get_y() + bigShape->m_shape->get_length() ) ))
		{
			cout<<"this1\n";Sleep(2000);
			this->deleteMovementsShapes(i_curr, i_curr2, Y_AXIS);
			return 0;
		}
		
	}

	else if( abs(x1 - x2WithLength) == 0)
	{
		if(! ( ( smallShape->m_shape->get_y() + smallShape->m_shape->get_length() < bigShape->m_shape->get_y() ) || ( smallShape->m_shape->get_y() >  bigShape->m_shape->get_y() + bigShape->m_shape->get_length() ) ))
		{
				cout<<"this2\n";Sleep(2000);
			this->deleteMovementsShapes(i_curr, i_curr2, X_AXIS);
			return 0;
		}
	}

	else if( abs(x1WithLength - x2) == 0)
	{
		if ( !( ( smallShape->m_shape->get_y() + smallShape->m_shape->get_length() < bigShape->m_shape->get_y() ) || ( smallShape->m_shape->get_y() >  bigShape->m_shape->get_y() + bigShape->m_shape->get_length() ) ) )
		{
			cout<<"this3\n";Sleep(2000);
			this->deleteMovementsShapes(i_curr, i_curr2, X_AXIS);
			return 0;
		}
	}

	else if( abs(x1WithLength - x2WithLength) == 0)
	{
		if ( !( ( smallShape->m_shape->get_y() + smallShape->m_shape->get_length() < bigShape->m_shape->get_y() ) || ( smallShape->m_shape->get_y() >  bigShape->m_shape->get_y() + bigShape->m_shape->get_length() ) ) )
		{
			cout<<"this4\n";Sleep(2000);
			this->deleteMovementsShapes(i_curr, i_curr2, X_AXIS);
			return 0;
		}
	}
	
	if( abs(y1-y2) == 0 )
	{
		if( ! ( ( smallShape->m_shape->get_x() + smallShape->m_shape->get_length() < bigShape->m_shape->get_x() ) || ( smallShape->m_shape->get_x() >  bigShape->m_shape->get_x() + bigShape->m_shape->get_length() ) ))
		{
			cout<<"this5\n";Sleep(2000);
			this->deleteMovementsShapes(i_curr, i_curr2, Y_AXIS);
			return 0;
		}
	}

	else if( abs(y1 - y2WithLength) == 0)
	{
		if( !( ( smallShape->m_shape->get_x() + smallShape->m_shape->get_length() < bigShape->m_shape->get_x() ) || ( smallShape->m_shape->get_x() >  bigShape->m_shape->get_x() + bigShape->m_shape->get_length() ) ) )
		{
			cout<<"this6\n";Sleep(2000);
			this->deleteMovementsShapes(i_curr, i_curr2, Y_AXIS);
			return 0;
		}
	}

	else if( abs(y1WithLength - y2) == 0)
	{
		if(!( ( smallShape->m_shape->get_x() + smallShape->m_shape->get_length() < bigShape->m_shape->get_x() ) || ( smallShape->m_shape->get_x() >  bigShape->m_shape->get_x() + bigShape->m_shape->get_length() ) ) )
		{
			cout<<"this7\n";Sleep(2000);
			this->deleteMovementsShapes(i_curr, i_curr2, Y_AXIS);
			return 0;
		}
	}

	else if( abs(y1WithLength - y2WithLength) == 0)
	{
		if(!( ( smallShape->m_shape->get_x() + smallShape->m_shape->get_length() < bigShape->m_shape->get_x() ) || ( smallShape->m_shape->get_x() >  bigShape->m_shape->get_x() + bigShape->m_shape->get_length() ) ) )
		{
			cout<<"this8\n";Sleep(2000);
			this->deleteMovementsShapes(i_curr, i_curr2, Y_AXIS);
			return 0;
		}
	}
	return 1;
	
}




void ShapeList::deleteMovementsShapes(ShapeNode* i_curr, ShapeNode* i_curr2, int axis)  //after there has been a collision between two moving squares we'll go here and delete the appropriate square, along with the DO RE ME FA SOL LA SI DO..
{
	Sleep(ONE_SECOND);
	  Beep(523,500); Beep(587,500); Beep(659,500); Beep(698,500);  Beep(784,500); Beep(870,500); Beep(978,500); Beep(1070,500);// 523 hertz (C5) for 500 milliseconds
 
	double curr1Speed, curr2Speed;
	int length1 = i_curr->m_shape->get_length();
	int length2 = i_curr2->m_shape->get_length();
	if(axis == X_AXIS)
	{
		curr1Speed = abs( i_curr->m_shape->getXmove() );
		curr2Speed = abs( i_curr2->m_shape->getXmove() );
	}
	else
	{
		curr1Speed = abs(i_curr->m_shape->getYmove() );
		curr2Speed = abs( i_curr2->m_shape->getYmove() );
	}
	if( ( length1 < length2 ) && (curr2Speed < curr1Speed) ) //if square 1 is smaller and faster- delete  2nd one
	{
		this->moveShapeNodeToEndOfList(i_curr2);
		this->deleteShapeNode();
	}	
	else if( ( length2 < length1 ) && (curr2Speed > curr1Speed) ) //if sqaure 2 is smaller and faster - delete the 1st one
	{

		this->moveShapeNodeToEndOfList(i_curr);
		this->deleteShapeNode();
	}	
	else if( ( length2 < length1 ) && (curr2Speed < curr1Speed) ) //...
	{
		this->moveShapeNodeToEndOfList(i_curr2);
		this->deleteShapeNode();
	}
	else if( ( length2 > length1 ) && (curr2Speed > curr1Speed) ) //...
	{
		this->moveShapeNodeToEndOfList(i_curr);
		this->deleteShapeNode();
	}
	else if( curr2Speed == curr1Speed ) //...
	{
		if ( length2 > length1 )
		{
			this->moveShapeNodeToEndOfList(i_curr);
			this->deleteShapeNode();
		}
		else
		{
			this->moveShapeNodeToEndOfList(i_curr2);
			this->deleteShapeNode();
		}
	}
	else 
	{
		this->moveShapeNodeToEndOfList(i_curr); //...
		this->deleteShapeNode();
	}
}

//--------------------------------------------------------------------------------------------------


														
void ShapeList::putListInMatrix(const int& i_status) //we take all the squares and put them in the matrix..
{
	if(i_status == AFTER)
		m_afterMatrix->initializeMatrix();
	int x, y, length;
	char ch;
	ShapeNode* curr = m_head;
	while(curr)
	{
		x = curr->m_shape->get_x();
		y = curr->m_shape->get_y();
		ch = curr->m_shape->get_char();
		length = curr->m_shape->get_length();
		if(i_status == AFTER)
			m_afterMatrix->putCharInMatrix(ch, x, y, length);
		else
			m_beforeMatrix->putCharInMatrix(ch, x, y, length);
		curr=curr->next;
	}
}



void ShapeList::printThruMatrixComapre()      //here we compare the two matrixes and we see what we'll be printing
{

	for(int i=MIN_ROWS; i<=MAX_ROWS; i++)
	{
		for(int j=MIN_COLS; j<=MAX_COLS; j++)
		{
			if(m_beforeMatrix->getChar(i,j) != m_afterMatrix->getChar(i,j) )
			{
				if(m_beforeMatrix->getChar(i,j) != ' ')
				{
					gotoxy(j,i);
					cout<<' ';
					
				}
				else if(m_beforeMatrix->getChar(i,j) == ' ')
				{
					gotoxy(j,i);
					cout<<m_afterMatrix->getChar(i,j);
				}
			}
		
		}
	}
}


void ShapeList::swapMatrixes()   //after each output to the screen the after matrix becomes the before matrix and the before matrix becomes the after matrix 
{
	m_temp = m_afterMatrix;
	m_afterMatrix = m_beforeMatrix;
	m_beforeMatrix = m_temp;
	m_temp = NULL;
	
}


void ShapeList::putListInMatrixSpecial(const int& i_status)
{
	if(i_status == AFTER)
		m_afterMatrix->initializeMatrix(); 
	int x, y, length;
	char ch;
	ShapeNode* curr = m_head;
	while(curr)
	{
		x = curr->m_shape->get_x();
		y = curr->m_shape->get_y();
		ch = curr->m_shape->get_char();
		length = curr->m_shape->get_length();
		if(curr->m_shape->isGotMove() && (i_status == AFTER) )
			m_afterMatrix->putCharInMatrix(ch, x, y, length);
		else if (curr->m_shape->isGotMove() && (i_status == BEFORE) )
			m_beforeMatrix->putCharInMatrix(ch, x, y, length);
		curr=curr->next;
	}
}


void ShapeList::drawAllSquaresWithMovements()
{
	ShapeNode* helper;
	clrscr();
	char charForDone = 0;
	ShapeNode* curr = m_head;
		this->putListInMatrix(AFTER);
			

	if(curr)
	{
		
		while(charForDone != ESC)
		{
			if(kbhit() )
				charForDone = getch();
			
			//while(curr->next!=NULL)
			while(curr)
			{
				if(curr->m_shape->isGotMove() )
				{
					helper = curr;
					curr->m_shape->updateShape(ADD_DOUBLE_ANIME);
					curr = curr->next;
					this->moveShapeNodeToHeadOfList(helper);
				}
				else
				{
					curr = curr->next;
				}
			}
			
			if(!curr)
				curr = m_head;

			this->putListInMatrix(AFTER);
			this->printThruMatrixComapre();
			this->swapMatrixes(); 

			
			Sleep(TENTH_SECOND);
		}
	}
	
}

#include "game.h"
#include "shapeList.h"

/*---------------------------------------------------
The menu is taken care of in game cpp, it recieves all the input from the user and according to what input is we got we'll go to the desired menu or  
-------------------------------------------------*/

void Game::startGame()					//we implemented cases for all the different options 
{
	system("color 0B");
	while(m_menu.getInput() != END_GAME)
	{
		clrscr();
		m_menu.openPrimeMenu();	
		switch( m_menu.getInput() )
		{
		case(ADD_SHAPE):
			{
				int n;
				clrscr();
				cout<<"please enter- (1)square (2)diamond\n";
				cin>>n;
				m_list.addShape(n);
					if (!m_list.m_tail->m_shape->isShapeLegal() )		
						m_list.deleteShapeNode();
					else 
					{
						m_list.drawShapes();
						this->escMoment();
					}
				
			}break;
		case(DRAW_SQUARES):
			{
				if(m_list.getCounter()>0)			
					m_list.drawAllSquaresWithMovements();
				else
				{
					cout<<"there are no squares\n";
					Sleep(TWO_SECONDS);
				}
			}break;
		case(PICK_SQUARE):
			{
				if(m_list.getCounter()>0)
				{
					m_menu.getInputForSecMenu();
					m_curr = m_list.findShapeNode( m_menu.getXForSecMenu(), m_menu.getYForSecMenu() );
					if(m_curr!=NULL)
					{
						m_list.drawShapes();
						m_curr->m_shape->drawElectedShape();
						if( m_menu.isInConsoleLimits() ) //getXForSecMenu() >= 0 && m_menu.getXForSecMenu() <= MAX_ROWS && m_menu.getYForSecMenu() >= 0 && m_menu.getYForSecMenu() <= MAX_COLS)
							m_menu.blinkMatchingCoord();
						else
							this->escMoment();
						this->activateSecMenu();
					}
					else
					{
						m_list.drawShapes();
						m_menu.blinkMatchingCoord();
					}
				}
				else
				{
					cout<<"there are no sqaures\n";
					Sleep(TWO_SECONDS);
				}
			}break;
		}
	}
}

void Game::activateSecMenu() //opens up the secondary menu for you and like the first menu we used switch case
{
	m_menu.openSecMenu();
	switch( m_menu.getInput() )
	{
	case(CANCEL):
		{
			m_list.drawShapes();
			this->escMoment();
		}break;
	case(DELETER):
		{
			m_list.moveShapeNodeToEndOfList(m_curr);
			m_list.deleteShapeNode();
			
		}break;
	case(MOVE_UP):
		{
			m_list.moveShapeNodeToEndOfList(m_curr);
		}break;
	case(MERGE):
		{
			m_list.merge( m_curr, m_curr->m_shape->get_x(), m_curr->m_shape->get_y() );    
		}break; 
	case(ADD_ANIME):                              //we've added  a new case if you want to animate a single square and see it go out of the borders
		{
			char charForDone = 0;
			clrscr();

			m_curr->m_shape->getMovement();
			clrscr();
			m_list.putListInMatrixSpecial(BEFORE);
			
			while(charForDone!=ESC)
			{
				if(kbhit() )
				{
					charForDone = getch();
				}
				m_curr->m_shape->updateShape(ADD_ANIME);
				m_list.putListInMatrixSpecial(AFTER);
				m_list.printThruMatrixComapre();
				m_list.swapMatrixes();
				
				Sleep(TENTH_SECOND);
			}
			clrscr();

			this->activateSecMenu();
		}break;

	case(ADD_DOUBLE_ANIME):                              //and this is the other new case which takes care of animating two squares with collision and they stay within the borders 
		{
			this->activeDoubleAnime();
		}break;
	}
}


void Game::activeDoubleAnime()
{
	char charForDone = 0;
	clrscr();
	cout<<"for the 2nd square-\n";
	m_menu.getInputForSecMenu();
	m_curr2 = m_list.findShapeNode( m_menu.getXForSecMenu(), m_menu.getYForSecMenu() );

	if(m_curr2)
	{
		cout<<"for the 1st sqaure-\n";
		m_curr->m_shape->getMovement();
		cout<<"\nfor  the 2nd square-\n";
		m_curr2->m_shape->getMovement();
		clrscr();
		

		if(m_curr->m_shape->get_x() < MIN_ROWS || ( m_curr->m_shape->get_x() + m_curr->m_shape->get_length() >MAX_ROWS) || m_curr->m_shape->get_y() < MIN_COLS || m_curr->m_shape->get_y() + m_curr->m_shape->get_length() > MAX_COLS 
			|| m_curr2->m_shape->get_x() < MIN_ROWS || ( m_curr2->m_shape->get_x() + m_curr2->m_shape->get_length() > MAX_ROWS) || m_curr2->m_shape->get_y() < MIN_COLS || m_curr2->m_shape->get_y() + m_curr2->m_shape->get_length() > MAX_COLS )
			throw("out of borders");
												//we've added an  exception here that appears if you try to move a sqaure thats on the border or passing it..	 
		if(m_curr != m_curr2)
		{
			this->handleDoubleAnimeCase();                   // and also if you dont choose a square in the right coordinate or you choose the same square by accident it will be ok
		}
		else
		{
			clrscr();
			cout<<"You can't choose the same square Twice\n";
			Sleep(TWO_SECONDS);
			clrscr();
		}
	}
	else
	{
		clrscr();
		cout<<"there is no Square at this location\n";
		Sleep(TWO_SECONDS);
		clrscr();
	}
}


void Game::handleDoubleAnimeCase()       //when we were working on the double anime we used two escapes.. this means that if you want to quit the double anime before the squares collided you'll have to hit esc twice, it was more comfortable for us to work like this    
{
	char charForDone = 0;
	double curr1Speed= ( abs(m_curr->m_shape->getXmove() ) + abs( m_curr->m_shape->getYmove() ) );
	double curr2Speed= ( abs(m_curr2->m_shape->getXmove() ) + abs( m_curr2->m_shape->getYmove() ) );
	int len1 = m_curr->m_shape->get_length();
	int len2 = m_curr2->m_shape->get_length();

		
	m_list.putListInMatrixSpecial(BEFORE);
	
	while(charForDone!=ESC && m_list.whichMergeForMovements(m_curr, m_curr2) )
	{
		if(kbhit() )
		{
			charForDone = getch();
		}
		m_curr->m_shape->updateShape(ADD_DOUBLE_ANIME);
		m_curr2->m_shape->updateShape(ADD_DOUBLE_ANIME);
	
		m_list.putListInMatrixSpecial(AFTER);
		m_list.printThruMatrixComapre();
		m_list.swapMatrixes();
					
		Sleep(TENTH_SECOND);
	}
	//	Sleep(2000);
	clrscr(); 
	
	m_list.putListInMatrixSpecial(BEFORE);

	

	/* TODO:: FIX IT
	charForDone = 0;
	while(charForDone!=ESC)
	{
		if(kbhit() )
			charForDone = getch();
		if(m_curr2->m_shape)
		{
			cout<<"got here to the first\n" ;Sleep(1000);
			m_curr2->m_shape->updateShape(ADD_DOUBLE_ANIME);
		}
		if(m_curr->m_shape)
		{
			cout<<"got here to the second\n" ;Sleep(1000);
			//m_curr->m_shape->updateShape(ADD_DOUBLE_ANIME);
		}
	
		m_list.putListInMatrixSpecial(AFTER);
		m_list.printThruMatrixComapre();
		m_list.swapMatrixes();
		Sleep(TENTH_SECOND);
	}
	*/
	
	clrscr();
}


void Game::drawSquares()    //drawsquares function goes over the list we defined in game.h and prints it 
{
	clrscr();
	cout<<"number of existing squares: "<<m_list.getCounter();
	Sleep(ONE_SECOND);
	clrscr();

	ShapeNode* curr = m_list.m_head;
	while(curr)
		{
			curr->m_shape->drawShape();
			curr=curr->next;
		}
}


void Game::escMoment() // takes care of esc so you can go back to whatever menu you are on after printing the squares on screen
{
	char charForDone=0;
	while(charForDone!=ESC)
		{
			kbhit();
			charForDone = getch();

		}
	clrscr();
}

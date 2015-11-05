#include "menu.h"

/*---------------------------------------------------
menu cpp has the functions which have to do with user interface interaction
-------------------------------------------------*/

void Menu::openPrimeMenu() //takes care of main menu
{
	cout<<"Please choose an option: \n(1) Create a new Shape \n(2) Print all squares \n(3)Choose a spot \n(8)Quit\n";
	cin>>m_input;
	while( m_input!=ADD_SHAPE && m_input!=DRAW_SQUARES && m_input!= PICK_SQUARE && m_input!= END_GAME) 
	{


		clrscr();
		throw(ERROR);
		cout<<"Input is Ivalid.\nPlease choose an option: \n(1) Create a new Square \n(2) Print all squares \n(3)Choose a spot \n(8)Quit\n";
		cin>>m_input;
	}
}


void Menu::getInputForSecMenu() // asks the user for coordinates to get into the secondary menu
{
	cout<<"Please enter x and y coords :\n";
	cin>>m_xInputForSecMenu>>m_yInputForSecMenu;
}


void Menu::openSecMenu() // this lets the user know that they are in the second menu
{
	cout<<"Please choose an option: \n(1) Cancel \n(2) Delete Square \n(3)Move to top \n(4)Merge \n(5)Add Animation \n(6)Add 2 Animations \n";
	cin>>m_input;
	while( m_input!=CANCEL && m_input!=DELETER && m_input!=MOVE_UP && m_input!= MERGE && m_input!= ADD_ANIME && m_input!=ADD_DOUBLE_ANIME) 
	{
		clrscr();
		cout<<"Input is Ivalid..\n\nPlease choose an option: \n(1) Cancel \n(2) Delete Square \n(3)Move to top \n(4)Merge \n(5)Add \n(6)Add 2 Animations\n ";
		cin>>m_input;
	}
}

//This function goes to the requested coordinate and prints out a blinking '@'
void Menu::blinkMatchingCoord()						
{
	gotoxy(m_yInputForSecMenu, m_xInputForSecMenu);
	
	char charForDone=0;
	while(charForDone!=ESC)
		{
			if(kbhit() )
				charForDone = getch();
			gotoxy(m_yInputForSecMenu, m_xInputForSecMenu); 
			cout<<" ";
			Sleep(BLING_TIME);
			gotoxy(m_yInputForSecMenu, m_xInputForSecMenu); 
			cout<<"@";
			Sleep(BLING_TIME);
		}
	clrscr();
}


bool Menu::isInConsoleLimits()  // this func makes sure that the printing is done in within the borders
{
	if(m_xInputForSecMenu >= 0 && m_xInputForSecMenu <= MAX_ROWS && m_yInputForSecMenu >= 0 && m_yInputForSecMenu <= MAX_COLS)
	{
		return TRUE;
	}
	return FALSE;
}

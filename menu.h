#ifndef _MENU_H
#define _MENU_H

#include "definitions.h"
using namespace std;

class Menu
{
	int m_input;
	int m_xInputForSecMenu;
	int m_yInputForSecMenu;
public:
	Menu():m_input(0){}
	~Menu(){}

	int getXForSecMenu(){return m_xInputForSecMenu;}
	int getYForSecMenu(){return m_yInputForSecMenu;}
	int getInput(){return m_input;}
	bool isInConsoleLimits();
	void openPrimeMenu();
	void openSecMenu();
	void getInputForSecMenu();
	void blinkMatchingCoord();
	
};

#endif
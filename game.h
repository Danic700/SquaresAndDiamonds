#ifndef _GAME_H
#define _GAME_H

//#include "square.h"
#include "menu.h"
#include "shapeList.h"
using namespace std;

class Game
{
	Menu m_menu;
	ShapeList m_list;
	ShapeNode* m_curr;
	ShapeNode* m_curr2;

	void initialize_array();
public:
	Game(){}
	~Game()
	{
		m_curr = NULL;
		delete m_curr;
	}

	void startGame();
	void activateSecMenu();
	void drawSquares();
	void escMoment();
	void handleDoubleAnimeCase();
	void activeDoubleAnime();
};

#endif
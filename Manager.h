#include "game.h"
#include "definitions.h"
using namespace std;

class Manager
{
	Game game;
public:
	void begin(){game.startGame() ;}
};

#include<iostream>
#include<fstream>
#include <string.h>
#include <Windows.h>
#include "game.h";

#include "Manager.h"

/*---------------------------------------------------
Main
-------------------------------------------------*/

void main()
{
	Manager game;
	try
	{
		game.begin();
	}
	catch(int num)
	{
		cout<<"invalid input, exception\n";
	}
	catch(string n)
	{
		cout<<"Error. both squares should be in the borders\n";
	}
}
#include "Levels.h"

void renderSelectLevel()
{
	COORD c = g_Console.getConsoleSize();
	c.Y = 0;
	c.X = 0;

	string sym;
	ifstream myfile("levelselection.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x0B);
			c.Y++;
		}
		myfile.close();
	}

	renderArrow();
	moveArrow();
	SelectLevel();
}
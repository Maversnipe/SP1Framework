#include "game.h"
extern Console g_Console;
extern SGameChar g_sChar;

void renderselectscreen()
{
	COORD c = g_Console.getConsoleSize();
	c.Y = 4;
	c.X = 7;

	string sym;
	ifstream myfile("levelselection.txt");

	if (myfile.is_open()){
		while (getline(myfile, sym)) {
			g_Console.writeToBuffer(c, sym, 0x0B);
			c.Y++;
		}
		myfile.close();
	}
	selectlevel();
}

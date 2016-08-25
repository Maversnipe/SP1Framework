#include "Story.h"
extern Console g_Console;
#include <iostream>

void StoryEight()
{
	g_Console.clearBuffer(0x17);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("StoryEight.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x17);
			c.Y++;
		}
		myfile.close();
	}
}
#include "Story.h"
extern Console g_Console;
#include <iostream>

void StoryOne()
{
	g_Console.clearBuffer(0x27);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("StoryOne.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x27);
			c.Y++;
		}
		myfile.close();
	}
}
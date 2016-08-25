#include "Story.h"
extern Console g_Console;
#include <iostream>
extern EGAMESTATES g_eGameState;
extern bool g_abKeyPressed[K_COUNT];

void StoryEnd()
{
	g_Console.clearBuffer(0x27);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("StoryLast.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x27);
			c.Y++;
		}
		myfile.close();
	}
	c.X = 25;
	c.Y = 20;

	ostringstream ss;
	ss.str("");
	ss << "You've finished the game.";
	g_Console.writeToBuffer(c, ss.str(), 0x2F);
	ss.str("");
	ss << "Press ENTER to proceed to the Leaderboard.";
	g_Console.writeToBuffer(c.X, c.Y + 2, ss.str(), 0x2F);
	ss.str("");
	ss << "Press SPACE to go back to the main menu.";
	g_Console.writeToBuffer(c.X, c.Y + 4, ss.str(), 0x2F);

	if (g_abKeyPressed[K_ENTER]){
		charSpawn();
		g_eGameState = S_LEADERBOARD;
	}

	if (g_abKeyPressed[K_SPACE]){
		g_eGameState = S_SPLASHSCREEN;
	}
}
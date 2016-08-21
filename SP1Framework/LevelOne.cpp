#include "Levels.h"
extern Console g_Console;
extern SGameChar g_sChar;
//extern char MapOne[100][100];
#include <iostream>

void LevelOne()
{
	COORD c;
	c.Y = 0;
	c.X = 0;
	extern char Map[20][100][100];
	ifstream File("LevelOne.txt");

	if (File.is_open())
	{
		for (int Rows = 0; Rows < 25; Rows++)
		{
			for (int Columns = 0; Columns < 55; Columns++)
			{
				File >> Map[1][Rows][Columns];
			}
		}
		File.close();
	}
}
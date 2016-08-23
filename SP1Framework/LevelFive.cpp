#include "Levels.h"
extern Console g_Console;
#include <iostream>
extern char Map[20][100][100];
extern SGameChar g_sChar;

void LevelFive()
{
	COORD c;
	c.Y = 0;
	c.X = 0;

	ifstream File("LevelFive.txt");

	if (File.is_open())
	{
		for (int Rows = 0; Rows < 24; Rows++)
		{
			for (int Columns = 0; Columns < 55; Columns++)
			{
				File >> Map[5][Rows][Columns];
			}
		}
		File.close();
	}
}
#include "LevelOne.h"
extern Console g_Console;
extern SGameChar g_sChar;
extern char MapOne[100][100];
#include <iostream>

void LevelOne()
{
	COORD c;
	c.Y = 0;
	c.X = 0;
	moveCharacter();
	extern char Map[100][100];
	ifstream File("LevelOne.txt");

	if (File.is_open())
	{
		for (int Rows = 0; Rows < 25; Rows++)
		{
			for (int Columns = 0; Columns < 55; Columns++)
			{
				File >> MapOne[Rows][Columns];
			}
		}
		File.close();
		for (int Rows = 0; Rows < 24; Rows++)
		{
			c.Y = Rows;
			for (int Columns = 0; Columns < 55; Columns++)
			{
				if (Map[Rows][Columns] == 'i')
				{
					Map[Rows][Columns] = ' ';
				}
				c.X = Columns;
				g_Console.writeToBuffer(c, Map[Rows][Columns], 0x0A);
			}
		}
	}
}
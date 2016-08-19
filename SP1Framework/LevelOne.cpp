#include "LevelOne.h"
extern Console g_Console;
#include <iostream>

void LevelOne()
{
	bool LevelOneChecker = true;
	COORD c;
	c.Y = 0;
	c.X = 0;
	extern char Map[100][100];
	ifstream File("LevelOne.txt");

	if (File.is_open() && LevelOneChecker == true)
	{
		for (int Rows = 0; Rows < 24; Rows++)
		{
			for (int Columns = 0; Columns < 55; Columns++)
			{
				File >> Map[Rows][Columns];
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
		LevelOneChecker = false;
	}
}
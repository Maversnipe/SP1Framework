#include "Levels.h"
extern Console g_Console;
#include <iostream>

void LevelSeven()
{
	COORD c;
	c.Y = 0;
	c.X = 0;
	extern char Map[20][100][100];
	ifstream File("LevelSeven.txt");

	if (File.is_open())
	{
		for (int Rows = 0; Rows < 24; Rows++)
		{
			for (int Columns = 0; Columns < 55; Columns++)
			{
				File >> Map[7][Rows][Columns];
			}
		}
		File.close();
		/*for (int Rows = 0; Rows < 24; Rows++)
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
		}*/
	}
}
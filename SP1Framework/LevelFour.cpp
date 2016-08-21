#include "Levels.h"
extern Console g_Console;
#include <iostream>

void LevelFour()
{
	COORD c;
	c.Y = 0;
	c.X = 0;
	extern char Map[20][100][100];
	ifstream File("LevelFour.txt");

	if (File.is_open())
	{
		for (int Rows = 0; Rows < 24; Rows++)
		{
			for (int Columns = 0; Columns < 55; Columns++)
			{
				File >> Map[4][Rows][Columns];
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

				if (Map[Rows][Columns] == '1' || Map[Rows][Columns] == '2' || Map[Rows][Columns] == '5'){
					g_Console.writeToBuffer(c, Map[Rows][Columns], 0x0E);
				}
			}
		}
		c.Y = 0;
		c.X = 0;
		g_Console.writeToBuffer(c.X + 12, c.Y + 15, (char)210, 0x0F);
		g_Console.writeToBuffer(c.X + 53, c.Y + 5, (char)158, 0x0E);*/
	}
}
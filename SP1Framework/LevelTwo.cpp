#include "LevelTwo.h"
extern Console g_Console;
#include <iostream>

void LevelTwo()
{
	COORD c;
	c.Y = 0;
	c.X = 0;
	extern char Map[100][100];
	ifstream File("LevelTwo.txt");

	if (File.is_open())
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

				if (Map[Rows][Columns] == 'r'){
					g_Console.writeToBuffer(c, Map[Rows][Columns], 0x0B);
				}
			}
		}
	}

	// ======== Pick-em-up =========
	g_Console.writeToBuffer(c.X - 9, c.Y - 14, "1", 0x0F);
	g_Console.writeToBuffer(c.X - 29, c.Y - 14, "1", 0x0F);
	g_Console.writeToBuffer(c.X - 8, c.Y - 6, "1", 0x0F);
	g_Console.writeToBuffer(c.X - 13, c.Y - 5, "5", 0x0E);
	g_Console.writeToBuffer(c.X - 13, c.Y - 6, "2", 0x0F);
	g_Console.writeToBuffer(c.X - 14, c.Y - 5, "1", 0x0F);
	g_Console.writeToBuffer(c.X - 12, c.Y - 5, "1", 0x0F);
	g_Console.writeToBuffer(c.X - 25, c.Y - 1, (char)210, 0x0F);
	g_Console.writeToBuffer(c.X - 47, c.Y - 4, (char)233, 0x0F);
	g_Console.writeToBuffer(c.X - 47, c.Y - 10, (char)233, 0x0F);
	g_Console.writeToBuffer(c.X - 47, c.Y - 12, (char)233, 0x0F);
	g_Console.writeToBuffer(c.X - 1, c.Y - 3, "T", 0x0A);
	g_Console.writeToBuffer(c.X - 47, c.Y - 17, "T", 0x0A);
	g_Console.writeToBuffer(c.X - 46, c.Y - 17, "T", 0x0A);
	g_Console.writeToBuffer(c.X - 45, c.Y - 17, "T", 0x0A);
	g_Console.writeToBuffer(c.X - 44, c.Y - 17, "T", 0x0A);
	g_Console.writeToBuffer(c.X - 42, c.Y - 16, "T", 0x0A);
	g_Console.writeToBuffer(c.X - 43, c.Y - 16, "T", 0x0A);
	g_Console.writeToBuffer(c.X - 44, c.Y - 16, "T", 0x0A);

	g_Console.writeToBuffer(c.X - 50, c.Y - 19, "T", 0x0A);
	g_Console.writeToBuffer(c.X - 49, c.Y - 19, "T", 0x0A);
	g_Console.writeToBuffer(c.X - 48, c.Y - 19, "T", 0x0A);
	g_Console.writeToBuffer(c.X - 47, c.Y - 19, "T", 0x0A);
	g_Console.writeToBuffer(c.X - 46, c.Y - 19, "T", 0x0A);
	g_Console.writeToBuffer(c.X - 45, c.Y - 19, "T", 0x0A);
	g_Console.writeToBuffer(c.X - 44, c.Y - 19, "T", 0x0A);
	g_Console.writeToBuffer(c.X - 43, c.Y - 19, "T", 0x0A);
	g_Console.writeToBuffer(c.X - 50, c.Y - 18, (char)225, 0x0F);
}
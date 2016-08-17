#include "LevelOne.h"
extern Console g_Console;
#include <iostream>
using namespace std;

void LevelOne()
{
	COORD c;
	c.Y = 0;
	c.X = 0;
	char LevelOne[22][52];
	std::ifstream File("LevelOne.txt");

	if (File.is_open())
	{
		for (int Rows = 0; Rows < 21; Rows++)
		{
			for (int Columns = 0; Columns < 52; Columns++)
			{
				File >> LevelOne[Rows][Columns];
			}
		}
		File.close();
		for (int Rows = 0; Rows < 21; Rows++)
		{
			c.Y = Rows + 3;
			for (int Columns = 0; Columns < 52; Columns++)
			{
				if (LevelOne[Rows][Columns] == 'i')
				{
					LevelOne[Rows][Columns] = ' ';
				}
				c.X = Columns + 3;
				g_Console.writeToBuffer(c, LevelOne[Rows][Columns], 0x0A);
			}
		}
	}
}
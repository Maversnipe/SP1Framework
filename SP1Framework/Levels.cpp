#include "Levels.h"
extern Console g_Console;

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

void LevelTwo()
{
	COORD c;
	c.Y = 0;
	c.X = 0;
	extern char Map[20][100][100];
	ifstream File("LevelTwo.txt");

	if (File.is_open())
	{
		for (int Rows = 0; Rows < 24; Rows++)
		{
			for (int Columns = 0; Columns < 55; Columns++)
			{
				File >> Map[2][Rows][Columns];
			}
		}
		File.close();
	}
}

void LevelThree()
{
	COORD c;
	c.Y = 0;
	c.X = 0;
	extern char Map[20][100][100];
	ifstream File("LevelThree.txt");

	if (File.is_open())
	{
		for (int Rows = 0; Rows < 24; Rows++)
		{
			for (int Columns = 0; Columns < 55; Columns++)
			{
				File >> Map[3][Rows][Columns];
			}
		}
		File.close();
	}
}

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
	}
}

void LevelFive()
{
	COORD c;
	c.Y = 0;
	c.X = 0;
	extern char Map[20][100][100];

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

void LevelSix()
{
	COORD c;
	c.Y = 0;
	c.X = 0;
	extern char Map[20][100][100];
	ifstream File("LevelSix.txt");

	if (File.is_open())
	{
		for (int Rows = 0; Rows < 24; Rows++)
		{
			for (int Columns = 0; Columns < 55; Columns++)
			{
				File >> Map[6][Rows][Columns];
			}
		}
		File.close();
	}
}

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
	}
}

void LevelEight()
{
	COORD c;
	c.Y = 0;
	c.X = 0;
	extern char Map[20][100][100];
	ifstream File("LevelEight.txt");

	if (File.is_open())
	{
		for (int Rows = 0; Rows < 24; Rows++)
		{
			for (int Columns = 0; Columns < 55; Columns++)
			{
				File >> Map[8][Rows][Columns];
			}
		}
		File.close();
	}
}

void LevelNine()
{
	COORD c;
	c.Y = 0;
	c.X = 0;
	extern char Map[20][100][100];
	ifstream File("LevelNine.txt");

	if (File.is_open())
	{
		for (int Rows = 0; Rows < 24; Rows++)
		{
			for (int Columns = 0; Columns < 55; Columns++)
			{
				File >> Map[9][Rows][Columns];
			}
		}
		File.close();
	}
}

void LevelTen()
{
	COORD c;
	c.Y = 0;
	c.X = 0;
	extern char Map[20][100][100];
	ifstream File("LevelTen.txt");

	if (File.is_open())
	{
		for (int Rows = 0; Rows < 24; Rows++)
		{
			for (int Columns = 0; Columns < 55; Columns++)
			{
				File >> Map[10][Rows][Columns];
			}
		}
		File.close();
	}
}

void BonusRoom(){
	extern bool bonusTimeKey;
	bonusTimeKey = false;

	COORD c;
	c.Y = 0;
	c.X = 0;
	extern char Map[20][100][100];
	extern int g_dTotalPoints;

	for (int Levels = 11; Levels < 16; Levels++)
	{
		ifstream File("bonusroom.txt");
		if (File.is_open())
		{
			for (int Rows = 0; Rows < 25; Rows++)
			{
				for (int Columns = 0; Columns < 55; Columns++)
				{
					File >> Map[Levels][Rows][Columns];
				}
			}
			File.close();
		}
	}
}
#include "Levels.h"
extern Console g_Console;
extern SGameChar g_sChar;
//extern char MapBonus[100][100];
extern char Map[20][100][100];
extern bool bonusTimeKey;

void BonusRoom(){
	bonusTimeKey = false;

	COORD c;
	c.Y = 0;
	c.X = 0;
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
	
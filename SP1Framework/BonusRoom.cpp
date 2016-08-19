#include "BonusRoom.h"
extern Console g_Console;
extern SGameChar g_sChar;

void BonusRoom(){
	COORD c;
	c.Y = 0;
	c.X = 0;
	extern char Map[100][100];
	extern int g_dTotalPoints;
	ifstream File("bonusroom.txt");

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
				pointSystem();
				c.X = Columns;
				g_Console.writeToBuffer(c, Map[Rows][Columns], 0x0B);
			}
		}
		if (Map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == 'A'){
			g_dTotalPoints = g_dTotalPoints + 50;
		}

	}
}
	
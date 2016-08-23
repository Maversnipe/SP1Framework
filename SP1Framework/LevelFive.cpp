#include "Levels.h"
extern Console g_Console;
#include <iostream>
extern char Map[20][100][100];
extern SGameChar g_sChar;
extern double dt;
extern double g_dDoorTime;
extern double g_dElapsedTime;

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

void doorSwitchFive(){
	if ((Map[5][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X]) == '&')
	{
		g_dDoorTime = g_dElapsedTime;
		for (int Rows = 0; Rows < 24; Rows++)
		{
			for (int Columns = 0; Columns < 55; Columns++)
			{
				if ((Map[5][Rows][Columns]) == '#'){
					Map[5][Rows][Columns] = (char)158;
				}
			}

			if ((g_dElapsedTime - g_dDoorTime) > (g_dDoorTime + 10)){
				for (int Columns = 0; Columns < 55; Columns++){
					if ((Map[5][Rows][Columns]) == (char)158){
						Map[5][Rows][Columns] = '#';
					}
				}
			}
		}
	}
}
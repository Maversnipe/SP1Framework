#include "AI.h"
EnemyChar Enemy;
extern SGameChar g_sChar;
extern char Map[20][100][100];
extern int LevelSelection;
bool detected = false;
int randomMovement;

void AiMovement()
{
	if (((Enemy.m_cLocation.Y - g_sChar.m_cLocation.Y <= 5) || (g_sChar.m_cLocation.Y - Enemy.m_cLocation.Y <= 5)))
	{ //Checks for player vertically
		detected = true;
	}
	else if (((Enemy.m_cLocation.X - g_sChar.m_cLocation.X <= 5) || (g_sChar.m_cLocation.X - Enemy.m_cLocation.X <= 5)))
	{ //Checks for player horizontally
		detected = true;
	}
	randomMovement = rand() % 4 + 1;
	if (detected == false)
	{
		if ((randomMovement == 1) && (Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != '|') && (Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != 'T'))
		{ //Enemy moves up if character isn't detected
			Enemy.m_cLocation.Y--;
		}
		else if ((randomMovement == 2) && (Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != '|') && (Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != 'T'))
		{ //Enemy moves down if character isn't detected
			Enemy.m_cLocation.Y++;
		}
		else if ((randomMovement == 3) && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != '|') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != 'T'))
		{ //Enemy moves left if character isn't detected
			Enemy.m_cLocation.X--;
		}
		else if ((randomMovement == 4) && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != '|') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != 'T'))
		{ //Enemy moves right if character isn't detected
			Enemy.m_cLocation.X++;
		}
	}
	else
	{

	}
}

void AiRender()
{
	WORD charColor = 0x04;
	g_Console.writeToBuffer(Enemy.m_cLocation, '$', charColor);
}

void AiSpawn()
{
	switch (LevelSelection)
	{
	case 1:
		Enemy.m_cLocation.X = 20;
		Enemy.m_cLocation.Y = 6;
		break;
	}
}
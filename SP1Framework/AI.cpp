#include "AI.h"
EnemyChar Enemy;
extern SGameChar g_sChar;
extern char Map[20][100][100];
extern int LevelSelection;
extern double g_dBounceTime;
extern double g_dElapsedTime;
bool detected = false;
int randomMovement;

void AiMovement()
{
	detected = false;
	if ((Enemy.m_cLocation.X == g_sChar.m_cLocation.X) && (((Enemy.m_cLocation.Y > g_sChar.m_cLocation.Y) && (Enemy.m_cLocation.Y - g_sChar.m_cLocation.Y <= 5)) || ((g_sChar.m_cLocation.Y > Enemy.m_cLocation.Y) && (g_sChar.m_cLocation.Y - Enemy.m_cLocation.Y <= 5))))
	{ //Checks for player vertically
		detected = true;
	}
	else if ((Enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (((Enemy.m_cLocation.X > g_sChar.m_cLocation.X) && (Enemy.m_cLocation.X - g_sChar.m_cLocation.X <= 5)) || ((g_sChar.m_cLocation.X > Enemy.m_cLocation.X) && (g_sChar.m_cLocation.X - Enemy.m_cLocation.X <= 5))))
	{ //Checks for player horizontally
		detected = true;
	}

	if (detected == false)
	{
		randomMovement = rand() % 4 + 1;
		bool bSomethingHappened = false;
		if (g_dBounceTime > g_dElapsedTime)
			return;

		if ((randomMovement == 1) && (Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != '|') && (Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != 'T'))
		{ //Enemy moves up if character isn't detected
			Enemy.m_cLocation.Y--;
			bSomethingHappened = true;
		}
		else if ((randomMovement == 2) && (Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != '|') && (Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != 'T'))
		{ //Enemy moves down if character isn't detected
			Enemy.m_cLocation.Y++;
			bSomethingHappened = true;
		}
		else if ((randomMovement == 3) && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != '|') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != 'T'))
		{ //Enemy moves left if character isn't detected
			Enemy.m_cLocation.X--;
			bSomethingHappened = true;
		}
		else if ((randomMovement == 4) && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != '|') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != 'T'))
		{ //Enemy moves right if character isn't detected
			Enemy.m_cLocation.X++;
			bSomethingHappened = true;
		}

		if (bSomethingHappened)
		{
			g_dBounceTime = g_dElapsedTime + 0.2;
		}
	}
	/*else
	{

	}*/
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
		Enemy.m_cLocation.Y = 4;
		break;
	}
}
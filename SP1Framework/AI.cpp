#include "game.h"
#include <stdlib.h>
#include <time.h> 
extern EGAMESTATES g_eGameState;
extern SGameChar g_sChar;
extern EnemyChar Enemy[3];
extern bool g_abKeyPressed[K_COUNT];
extern char Map[20][100][100];
extern int LevelSelection;
extern double g_dElapsedTime;
double enemyMoveTime = 0.0;
bool detected = false;
int randomMovement; 

void AiMovement()
{
	for (int i = 0; i < 3; i++)
	{
		detected = false;
		if ((Enemy[i].m_cLocation.X == g_sChar.m_cLocation.X) && //Checks for player vertically
			(((Enemy[i].m_cLocation.Y > g_sChar.m_cLocation.Y) && (Enemy[i].m_cLocation.Y - g_sChar.m_cLocation.Y <= 10)) || //Checking upwards
			((g_sChar.m_cLocation.Y > Enemy[i].m_cLocation.Y) && (g_sChar.m_cLocation.Y - Enemy[i].m_cLocation.Y <= 10)))) //Checking downwards
		{
			detected = true;
		}
		else if ((Enemy[i].m_cLocation.Y == g_sChar.m_cLocation.Y) && //Checks for player horizontally
			(((Enemy[i].m_cLocation.X > g_sChar.m_cLocation.X) && (Enemy[i].m_cLocation.X - g_sChar.m_cLocation.X <= 10)) || //Checking left
			((g_sChar.m_cLocation.X > Enemy[i].m_cLocation.X) && (g_sChar.m_cLocation.X - Enemy[i].m_cLocation.X <= 10)))) //Checking right
		{
			detected = true;
		}

		if (detected == false)
		{
			srand((unsigned int)time(NULL));
			randomMovement = rand() % 4 + 1;
			bool bSomethingHappened = false;
			if (enemyMoveTime > g_dElapsedTime)
				return;

			if ((randomMovement == 1) &&
				(Map[LevelSelection][Enemy[i].m_cLocation.Y - 1][Enemy[i].m_cLocation.X] != '=') && (Map[LevelSelection][Enemy[i].m_cLocation.Y - 1][Enemy[i].m_cLocation.X] != '|') &&
				(Map[LevelSelection][Enemy[i].m_cLocation.Y - 1][Enemy[i].m_cLocation.X] != 'r') && (Map[LevelSelection][Enemy[i].m_cLocation.Y - 1][Enemy[i].m_cLocation.X] != 'T'))
			{ //Enemy moves up if character isn't detected
				Enemy[i].m_cLocation.Y--;
				bSomethingHappened = true;
			}
			else if ((randomMovement == 2) &&
				(Map[LevelSelection][Enemy[i].m_cLocation.Y + 1][Enemy[i].m_cLocation.X] != '=') && (Map[LevelSelection][Enemy[i].m_cLocation.Y + 1][Enemy[i].m_cLocation.X] != '|') &&
				(Map[LevelSelection][Enemy[i].m_cLocation.Y + 1][Enemy[i].m_cLocation.X] != 'r') && (Map[LevelSelection][Enemy[i].m_cLocation.Y + 1][Enemy[i].m_cLocation.X] != 'T'))
			{ //Enemy moves down if character isn't detected
				Enemy[i].m_cLocation.Y++;
				bSomethingHappened = true;
			}
			else if ((randomMovement == 3) &&
				(Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X - 1] != '=') && (Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X - 1] != '|') &&
				(Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X - 1] != 'r') && (Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X - 1] != 'T'))
			{ //Enemy moves left if character isn't detected
				Enemy[i].m_cLocation.X--;
				bSomethingHappened = true;
			}
			else if ((randomMovement == 4) &&
				(Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X + 1] != '=') && (Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X + 1] != '|') &&
				(Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X + 1] != 'r') && (Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X + 1] != 'T'))
			{ //Enemy moves right if character isn't detected
				Enemy[i].m_cLocation.X++;
				bSomethingHappened = true;
			}

			if (bSomethingHappened)
			{
				enemyMoveTime = g_dElapsedTime + 0.2;
			}
		}
		else if (detected == true)
		{
			bool bSomethingHappened = false;
			if (enemyMoveTime > g_dElapsedTime)
				return;

			if ((g_sChar.m_cLocation.X == Enemy[i].m_cLocation.X) && (Enemy[i].m_cLocation.Y > g_sChar.m_cLocation.Y) && (Enemy[i].m_cLocation.Y - g_sChar.m_cLocation.Y <= 10) && //Enemy moves up if character is detected upwards
				(Map[LevelSelection][Enemy[i].m_cLocation.Y - 1][Enemy[i].m_cLocation.X] != '=') && (Map[LevelSelection][Enemy[i].m_cLocation.Y - 1][Enemy[i].m_cLocation.X] != '|') && //Collision
				(Map[LevelSelection][Enemy[i].m_cLocation.Y - 1][Enemy[i].m_cLocation.X] != 'r') && (Map[LevelSelection][Enemy[i].m_cLocation.Y - 1][Enemy[i].m_cLocation.X] != 'T'))//Collision
			{
				Enemy[i].m_cLocation.Y--;
				bSomethingHappened = true;
			}
			else if ((g_sChar.m_cLocation.X == Enemy[i].m_cLocation.X) && (g_sChar.m_cLocation.Y > Enemy[i].m_cLocation.Y) && (g_sChar.m_cLocation.Y - Enemy[i].m_cLocation.Y <= 10) &&
				(Map[LevelSelection][Enemy[i].m_cLocation.Y + 1][Enemy[i].m_cLocation.X] != '=') && (Map[LevelSelection][Enemy[i].m_cLocation.Y + 1][Enemy[i].m_cLocation.X] != '|') && //Collision
				(Map[LevelSelection][Enemy[i].m_cLocation.Y + 1][Enemy[i].m_cLocation.X] != 'r') && (Map[LevelSelection][Enemy[i].m_cLocation.Y + 1][Enemy[i].m_cLocation.X] != 'T'))//Collision
			{ //Enemy moves down if character isn't detected
				Enemy[i].m_cLocation.Y++;
				bSomethingHappened = true;
			}
			else if ((Enemy[i].m_cLocation.Y == g_sChar.m_cLocation.Y) && (Enemy[i].m_cLocation.X > g_sChar.m_cLocation.X) && (Enemy[i].m_cLocation.X - g_sChar.m_cLocation.X <= 10) &&
				(Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X - 1] != '=') && (Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X - 1] != '|') && //Collision
				(Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X - 1] != 'r') && (Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X - 1] != 'T')) //Collision
			{ //Enemy moves left if character isn't detected
				Enemy[i].m_cLocation.X--;
				bSomethingHappened = true;
			}
			else if ((Enemy[i].m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_sChar.m_cLocation.X > Enemy[i].m_cLocation.X) && (g_sChar.m_cLocation.X - Enemy[i].m_cLocation.X <= 10) &&
				(Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X + 1] != '=') && (Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X + 1] != '|') && //Collision
				(Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X + 1] != 'r') && (Map[LevelSelection][Enemy[i].m_cLocation.Y][Enemy[i].m_cLocation.X + 1] != 'T')) //Collision
			{ //Enemy moves right if character isn't detected
				Enemy[i].m_cLocation.X++;
				bSomethingHappened = true;
			}

			if (bSomethingHappened)
			{
				enemyMoveTime = g_dElapsedTime + 0.2;
			}

			if ((LevelSelection == 4) || (LevelSelection == 9) || (LevelSelection == 10))
			{
				if (Enemy[0].m_cLocation.Y == g_sChar.m_cLocation.Y && Enemy[0].m_cLocation.X == g_sChar.m_cLocation.X)
				{
					g_eGameState = S_GAMEOVER2;
				}
			}
			if ((LevelSelection == 9) || (LevelSelection == 10))
			{
				if (Enemy[1].m_cLocation.Y == g_sChar.m_cLocation.Y && Enemy[1].m_cLocation.X == g_sChar.m_cLocation.X)
				{
					g_eGameState = S_GAMEOVER2;
				}
			}
			if (LevelSelection == 10)
			{
				if (Enemy[2].m_cLocation.Y == g_sChar.m_cLocation.Y && Enemy[2].m_cLocation.X == g_sChar.m_cLocation.X)
				{
					g_eGameState = S_GAMEOVER2;
				}
			}
		}
	}
}

void AiRender()
{
	WORD charColor = 0x04;
	if ((LevelSelection == 4) || (LevelSelection == 9) || (LevelSelection == 10))
	{
		g_Console.writeToBuffer(Enemy[0].m_cLocation, '$', charColor);
	}
	if ((LevelSelection == 9) || (LevelSelection == 10))
	{
		g_Console.writeToBuffer(Enemy[1].m_cLocation, '$', charColor);
	}
	if (LevelSelection == 10)
	{
		g_Console.writeToBuffer(Enemy[2].m_cLocation, '$', charColor);
	}
}

void AiSpawn()
{
	switch (LevelSelection)
	{
	case 4:
		Enemy[0].m_cLocation.X = 32;
		Enemy[0].m_cLocation.Y = 4;
		break;
	case 9:
		Enemy[0].m_cLocation.X = 36;
		Enemy[0].m_cLocation.Y = 12;

		Enemy[1].m_cLocation.X = 27;
		Enemy[1].m_cLocation.Y = 12;
		break;
	case 10:
		Enemy[0].m_cLocation.X = 36;
		Enemy[0].m_cLocation.Y = 12;

		Enemy[1].m_cLocation.X = 27;
		Enemy[1].m_cLocation.Y = 12;

		Enemy[2].m_cLocation.X = 51;
		Enemy[2].m_cLocation.Y = 16;
		break;
	}
}
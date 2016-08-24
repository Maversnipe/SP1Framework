#include "AI.h"
EnemyChar Enemy;
extern SGameChar g_sChar;
extern char Map[20][100][100];
extern int LevelSelection;
extern double g_dElapsedTime;
double enemyMoveTime = 0.0;
bool detected = false;
int randomMovement;

void AiMovement()
{
	detected = false;
	if ((Enemy.m_cLocation.X == g_sChar.m_cLocation.X) && //Checks for player vertically
		(((Enemy.m_cLocation.Y > g_sChar.m_cLocation.Y) && (Enemy.m_cLocation.Y - g_sChar.m_cLocation.Y <= 10)) || //Checking upwards
		((g_sChar.m_cLocation.Y > Enemy.m_cLocation.Y) && (g_sChar.m_cLocation.Y - Enemy.m_cLocation.Y <= 10)))) //Checking downwards
	{ 
		detected = true;
	}
	else if ((Enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && //Checks for player horizontally
		(((Enemy.m_cLocation.X > g_sChar.m_cLocation.X) && (Enemy.m_cLocation.X - g_sChar.m_cLocation.X <= 10)) || //Checking left
		((g_sChar.m_cLocation.X > Enemy.m_cLocation.X) && (g_sChar.m_cLocation.X - Enemy.m_cLocation.X <= 10)))) //Checking right
	{ 
		detected = true;
	}

	if (detected == false)
	{
		randomMovement = rand() % 4 + 1;
		bool bSomethingHappened = false;
		if (enemyMoveTime > g_dElapsedTime)
			return;

		if ((randomMovement == 1) && 
			(Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != '|') && 
			(Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != 'T'))
		{ //Enemy moves up if character isn't detected
			Enemy.m_cLocation.Y--;
			bSomethingHappened = true;
		}
		else if ((randomMovement == 2) && 
			(Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != '|') && 
			(Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != 'T'))
		{ //Enemy moves down if character isn't detected
			Enemy.m_cLocation.Y++;
			bSomethingHappened = true;
		}
		else if ((randomMovement == 3) && 
			(Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != '|') && 
			(Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != 'T'))
		{ //Enemy moves left if character isn't detected
			Enemy.m_cLocation.X--;
			bSomethingHappened = true;
		}
		else if ((randomMovement == 4) && 
			(Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != '|') && 
			(Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != 'T'))
		{ //Enemy moves right if character isn't detected
			Enemy.m_cLocation.X++;
			bSomethingHappened = true;
		}

		if (bSomethingHappened)
		{
			enemyMoveTime = g_dElapsedTime + 0.125;
		}
	}
	else if (detected == true)
	{
		bool bSomethingHappened = false;
		if (enemyMoveTime > g_dElapsedTime)
			return;

		if ((g_sChar.m_cLocation.X == Enemy.m_cLocation.X) && (Enemy.m_cLocation.Y > g_sChar.m_cLocation.Y) && (Enemy.m_cLocation.Y - g_sChar.m_cLocation.Y <= 10) && //Enemy moves up if character is detected upwards
			(Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != '|') && //Collision
			(Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y - 1][Enemy.m_cLocation.X] != 'T'))//Collision
		{ 
			Enemy.m_cLocation.Y--;
			bSomethingHappened = true;
		}
		else if ((g_sChar.m_cLocation.X == Enemy.m_cLocation.X) && (g_sChar.m_cLocation.Y > Enemy.m_cLocation.Y) && (g_sChar.m_cLocation.Y - Enemy.m_cLocation.Y <= 10) &&
			(Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != '|') && //Collision
			(Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y + 1][Enemy.m_cLocation.X] != 'T'))//Collision
		{ //Enemy moves down if character isn't detected
			Enemy.m_cLocation.Y++;
			bSomethingHappened = true;
		}
		else if ((Enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (Enemy.m_cLocation.X > g_sChar.m_cLocation.X) && (Enemy.m_cLocation.X - g_sChar.m_cLocation.X <= 10) &&
			(Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != '|') && //Collision
			(Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X - 1] != 'T')) //Collision
		{ //Enemy moves left if character isn't detected
			Enemy.m_cLocation.X--;
			bSomethingHappened = true;
		}
		else if ((Enemy.m_cLocation.Y == g_sChar.m_cLocation.Y) && (g_sChar.m_cLocation.X > Enemy.m_cLocation.X) && (g_sChar.m_cLocation.X - Enemy.m_cLocation.X <= 10) &&
			(Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != '=') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != '|') && //Collision
			(Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != 'r') && (Map[LevelSelection][Enemy.m_cLocation.Y][Enemy.m_cLocation.X + 1] != 'T')) //Collision
		{ //Enemy moves right if character isn't detected
			Enemy.m_cLocation.X++;
			bSomethingHappened = true;
		}

		if (bSomethingHappened)
		{
			enemyMoveTime = g_dElapsedTime + 0.125;
		}

		if (Enemy.m_cLocation.Y == g_sChar.m_cLocation.Y && Enemy.m_cLocation.X == g_sChar.m_cLocation.X)
		{
			restart();
		}
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
		Enemy.m_cLocation.X = 30;
		Enemy.m_cLocation.Y = 4;
		break;
	}
}
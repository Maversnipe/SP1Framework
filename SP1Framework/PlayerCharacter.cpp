#include "game.h"
extern char Map[20][100][100];
extern double g_dElapsedTime;
extern double  g_dBounceTime;
extern SGameChar g_sChar;
extern bool g_abKeyPressed[K_COUNT];
extern int LevelSelection;
extern bool playerOnRock;
extern bool onRock;
extern int g_dTotalPoints;

void renderCharacter()
{
	// Draw the location of the character
	WORD charColor = 0x06;
	g_Console.writeToBuffer(g_sChar.m_cLocation, (char)232, charColor);
}

void moveCharacter()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'O')
		playerOnRock = true;
	else
		playerOnRock = false;
	// Updating the location of the character baseed on the key press
	// providing a beep sound whenver we shift the character

//////////MOVE UP//////////
	if (((g_abKeyPressed[K_W]) || (g_abKeyPressed[K_UP])) && (g_sChar.m_cLocation.Y > 0))//Move Up 
	{
		//Beep(1440, 30);
		if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == (char)233)
		{ //Check for boulder in front of player
			if ((onRock == true) && (playerOnRock == true) && (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'O'))
			{ // 1a. Pushing boulder ONTO ROCK while BOULDER ON ANOTHER ROCK while PLAYER ON ROCK
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
				g_sChar.m_cLocation.Y--;
				bSomethingHappened = true;
				onRock = true;
			}
			else if ((onRock == true) && (playerOnRock == false) && (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'O'))
			{ // 1b. Pushing boulder ONTO ROCK while BOULDER IS ON ANOTHER ROCK while PLAYER ON LAND
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y--;
				bSomethingHappened = true;
				onRock = true;
			}
			else if ((onRock == true) && (playerOnRock == true) && (((Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'r')) ||
				((Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'o'))))
			{ // 2a. Pushing boulder INTO WATER/HOLE while BOULDER ON ROCK while PLAYER ON ROCK
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
				g_sChar.m_cLocation.Y--;
				bSomethingHappened = true;
				onRock = false;
			}
			else if ((onRock == true) && (playerOnRock == false) && (((Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'r')) ||
				((Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'o'))))
			{ // 2b. Pushing boulder INTO WATER/HOLE while BOULDER ON ROCK while PLAYER ON LAND
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y--;
				bSomethingHappened = true;
				onRock = false;
			}
			//else if ((onRock == false) && (playerOnRock == true) && Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'O')
			//{ // 3a. Pushing boulder onto rock while boulder on land while player is on rock
			//	Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = (char)233;
			//	Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = ' ';
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
			//	g_sChar.m_cLocation.Y--;
			//	bSomethingHappened = true;
			//	playerOnRock = false;
			//	onRock = true;
			//}
			else if ((onRock == false) && (playerOnRock == false) && Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'O')
			{ // 3b. Pushing boulder onto rock while boulder on land while player is on land
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = ' ';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y--;
				bSomethingHappened = true;
				onRock = true;
			}
			//else if ((onRock == false) && (playerOnRock == true) && ((Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'r') ||
			//	(Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'o')))
			//{ // 4a. Pushing boulder INTO WATER while BOULDER ON LAND and PLAYER ON ROCK
			//	Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = 'O';
			//	Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = ' ';
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
			//	g_sChar.m_cLocation.Y--;
			//	bSomethingHappened = true;
			//	playerOnRock = false;
			//	onRock = false;
			//}
			else if ((onRock == false) && (playerOnRock == false) && ((Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'r') ||
				(Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'o')))
			{ // 4b. Pushing boulder INTO WATER while BOULDER ON LAND and PLAYER ON LAND
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = ' ';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y--;
				bSomethingHappened = true;
				onRock = false;
			}
			else if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] != '=' &&
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] != '|' &&
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] != 'T' &&
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] != (char)233)
			{ //Moving the boulder
				switch (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X])
				{
				case '.':
					g_dTotalPoints += 10;
					break;
				case '1':
					g_dTotalPoints += 100;
					break;
				case '2':
					g_dTotalPoints += 200;
					break;
				case '5':
					g_dTotalPoints += 500;
					break;
				case 'A':
					g_dTotalPoints += 1000;
					break;
				}
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y--;
				bSomethingHappened = true;
			}
		}
		else if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != '=' &&
			Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != '|' &&
			Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != 'r' &&
			Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != 'T' &&
			Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != 'o')
		{ //Character movement without boulder
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
	}
//////////MOVE LEFT//////////
	if (((g_abKeyPressed[K_A]) || (g_abKeyPressed[K_LEFT])) && (g_sChar.m_cLocation.X > 0))//Move Left 
	{
		//Beep(1440, 30);
		if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == (char)233)
		{ //Check for boulder in front of player
			if ((onRock == true) && (playerOnRock == true) && (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'O'))
			{ // 1a. Pushing boulder ONTO ROCK while BOULDER ON ANOTHER ROCK while PLAYER ON ROCK
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
				g_sChar.m_cLocation.X--;
				bSomethingHappened = true;
				onRock = true;
			}
			else if ((onRock == true) && (playerOnRock == false) && (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'O'))
			{ // 1b. Pushing boulder ONTO ROCK while BOULDER IS ON ANOTHER ROCK while PLAYER ON LAND
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.X--;
				bSomethingHappened = true;
				playerOnRock = true;
				onRock = true;
			}
			else if ((onRock == true) && (playerOnRock == true) && (((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'r')) ||
				((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'o'))))
			{ // 2a. Pushing boulder INTO WATER/HOLE while BOULDER ON ROCK while PLAYER ON ROCK
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
				g_sChar.m_cLocation.X--;
				bSomethingHappened = true;
				onRock = false;
			}
			else if ((onRock == true) && (playerOnRock == false) && (((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'r')) ||
				((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'o'))))
			{ // 2b. Pushing boulder INTO WATER/HOLE while BOULDER ON ROCK while PLAYER ON LAND
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.X--;
				bSomethingHappened = true;
				onRock = false;
			}
			//else if ((onRock == false) && (playerOnRock == true) && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'O')
			//{ // 3a. Pushing boulder onto rock while boulder on land while player is on rock
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = (char)233;
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = ' ';
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
			//	g_sChar.m_cLocation.X--;
			//	bSomethingHappened = true;
			//	playerOnRock = false;
			//	onRock = true;
			//}
			else if ((onRock == false) && (playerOnRock == false) && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'O')
			{ // 3b. Pushing boulder onto rock while boulder on land while player is on land
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = ' ';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.X--;
				bSomethingHappened = true;
				onRock = true;
			}
			//else if ((onRock == false) && (playerOnRock == true) && ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'r') ||
			//	(Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'o')))
			//{ // 4a. Pushing boulder INTO WATER while BOULDER ON LAND and PLAYER ON ROCK
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = 'O';
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = ' ';
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
			//	g_sChar.m_cLocation.X--;
			//	bSomethingHappened = true;
			//	playerOnRock = false;
			//	onRock = false;
			//}
			else if ((onRock == false) && (playerOnRock == false) && ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'r') ||
				(Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'o')))
			{ // 4b. Pushing boulder INTO WATER while BOULDER ON LAND and PLAYER ON LAND
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = ' ';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.X--;
				bSomethingHappened = true;
				onRock = false;
			}
			else if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] != '=' &&
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] != '|' &&
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] != 'T' &&
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] != (char)233)
			{ //Moving the boulder
				switch (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2])
				{
				case '.':
					g_dTotalPoints += 10;
					break;
				case '1':
					g_dTotalPoints += 100;
					break;
				case '2':
					g_dTotalPoints += 200;
					break;
				case '5':
					g_dTotalPoints += 500;
					break;
				case 'A':
					g_dTotalPoints += 1000;
					break;
				}
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = ' ';
				g_sChar.m_cLocation.X--;
				bSomethingHappened = true;
			}
		}
		else if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != '=' &&
			Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != '|' &&
			Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != 'T' &&
			Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != 'r' &&
			Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != 'o')
		{ //Character movement without boulder
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
	}
//////////MOVE DOWN//////////
	if (((g_abKeyPressed[K_S]) || (g_abKeyPressed[K_DOWN])) && (g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1))//Move Down
	{
		//Beep(1440, 30);
		if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == (char)233)
		{ //Check for boulder in front of player
			if ((onRock == true) && (playerOnRock == true) && (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'O'))
			{ // 1a. Pushing boulder ONTO ROCK while BOULDER ON ANOTHER ROCK while PLAYER ON ROCK
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
				g_sChar.m_cLocation.Y++;
				bSomethingHappened = true;
				onRock = true;
			}
			else if ((onRock == true) && (playerOnRock == false) && (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'O'))
			{ // 1b. Pushing boulder ONTO ROCK while BOULDER IS ON ANOTHER ROCK while PLAYER ON LAND
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y++;
				bSomethingHappened = true;
				playerOnRock = true;
				onRock = true;
			}
			else if ((onRock == true) && (playerOnRock == true) && (((Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'r')) ||
				((Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'o'))))
			{ // 2a. Pushing boulder INTO WATER/HOLE while BOULDER ON ROCK while PLAYER ON ROCK
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
				g_sChar.m_cLocation.Y++;
				bSomethingHappened = true;
				onRock = false;
			}
			else if ((onRock == true) && (playerOnRock == false) && (((Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'r')) ||
				((Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'o'))))
			{ // 2b. Pushing boulder INTO WATER/HOLE while BOULDER ON ROCK while PLAYER ON LAND
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y++;
				bSomethingHappened = true;
				onRock = false;
			}
			//else if ((onRock == false) && (playerOnRock == true) && Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'O')
			//{ // 3a. Pushing boulder onto rock while boulder on land while player is on rock
			//	Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = (char)233;
			//	Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = ' ';
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
			//	g_sChar.m_cLocation.Y++;
			//	bSomethingHappened = true;
			//	playerOnRock = false;
			//	onRock = true;
			//}
			else if ((onRock == false) && (playerOnRock == false) && Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'O')
			{ // 3b. Pushing boulder onto rock while boulder on land while player is on land
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = ' ';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y++;
				bSomethingHappened = true;
				onRock = true;
			}
			//else if ((onRock == false) && (playerOnRock == true) && ((Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'r') ||
			//	(Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'o')))
			//{ // 4a. Pushing boulder INTO WATER while BOULDER ON LAND and PLAYER ON ROCK
			//	Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = 'O';
			//	Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = ' ';
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
			//	g_sChar.m_cLocation.Y++;
			//	bSomethingHappened = true;
			//	playerOnRock = false;
			//	onRock = false;
			//}
			else if ((onRock == false) && (playerOnRock == false) && ((Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'r') ||
				(Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'o')))
			{ // 4b. Pushing boulder INTO WATER while BOULDER ON LAND and PLAYER ON LAND
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = ' ';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y++;
				bSomethingHappened = true;
				onRock = false;
			}
			else if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] != '=' &&
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] != '|' &&
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] != 'T' &&
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] != (char)233)
			{ //Moving the boulder
				switch (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X])
				{
				case '.':
					g_dTotalPoints += 10;
					break;
				case '1':
					g_dTotalPoints += 100;
					break;
				case '2':
					g_dTotalPoints += 200;
					break;
				case '5':
					g_dTotalPoints += 500;
					break;
				case 'A':
					g_dTotalPoints += 1000;
					break;
				}
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y++;
				bSomethingHappened = true;
			}
		}
		else if ((Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != '=') &&
			(Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != '|') &&
			(Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != 'T') &&
			(Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != 'r') &&
			(Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != 'o'))
		{ //Character movement without boulder
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
	}
//////////MOVE RIGHT//////////
	if (((g_abKeyPressed[K_D]) || (g_abKeyPressed[K_RIGHT])) && (g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1))//Move Right
	{
		//Beep(1440, 30);
		if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == (char)233)
		{ //Check for boulder in front of player
			if ((onRock == true) && (playerOnRock == true) && (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'O'))
			{ // 1a. Pushing boulder ONTO ROCK while BOULDER ON ANOTHER ROCK while PLAYER ON ROCK
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
				g_sChar.m_cLocation.X++;
				bSomethingHappened = true;
				onRock = true;
			}
			else if ((onRock == true) && (playerOnRock == false) && (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'O'))
			{ // 1b. Pushing boulder ONTO ROCK while BOULDER IS ON ANOTHER ROCK while PLAYER ON LAND
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.X++;
				bSomethingHappened = true;
				onRock = true;
			}
			else if ((onRock == true) && (playerOnRock == true) && (((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'r')) ||
				((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'o'))))
			{ // 2a. Pushing boulder INTO WATER/HOLE while BOULDER ON ROCK while PLAYER ON ROCK
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
				g_sChar.m_cLocation.X++;
				bSomethingHappened = true;
				onRock = false;
			}
			else if ((onRock == true) && (playerOnRock == false) && (((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'r')) ||
				((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'o'))))
			{ // 2b. Pushing boulder INTO WATER/HOLE while BOULDER ON ROCK while PLAYER ON LAND
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.X++;
				bSomethingHappened = true;
				onRock = false;
			}
			//else if ((onRock == false) && (playerOnRock == true) && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'O')
			//{ // 3a. Pushing boulder onto rock while boulder on land while player is on rock
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = (char)233;
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = ' ';
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
			//	g_sChar.m_cLocation.X++;
			//	bSomethingHappened = true;
			//	playerOnRock = false;
			//	onRock = true;
			//}
			else if ((onRock == false) && (playerOnRock == false) && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'O')
			{ // 3b. Pushing boulder onto rock while boulder on land while player is on land
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = ' ';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.X++;
				bSomethingHappened = true;
				onRock = true;
			}
			//else if ((onRock == false) && (playerOnRock == true) && ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'r') ||
			//	(Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'o')))
			//{ // 4a. Pushing boulder INTO WATER while BOULDER ON LAND and PLAYER ON ROCK
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = 'O';
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = ' ';
			//	Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = 'O';
			//	g_sChar.m_cLocation.X++;
			//	bSomethingHappened = true;
			//	playerOnRock = false;
			//	onRock = false;
			//}
			else if ((onRock == false) && (playerOnRock == false) && ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'r') ||
				(Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'o')))
			{ // 4b. Pushing boulder INTO WATER while BOULDER ON LAND and PLAYER ON LAND
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = ' ';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.X++;
				bSomethingHappened = true;
				onRock = false;
			}
			else if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] != '=' &&
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] != '|' &&
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] != 'T' &&
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] != (char)233)
			{ //Moving the boulder
				switch (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2])
				{
				case '.':
					g_dTotalPoints += 10;
					break;
				case '1':
					g_dTotalPoints += 100;
					break;
				case '2':
					g_dTotalPoints += 200;
					break;
				case '5':
					g_dTotalPoints += 500;
					break;
				case 'A':
					g_dTotalPoints += 1000;
					break;
				}
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = ' ';
				g_sChar.m_cLocation.X++;
				bSomethingHappened = true;
			}
		}
		else if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != '=' &&
			Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != '|' &&
			Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != 'T' &&
			Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != 'r' &&
			Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != 'o')
		{ //Character movement without boulder
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}
	}
//////////OTHERS//////////
	if (g_abKeyPressed[K_SPACE])
	{
		g_sChar.m_bActive = !g_sChar.m_bActive;
		bSomethingHappened = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}

void charSpawn()
{
	switch (LevelSelection)
	{
	case 1:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 22;
		break;
	case 2:
		g_sChar.m_cLocation.X = 6;
		g_sChar.m_cLocation.Y = 22;
		break;
	case 3:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 5;
		break;
	case 4:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 21;
		break;
	case 5:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 5;
		break;
	case 6:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 21;
		break;
	case 7:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 21;
		break;
	case 8:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 21;
		break;
	case 9:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 21;
		break;
	case 10:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 21;
		break;
	}
}

void CharName()
{
	g_sChar.Name = "";
	int Key = 0;
	switch (g_abKeyPressed[K_COUNT])
	{
	case K_A:
		g_sChar.Name += 'A';
		break;
	case K_B:
		g_sChar.Name += 'B';
		break;
	case K_C:
		g_sChar.Name += 'C';
		break;
	case K_D:
		g_sChar.Name += 'D';
		break;
	case K_E:
		g_sChar.Name += 'E';
		break;
	case K_F:
		g_sChar.Name += 'F';
		break;
	case K_G:
		g_sChar.Name += 'G';
		break;
	case K_H:
		g_sChar.Name += 'H';
		break;
	case K_I:
		g_sChar.Name += 'I';
		break;
	case K_J:
		g_sChar.Name += 'J';
		break;
	case K_K:
		g_sChar.Name += 'K';
		break;
	case K_L:
		g_sChar.Name += 'L';
		break;
	case K_M:
		g_sChar.Name += 'M';
		break;
	case K_N:
		g_sChar.Name += 'N';
		break;
	case K_O:
		g_sChar.Name += 'O';
		break;
	case K_P:
		g_sChar.Name += 'P';
		break;
	case K_Q:
		g_sChar.Name += 'Q';
		break;
	case K_R:
		g_sChar.Name += 'R';
		break;
	case K_S:
		g_sChar.Name += 'S';
		break;
	case K_T:
		g_sChar.Name += 'T';
		break;
	case K_U:
		g_sChar.Name += 'U';
		break;
	case K_V:
		g_sChar.Name += 'V';
		break;
	case K_W:
		g_sChar.Name += 'W';
		break;
	case K_X:
		g_sChar.Name += 'X';
		break;
	case K_Y:
		g_sChar.Name += 'Y';
		break;
	case K_Z:
		g_sChar.Name += 'Z';
		break;
	case K_SPACE:
		g_sChar.Name += ' ';

	}
}
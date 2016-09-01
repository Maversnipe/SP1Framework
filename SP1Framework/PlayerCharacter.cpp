#include "game.h"
extern char Map[20][100][100];
extern double g_dElapsedTime;
extern double  g_dBounceTime;
extern double g_dEndToName;
extern SGameChar g_sChar;
extern bool g_abKeyPressed[K_COUNT];
extern int LevelSelection;
extern bool playerOnRock;
extern bool onRock;
extern int g_dTotalPoints;
extern EGAMESTATES g_eGameState;
extern int nameLetterCounter;
extern bool GMode;

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
			else if ((onRock == false) && (playerOnRock == false) && Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'O')
			{ // 3. Pushing boulder onto rock while boulder on land while player is on land
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = ' ';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y--;
				bSomethingHappened = true;
				onRock = true;
			}
			else if ((onRock == false) && (playerOnRock == false) && ((Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'r') ||
				(Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'o')))
			{ // 4. Pushing boulder INTO WATER while BOULDER ON LAND and PLAYER ON LAND
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
			Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != 'o' &&
			GMode == false)
		{ //Character movement without boulder
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
		else if (GMode == true)
		{ //Character can bypass walls
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
			else if ((onRock == false) && (playerOnRock == false) && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'O')
			{ // 3. Pushing boulder onto rock while boulder on land while player is on land
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = ' ';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.X--;
				bSomethingHappened = true;
				onRock = true;
			}
			else if ((onRock == false) && (playerOnRock == false) && ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'r') ||
				(Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'o')))
			{ // 4. Pushing boulder INTO WATER while BOULDER ON LAND and PLAYER ON LAND
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
			Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != 'o' &&
			GMode == false)
		{ //Character movement without boulder
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
		else if (GMode == true)
		{ //Character can bypass walls
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
			else if ((onRock == false) && (playerOnRock == false) && Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'O')
			{ // 3. Pushing boulder onto rock while boulder on land while player is on land
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = ' ';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y++;
				bSomethingHappened = true;
				onRock = true;
			}
			else if ((onRock == false) && (playerOnRock == false) && ((Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'r') ||
				(Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'o')))
			{ // 4. Pushing boulder INTO WATER while BOULDER ON LAND and PLAYER ON LAND
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
			(Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != 'o') &&
			(GMode == false))
		{ //Character movement without boulder
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
		else if (GMode == true)
		{ //Character can bypass walls
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
			else if ((onRock == false) && (playerOnRock == false) && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'O')
			{ // 3b. Pushing boulder onto rock while boulder on land while player is on land
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = ' ';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.X++;
				bSomethingHappened = true;
				onRock = true;
			}
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
			Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != 'o' &&
			GMode == false)
		{ //Character movement without boulder
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}
		else if (GMode == true)
		{ //Character can bypass walls
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

	if (g_abKeyPressed[K_I])
	{
		GMode = true;
		bSomethingHappened = true;
	}

	if ((g_abKeyPressed[K_U]) && (GMode == true))
	{
		GMode = false;
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
		g_sChar.m_cLocation.Y = 20;
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
	COORD c = g_Console.getConsoleSize();
	c.Y = c.Y / 2;
	c.X = (c.X / 2) - (nameLetterCounter / 2);

	//while ((nameLetterCounter < 10) || (g_abKeyPressed[K_ENTER] == false))
	////for (nameLetterCounter = 0; nameLetterCounter < 10;)
	
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	if ((nameLetterCounter < 10) && (g_dElapsedTime > g_dEndToName))
	{
		if ((g_abKeyPressed[K_A]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "A";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_B]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "B";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_C]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "C";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_D]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "D";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_E]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "E";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_F]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "F";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_G]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "G";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_H]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "H";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_I]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "I";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_J]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "J";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_K]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "K";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_L]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "L";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_M]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "M";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_N]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "N";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_O]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "O";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_P]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "P";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_Q]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "Q";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_R]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "R";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_S]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "S";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_T]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "T";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_U]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "U";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_V]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "V";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_W]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "W";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_X]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "X";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_Y]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "Y";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_Z]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += "Z";
			bSomethingHappened = true;
		}
		if ((g_abKeyPressed[K_SPACE]) && (g_dElapsedTime > g_dBounceTime))
		{
			nameLetterCounter++;
			g_sChar.Name += " ";
			bSomethingHappened = true;
		}
	}

	if ((g_abKeyPressed[K_BACKSPACE]) && (g_dElapsedTime > g_dBounceTime) && (nameLetterCounter >= 1))
	{
		g_sChar.Name.erase(nameLetterCounter - 1, 1);
		nameLetterCounter--;
		bSomethingHappened = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.2; // 125ms should be enough
	}

	g_Console.writeToBuffer(c, g_sChar.Name);

	if (g_abKeyPressed[K_ENTER] && (g_eGameState == S_INPUT_NAME))
	{
		nameLetterCounter = 0;
		g_eGameState = S_LEADERBOARD;
	}
}
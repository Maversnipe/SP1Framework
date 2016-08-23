#include "game.h"
extern char Map[20][100][100];
extern double g_dElapsedTime;
extern double  g_dBounceTime;
extern struct SGameChar;
extern SGameChar g_sChar;
extern bool g_abKeyPressed[K_COUNT];
extern int LevelSelection;
extern bool onRock;

void moveCharacter()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (((g_abKeyPressed[K_W]) || (g_abKeyPressed[K_UP])) && (g_sChar.m_cLocation.Y > 0))//Move Up 
	{
		//Beep(1440, 30);
		if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == (char)233)
		{
			if (onRock == true && Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'O')
			{
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = 'O';
				g_sChar.m_cLocation.Y--;
				onRock = true;
				bSomethingHappened = true;
			}
			else if (onRock == true && Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'r')
			{ //Pushing boulder into water while on boulder
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = 'O';
				g_sChar.m_cLocation.Y--;
				onRock = false;
				bSomethingHappened = true;
			}
			else if (onRock == false && Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'O')
			{ //Pushing boulder onto boulder while on land
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y--;
				onRock = true;
				bSomethingHappened = true;
			}
			else if (onRock == true && Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'O')
			{ //Pushing boulder onto boulder while on a boulder
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = 'O';
				g_sChar.m_cLocation.Y--;
				bSomethingHappened = true;
			}
			else if (onRock == false && Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'r')
			{ //Pushing boulder into water
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y--;
				bSomethingHappened = true;
			}
			else if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] != '=' && Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] != '|' && Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] != 'T' && Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] != 'r')
			{ //Moving the boulder
				Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y--;
				bSomethingHappened = true;
			}
		}
		else if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != '=' && Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != '|' && Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != 'r' && Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != 'T')
		{
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
	}

	if (((g_abKeyPressed[K_A]) || (g_abKeyPressed[K_LEFT])) && (g_sChar.m_cLocation.X > 0))//Move Left 
	{
		//Beep(1440, 30);
		if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == (char)233)
		{
			if (onRock == true && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'O')
			{
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = 'O';
				g_sChar.m_cLocation.X--;
				onRock = true;
				bSomethingHappened = true;
			}
			else if (onRock == true && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'r')
			{ //Pushing boulder into water while on boulder
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = 'O';
				g_sChar.m_cLocation.X--;
				onRock = false;
				bSomethingHappened = true;
			}
			else if (onRock == false && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'O')
			{ //Pushing boulder onto boulder while on land
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = ' ';
				g_sChar.m_cLocation.X--;
				onRock = true;
				bSomethingHappened = true;
			}
			else if (onRock == true && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'O')
			{ //Pushing boulder onto boulder while on a boulder
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = 'O';
				g_sChar.m_cLocation.X--;
				bSomethingHappened = true;
			}
			else if (onRock == false && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'r')
			{ //Pushing boulder into water
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = ' ';
				g_sChar.m_cLocation.X--;
				bSomethingHappened = true;
			}
			else if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] != '=' && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] != '|' && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] != 'T' && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] != 'r')
			{ //Moving the boulder
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] = ' ';
				g_sChar.m_cLocation.X--;
				bSomethingHappened = true;
			}
		}
		else if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != '=' && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != '|' && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != 'T' && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != 'r')
		{
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
	}

	if (((g_abKeyPressed[K_S]) || (g_abKeyPressed[K_DOWN])) && (g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1))//Move Down
	{
		//Beep(1440, 30);
		if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == (char)233)
		{
			if (onRock == true && Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'O')
			{
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = 'O';
				g_sChar.m_cLocation.Y++;
				onRock = true;
				bSomethingHappened = true;
			}
			else if (onRock == true && Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'r')
			{ //Pushing boulder into water while on boulder
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = 'O';
				g_sChar.m_cLocation.Y++;
				onRock = false;
				bSomethingHappened = true;
			}
			else if (onRock == false && Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'O')
			{ //Pushing boulder onto boulder while on land
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y++;
				onRock = true;
				bSomethingHappened = true;
			}
			else if (onRock == true && Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'O')
			{ //Pushing boulder onto boulder while on a boulder
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = 'O';
				g_sChar.m_cLocation.Y++;
				bSomethingHappened = true;
			}
			else if (onRock == false && Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'r')
			{ //Pushing boulder into water
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y++;
				bSomethingHappened = true;
			}
			else if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] != '=' && Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] != '|' && Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] != 'T' && Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] != 'r')
			{ //Moving the boulder
				Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = ' ';
				g_sChar.m_cLocation.Y++;
				bSomethingHappened = true;
			}
		}
		else if ((Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != '=') && (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != '|') && (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != 'T') && ((Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != 'r')))
		{
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
	}

	if (((g_abKeyPressed[K_D]) || (g_abKeyPressed[K_RIGHT])) && (g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1))//Move Right
	{
		//Beep(1440, 30);
		if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == (char)233)
		{
			if (onRock == true && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'O')
			{
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = 'O';
				g_sChar.m_cLocation.X++;
				onRock = true;
				bSomethingHappened = true;
			}
			else if (onRock == true && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'r')
			{ //Pushing boulder into water while on boulder
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = 'O';
				g_sChar.m_cLocation.X++;
				onRock = false;
				bSomethingHappened = true;
			}
			else if (onRock == false && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'O')
			{ //Pushing boulder onto boulder while on land
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = ' ';
				g_sChar.m_cLocation.X++;
				onRock = true;
				bSomethingHappened = true;
			}
			else if (onRock == true && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'O')
			{ //Pushing boulder onto boulder while on a boulder
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = 'O';
				g_sChar.m_cLocation.X++;
				bSomethingHappened = true;
			}
			else if (onRock == false && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'r')
			{ //Pushing boulder into water
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = 'O';
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = ' ';
				g_sChar.m_cLocation.X++;
				bSomethingHappened = true;
			}
			else if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] != '=' && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] != '|' && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] != 'T' && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] != 'r')
			{ //Moving the boulder
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] = (char)233;
				Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] = ' ';
				g_sChar.m_cLocation.X++;
				bSomethingHappened = true;
			}
		}
		else if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != '=' && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != '|' && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != 'T' && Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != 'r')
		{
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}
	}

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
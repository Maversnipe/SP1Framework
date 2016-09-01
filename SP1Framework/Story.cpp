#include "Story.h"
extern Console g_Console;

void StoryOne()
{
	g_Console.clearBuffer(0x27);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("StoryOne.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x27);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryTwo()
{
	g_Console.clearBuffer(0x27);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("StoryTwo.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x27);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryThree()
{
	g_Console.clearBuffer(0x27);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("StoryThree.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x27);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryFour()
{
	g_Console.clearBuffer(0x27);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("StoryFour.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x27);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryFive()
{
	g_Console.clearBuffer(0x17);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("StoryFive.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x17);
			c.Y++;
		}
		myfile.close();
	}
}

void StorySix()
{
	g_Console.clearBuffer(0x17);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("StorySix.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x17);
			c.Y++;
		}
		myfile.close();
	}
}

void StorySeven()
{
	g_Console.clearBuffer(0x17);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("StorySeven.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x17);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryEight()
{
	g_Console.clearBuffer(0x17);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("StoryEight.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x17);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryNine()
{
	g_Console.clearBuffer(0x17);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("StoryNine.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x17);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryTen()
{
	g_Console.clearBuffer(0x17);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("StoryTen.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x17);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryEnd()
{
	extern double g_dTimer;
	extern int g_dTotalPoints;
	extern int SavedPoints;
	extern int AxeUses;
	extern bool playerOnRock;
	extern bool treeAxe;
	extern bool bonusTimeKey;
	extern Console g_Console;
	extern SGameChar g_sChar;
	extern EGAMESTATES g_eGameState;
	extern bool g_abKeyPressed[K_COUNT];
	extern bool playedGame;
	extern bool CheckLever[11];

	g_Console.clearBuffer(0x27);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("StoryLast.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x27);
			c.Y++;
		}
		myfile.close();
	}
	c.X = 25;
	c.Y = 20;

	ostringstream ss;
	ss.str("");
	ss << "You've finished the game.";
	g_Console.writeToBuffer(c, ss.str(), 0x2F);
	ss.str("");
	ss << "Press ENTER to proceed to the Leaderboard.";
	g_Console.writeToBuffer(c.X, c.Y + 2, ss.str(), 0x2F);
	ss.str("");
	ss << "Press SPACE to go back to the main menu.";
	g_Console.writeToBuffer(c.X, c.Y + 4, ss.str(), 0x2F);

	if (g_abKeyPressed[K_ENTER]){
		g_sChar.time = g_dTimer;
		g_dTimer = 0.0;
		g_sChar.points = g_dTotalPoints;
		g_dTotalPoints = 0;
		SavedPoints = 0;
		playerOnRock = false;
		treeAxe = false;
		AxeUses = 0;
		for (int LevelsDone = 5; LevelsDone <= 10; LevelsDone++) //Reset check lever to false
		{
			CheckLever[LevelsDone] = false;
		}
		bonusTimeKey = false;
		playedGame = true;
		LoadMaps();
		g_eGameState = S_INPUT_NAME;
	}

	if (g_abKeyPressed[K_SPACE]){
		g_sChar.time = g_dTimer;
		g_dTimer = 0.0;
		g_sChar.points = g_dTotalPoints;
		g_dTotalPoints = 0;
		SavedPoints = 0;
		treeAxe = false;
		AxeUses = 0;
		playerOnRock = false;
		for (int LevelsDone = 5; LevelsDone <= 10; LevelsDone++) //Reset check lever to false
		{
			CheckLever[LevelsDone] = false;
		}
		bonusTimeKey = false;
		playedGame = true;
		LoadMaps();
		g_eGameState = S_SPLASHSCREEN;
	}
}
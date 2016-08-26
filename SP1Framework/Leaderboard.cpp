#include "game.h"
extern bool g_abKeyPressed[K_COUNT];
extern EGAMESTATES g_eGameState;
extern COORD arrow;
extern stringstream OverallTime;
extern stringstream OverallPoints;
extern stringstream InputName;
extern int Points;
extern int Time;
string Leaderboard[5][2];


void renderLeaderboard()
{
	LeaderboardMenu();
}

void LeaderboardMenu()
{
	COORD c = g_Console.getConsoleSize();
	c.Y = c.Y / 2;
	c.X = c.X / 2;
	COORD a = g_Console.getConsoleSize();
	a.Y = 5;
	a.X = 10;

	ostringstream highScore;
	ostringstream fastTime;
	ostringstream mes;
	highScore.str("");
	fastTime.str("");
	highScore << "HIGHEST SCORES";
	fastTime << "SHORTEST TIMES"; // shows the highest score + shortest time
	g_Console.writeToBuffer(c.X - 7, c.Y, highScore.str(), 0x07);
	g_Console.writeToBuffer(c.X - 7, c.Y + 1, fastTime.str(), 0x07);

	mes.str("");
	mes << "Press 'ESC' to return to the MAIN MENU";
	g_Console.writeToBuffer(a.X + 12, a.Y + 19, mes.str(), 0x07);

	// reads and writes leaderboard.txt for the leaderboard screen
	string sym;
	ifstream myfile("Leaderboard.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(a, sym, 0x07);
			a.Y++;
		}
		myfile.close();
	}

	renderArrow();
	moveArrow();

	if (g_abKeyPressed[K_ENTER] && arrow.Y == 15)
	{
		Highscore();
	}
	if (g_abKeyPressed[K_ENTER] && arrow.Y == 16)
	{
		FastTime();
	}
	// goes back to splash screen if escape is pressed
	if (g_abKeyPressed[K_ESCAPE] && (g_eGameState == S_LEADERBOARD)){
		g_eGameState = S_SPLASHSCREEN;
	}
}

void LoadLeaderboard()
{
	ifstream File("Leaderboard.csv");

		for (int columns = 0; columns <= 5; columns++)
		{
			for (int rows = 0; rows <= 2; rows++)
			{
				File >> Leaderboard[columns][rows];
			}
		}
	File.close();
}

void Highscore()
{
	LoadLeaderboard();
	if (Points > stoi(Leaderboard[0][1]))
	{
		Leaderboard[2][1] = Leaderboard[1][1];
		Leaderboard[1][1] = Leaderboard[0][1];
		OverallPoints >> Leaderboard[0][1];
		Leaderboard[2][2] = Leaderboard[1][2];
		Leaderboard[1][2] = Leaderboard[0][2];
		OverallTime >> Leaderboard[0][2];
		Leaderboard[2][0] = Leaderboard[1][0];
		Leaderboard[2][0] = Leaderboard[0][0];
		InputName >> Leaderboard[0][0];
	}
	else if ((Points > stoi(Leaderboard[1][1])) && (Points < stoi(Leaderboard[0][1])))
	{
		Leaderboard[2][1] = Leaderboard[1][1];
		OverallPoints >> Leaderboard[1][1];
		Leaderboard[2][1] = Leaderboard[1][1];
		OverallTime >> Leaderboard[1][1];
		Leaderboard[2][0] = Leaderboard[1][0];
		InputName >> Leaderboard[1][0];
	}
	else if ((Points > stoi(Leaderboard[2][1])) && (Points < stoi(Leaderboard[1][1])) && (Points < stoi(Leaderboard[0][1])))
	{
		OverallPoints >> Leaderboard[2][1];
		OverallTime >> Leaderboard[2][2];
		InputName >> Leaderboard[2][0];
	}
}

void FastTime()
{
	LoadLeaderboard();
	if (Time < stoi(Leaderboard[3][1]))
	{
		Leaderboard[5][1] = Leaderboard[4][1];
		Leaderboard[4][1] = Leaderboard[3][1];
		OverallPoints >> Leaderboard[3][1];
		Leaderboard[5][2] = Leaderboard[4][2];
		Leaderboard[4][2] = Leaderboard[3][2];
		OverallTime >> Leaderboard[3][2];
		Leaderboard[5][0] = Leaderboard[4][0];
		Leaderboard[4][0] = Leaderboard[3][0];
		InputName >> Leaderboard[3][0];
	}
	else if ((Time < stoi(Leaderboard[4][1])) && (Time > stoi(Leaderboard[3][1])))
	{
		Leaderboard[5][1] = Leaderboard[4][1];
		OverallPoints >> Leaderboard[5][1];
		Leaderboard[5][1] = Leaderboard[4][1];
		OverallTime >> Leaderboard[5][1];
		Leaderboard[5][0] = Leaderboard[4][0];
		InputName >> Leaderboard[5][0];
	}
	else if ((Time < stoi(Leaderboard[5][1])) && (Time > stoi(Leaderboard[4][1])) && (Time > stoi(Leaderboard[3][1])))
	{
		OverallPoints >> Leaderboard[5][1];
		OverallTime >> Leaderboard[5][2];
		InputName >> Leaderboard[5][0];
	}
}
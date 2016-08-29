#include "game.h"
extern SGameChar g_sChar;
extern Leaderboard Leaders[6];
extern bool g_abKeyPressed[K_COUNT];
extern EGAMESTATES g_eGameState;
extern COORD arrow;
extern bool playedGame;
bool changes;
extern bool setArrowMenu;
void renderLeaderboard()
{
	LeaderboardMenu();
}

void LoadLeaderboard();

void LeaderboardMenu()                                                          //"cout" highest score,fastest time,name,score and time
{
	changes = false;

	COORD c = g_Console.getConsoleSize();
	c.Y = c.Y / 2;
	c.X = c.X / 2;
	COORD a = g_Console.getConsoleSize();
	a.Y = 1;
	a.X = 10;
	ostringstream mes;
	ostringstream HighestScore;
	ostringstream FastestTime;
	ostringstream Name;
	ostringstream Score;
	ostringstream Time;

	HighestScore.str("");
	HighestScore << "Highest Score";       
	FastestTime.str("");
	FastestTime << "Fastest Time";
	Name.str("");
	Name << "Name";
	Time.str("");
	Time << "Time";
	Score.str("");
	Score << "Score";
	mes.str("");
	mes << "Press 'ESC' to return to the MAIN MENU";

	g_Console.writeToBuffer(c.X - 7, c.Y - 7, HighestScore.str(), 0x07);              ////////////////////////////////////////////////////////////////
	g_Console.writeToBuffer(c.X - 22, c.Y - 6, Name.str(), 0x07);
	g_Console.writeToBuffer(c.X - 2, c.Y - 6, Score.str(), 0x07);
	g_Console.writeToBuffer(c.X + 20, c.Y - 6, Time.str(), 0x07);
	g_Console.writeToBuffer(c.X - 6, c.Y, FastestTime.str(), 0x07);
	g_Console.writeToBuffer(c.X - 22, c.Y + 1, Name.str(), 0x07);
	g_Console.writeToBuffer(c.X - 2, c.Y + 1, Score.str(), 0x07);
	g_Console.writeToBuffer(c.X + 20, c.Y + 1, Time.str(), 0x07);
	g_Console.writeToBuffer(a.X + 12, a.Y + 23, mes.str(), 0x07);                     //the position highest score,fastest time,name,score and time

	// reads and writes leaderboard.txt for the leaderboard screen
	string sym;
	ifstream myfile("Leaderboard.txt");                                              //cout the ascii art for leaderboard

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(a, sym, 0x07);
			a.Y++;
		}
		myfile.close();
	}

	LoadLeaderboard();

	if (g_abKeyPressed[K_ESCAPE])
	{
		setArrowMenu = false;
		g_eGameState = S_SPLASHSCREEN;
		
	}

}

void LoadLeaderboard()
{
	int i = 0;

	ifstream File("Leaderboard.csv");                                          //get the data from the csv file
	while (File >> Leaders[i].Name >> Leaders[i].Score >> Leaders[i].Time)
	{
		i++;
	}
	File.close();

	if (playedGame == true)
	{
		Highscore();
		FastTime();
		playedGame = false;
	}

	for (int a = 0; a <= 2; a++)
	{
		COORD c = g_Console.getConsoleSize();                                      //cout the name,highest score score and time
		c.Y = c.Y / 2 - 5;
		c.X = c.X / 2;
		g_Console.writeToBuffer(c.X - 22, c.Y + a, Leaders[a].Name);
		g_Console.writeToBuffer(c.X - 2, c.Y + a, to_string(Leaders[a].Score));
		g_Console.writeToBuffer(c.X + 20, c.Y + a, to_string(Leaders[a].Time));
	}
		
	for (int a = 3; a <= 5; a++)                                                   //cout the name,fastest time score, and time
	{
		COORD c = g_Console.getConsoleSize();
		c.Y = c.Y / 2 - 1;
		c.X = c.X / 2;
		g_Console.writeToBuffer(c.X - 22, c.Y + a, Leaders[a].Name);
		g_Console.writeToBuffer(c.X - 2, c.Y + a, to_string(Leaders[a].Score));
		g_Console.writeToBuffer(c.X + 20, c.Y + a, to_string(Leaders[a].Time));
	}

	if (changes == true)                                                          //update the leaderboard.csv
	{

		ofstream MyFile("Leaderboard.csv");
		for (i = 0; i < 6; i++)
		{
			MyFile << Leaders[i].Name << " " << Leaders[i].Score << " " << Leaders[i].Time << endl;
		}
		File.close();
	}
}
	

void Highscore()
{
	if (g_sChar.points > Leaders[0].Score)
	{ // If player's score is higher than highest score
		Leaders[2].Score = Leaders[1].Score;
		Leaders[1].Score = Leaders[0].Score;
		Leaders[0].Score = g_sChar.points; // Puts player's points into array
		Leaders[2].Time = Leaders[1].Time;
		Leaders[1].Time = Leaders[0].Time;
		Leaders[0].Time = g_sChar.time; // Puts player's time into array
		Leaders[2].Name = Leaders[1].Name;
		Leaders[1].Name = Leaders[0].Name;
		Leaders[0].Name = g_sChar.Name; // Puts player's name into array
		changes = true;
	}
	else if ((g_sChar.points > Leaders[1].Score) && (g_sChar.points < Leaders[0].Score))
	{ // If player's score is higher than second highest score
		Leaders[2].Score = Leaders[1].Score;
		Leaders[1].Score = g_sChar.points; // Puts player's points into array
		Leaders[2].Time = Leaders[1].Time;
		Leaders[1].Time = g_sChar.time; // Puts player's time into array
		Leaders[2].Name = Leaders[1].Name;
		Leaders[1].Name = g_sChar.Name; // Puts player's name into array
		changes = true;
	}
	else if ((g_sChar.points > Leaders[2].Score) && (g_sChar.points < Leaders[1].Score) && (g_sChar.points < Leaders[0].Score))
	{ // If player's score is higher than third highest score
		Leaders[2].Score = g_sChar.points; // Puts player's points into array
		Leaders[2].Time = g_sChar.time; // Puts player's time into array
		Leaders[2].Name = g_sChar.Name; // Puts player's name into array
		changes = true;
	}
}
	
void FastTime()
{
	if ((g_sChar.time < Leaders[3].Time) && (Leaders[3].Time > 0) && (g_sChar.time > 0))
	{
		Leaders[5].Score = Leaders[4].Score;
		Leaders[4].Score = Leaders[3].Score;
		Leaders[3].Score = g_sChar.points; // Puts player's points into array
		Leaders[5].Time = Leaders[4].Time;
		Leaders[4].Time = Leaders[3].Time;
		Leaders[3].Time = g_sChar.time; // Puts player's time into array
		Leaders[5].Name = Leaders[4].Name;
		Leaders[4].Name = Leaders[3].Name;
		Leaders[3].Name = g_sChar.Name; // Puts player's name into array
		changes = true;
	}
	else if ((g_sChar.time < Leaders[4].Time) && (g_sChar.time > Leaders[3].Time) &&
		(g_sChar.time > 0) && (Leaders[4].Time > 0) && (Leaders[3].Time > 0))
	{
		Leaders[5].Score = Leaders[4].Score;
		Leaders[4].Score = g_sChar.points; // Puts player's points into array
		Leaders[5].Time = Leaders[4].Time;
		Leaders[4].Time = g_sChar.time; // Puts player's time into array
		Leaders[5].Name = Leaders[4].Name;
		Leaders[4].Name = g_sChar.Name; // Puts player's name into array
		changes = true;
	}
	else if ((g_sChar.time < Leaders[5].Time) && (g_sChar.time > Leaders[4].Time) && (g_sChar.time > Leaders[3].Time) &&
		(g_sChar.time > 0) && (Leaders[5].Time > 0))
	{
		Leaders[5].Score = g_sChar.points; // Puts player's points into array
		Leaders[5].Time = g_sChar.time; // Puts player's time into array
		Leaders[5].Name = g_sChar.Name; // Puts player's name into array
		changes = true;
	}

	if ((Leaders[3].Time == 0) && (Leaders[4].Time == 0) && (Leaders[5].Time == 0))
	{
		Leaders[3].Score = g_sChar.points; // Puts player's points into array
		Leaders[3].Time = g_sChar.time; // Puts player's time into array
		Leaders[3].Name = g_sChar.Name; // Puts player's name into array
		changes = true;
	}
	else if ((Leaders[4].Time == 0) && (Leaders[5].Time == 0))
	{
		Leaders[4].Score = g_sChar.points; // Puts player's points into array
		Leaders[4].Time = g_sChar.time; // Puts player's time into array
		Leaders[4].Name = g_sChar.Name; // Puts player's name into array
		changes = true;
	}
	else if (Leaders[5].Time == 0)
	{
		Leaders[5].Score = g_sChar.points; // Puts player's points into array
		Leaders[5].Time = g_sChar.time; // Puts player's time into array
		Leaders[5].Name = g_sChar.Name; // Puts player's name into array
		changes = true;
	}
}
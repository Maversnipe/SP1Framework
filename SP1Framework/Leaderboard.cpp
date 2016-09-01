#include "game.h"
extern SGameChar g_sChar;
extern Leaderboard Leaders[6];
extern bool g_abKeyPressed[K_COUNT];
extern EGAMESTATES g_eGameState;
extern COORD arrow;
extern bool playedGame;
extern bool playedGame1;
bool changesPoints;
bool changesTime;
extern bool setArrowMenu;
void renderLeaderboard()
{
	LeaderboardMenu();
}

void LoadLeaderboard();

void LeaderboardMenu()                                                          //"cout" highest score,fastest time,name,score and time
{
	changesPoints = false;
	changesTime = false;

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
	g_Console.writeToBuffer(a.X + 12, a.Y + 23, mes.str(), 0x07);                     //the position of highest score,fastest time,name,score and time

	// reads and writes leaderboard.txt for the leaderboard screen
	string sym;
	ifstream myfile("Menu/Leaderboard.txt");                                              //cout the ascii art for leaderboard

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
		g_sChar.Name = "";
		setArrowMenu = false;
		g_eGameState = S_SPLASHSCREEN;
		
	}

}

void LoadLeaderboard()
{
	int i = 0;

	ifstream File("Menu/Leaderboard.csv");                                          //get the data from the csv file
	while (File >> Leaders[i].Name >> Leaders[i].Score >> Leaders[i].Time)
	{
		i++;
	}
	File.close();

	if (playedGame == true && playedGame1 == true )                            //the player has to play from level 1 to 10 so that he/she will get the score after he/she completed the game
	{
		Highscore();
		FastTime();
		playedGame = false;
		playedGame1 = false;
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

	if (changesPoints == true || changesTime == true)                                                          //update the leaderboard.csv
	{
		ofstream MyFile("Menu/Leaderboard.csv");
		for (i = 0; i < 6; i++)
		{
			MyFile << Leaders[i].Name << " " << Leaders[i].Score << " " << Leaders[i].Time << endl;
		}
		File.close();
	}
}
	

void Highscore()
{
	if ((g_sChar.points > Leaders[0].Score) || ((g_sChar.points == Leaders[0].Score) && 
		(g_sChar.time < Leaders[0].Time) && (Leaders[0].Time != 0)) || (Leaders[0].Time == 0.0) && (Leaders[0].Score == 0))
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
		changesPoints = true;
	}
	else if ((g_sChar.points > Leaders[1].Score) && (g_sChar.points < Leaders[0].Score) || ((g_sChar.points == Leaders[1].Score) && 
		(Leaders[1].Time != 0) && (g_sChar.time > Leaders[1].Time)) || (Leaders[1].Time == 0.0) && (Leaders[1].Score == 0))
	{ // If player's score is higher than second highest score but lesser than the highest score
		Leaders[2].Score = Leaders[1].Score;
		Leaders[1].Score = g_sChar.points; // Puts player's points into array
		Leaders[2].Time = Leaders[1].Time;
		Leaders[1].Time = g_sChar.time; // Puts player's time into array
		Leaders[2].Name = Leaders[1].Name;
		Leaders[1].Name = g_sChar.Name; // Puts player's name into array
		changesPoints = true;
	}
	else if ((g_sChar.points > Leaders[2].Score) && (g_sChar.points < Leaders[1].Score) && (g_sChar.points < Leaders[0].Score) || ((g_sChar.points == Leaders[2].Score) && 
		(Leaders[2].Time != 0) && (g_sChar.time > Leaders[2].Time)) || (Leaders[2].Time == 0.0) && (Leaders[2].Score == 0))
	{ // If player's score is higher than third highest score but lesser than the second highest score and the highest score
		Leaders[2].Score = g_sChar.points; // Puts player's points into array
		Leaders[2].Time = g_sChar.time; // Puts player's time into array
		Leaders[2].Name = g_sChar.Name; // Puts player's name into array
		changesPoints = true;
	}
}
	
void FastTime()
{
	if ((g_sChar.time < Leaders[3].Time) && (Leaders[3].Time != 0) && (g_sChar.time != 0))
	{//when the player's time is lesser than the fastest time.
		Leaders[5].Score = Leaders[4].Score;
		Leaders[4].Score = Leaders[3].Score;
		Leaders[3].Score = g_sChar.points; // Puts player's points into array
		Leaders[5].Time = Leaders[4].Time;
		Leaders[4].Time = Leaders[3].Time;
		Leaders[3].Time = g_sChar.time; // Puts player's time into array
		Leaders[5].Name = Leaders[4].Name;
		Leaders[4].Name = Leaders[3].Name;
		Leaders[3].Name = g_sChar.Name; // Puts player's name into array
		changesTime = true;
	}
	else if ((g_sChar.time < Leaders[4].Time) && (g_sChar.time > Leaders[3].Time) &&
		(g_sChar.time != 0) && (Leaders[4].Time != 0) && (Leaders[3].Time != 0))
	{//when the player's time is lesser than the 2nd fastest time but more than the top fastest time.
		Leaders[5].Score = Leaders[4].Score;
		Leaders[4].Score = g_sChar.points; // Puts player's points into array
		Leaders[5].Time = Leaders[4].Time;
		Leaders[4].Time = g_sChar.time; // Puts player's time into array
		Leaders[5].Name = Leaders[4].Name;
		Leaders[4].Name = g_sChar.Name; // Puts player's name into array
		changesTime = true;
	}
	else if ((g_sChar.time < Leaders[5].Time) && (g_sChar.time > Leaders[4].Time) && (g_sChar.time > Leaders[3].Time) &&
		(g_sChar.time != 0) && (Leaders[5].Time != 0) && (Leaders[4].Time != 0) && (Leaders[3].Time != 0))
	{//when the player's time is lesser than the 3rd fastest but more than the 2nd and 1st.
		Leaders[5].Score = g_sChar.points; // Puts player's points into array
		Leaders[5].Time = g_sChar.time; // Puts player's time into array
		Leaders[5].Name = g_sChar.Name; // Puts player's name into array
		changesTime = true;
	}

	if ((Leaders[3].Time == 0) && (Leaders[4].Time == 0) && (Leaders[5].Time == 0) && (changesTime == false))
	{//putting the player's score,time,name in the 1st place for the fastest time score category
		Leaders[3].Score = g_sChar.points; // Puts player's points into array
		Leaders[3].Time = g_sChar.time; // Puts player's time into array
		Leaders[3].Name = g_sChar.Name; // Puts player's name into array
		changesTime = true;
	}
	else if ((Leaders[3].Time != 0) && (Leaders[4].Time == 0) && (Leaders[5].Time == 0) && (changesTime == false))
	{//putting the player's score,time,name in the 2nd place for the fastest time score category
		Leaders[4].Score = g_sChar.points; // Puts player's points into array
		Leaders[4].Time = g_sChar.time; // Puts player's time into array
		Leaders[4].Name = g_sChar.Name; // Puts player's name into array
		changesTime = true;
	}
	else if ((Leaders[3].Time != 0) && (Leaders[4].Time != 0) && (Leaders[5].Time == 0) && (changesTime == false))
	{//putting the player's score,time name in the 3rd place for the fastest time score category
		Leaders[5].Score = g_sChar.points; // Puts player's points into array
		Leaders[5].Time = g_sChar.time; // Puts player's time into array
		Leaders[5].Name = g_sChar.Name; // Puts player's name into array
		changesTime = true;
	}
}
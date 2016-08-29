#include "game.h"
#include <vector>
extern bool g_abKeyPressed[K_COUNT];
extern char Map[20][100][100];
extern EGAMESTATES g_eGameState;
extern COORD arrow;
extern stringstream overalltime;
extern stringstream overallpoints;
extern stringstream inputname;
#include <vector>
extern int points;
extern int g_dTotalPoints;
int highscore = 0;
int score = g_dTotalPoints;
extern double g_dTimer;
extern double g_dShortestTime;
vector<int> allscores;
vector<int>STORESCORES;
vector<int>alltime;
vector<int>STORETIME;
void leaderboard()
{
	COORD c = g_Console.getConsoleSize();
		c.Y = c.Y / 2;
		c.X = c.X / 2;
		COORD a = g_Console.getConsoleSize();
		a.Y = 5;
		a.X = 5;
		COORD t = g_Console.getConsoleSize();
		t.Y = 5;
		t.X = 20;
//		 reads and writes leaderboard.txt for the leaderboard screen
		string sym;
		ifstream myfile("scoresystem.txt");
		if (myfile.is_open())
		{
			while (getline(myfile, sym))//this get line function is to get the one line from the text file and assign it into sym.
			{
				bool tcheck2 = false;
				bool scheck = false;
				bool tcheck = false;
				string timestr;
				string scorestr;
				for (int L = 0; L < sym.length(); L++)//check all the characters in that line.
				{
					if (scheck)
					{
						scorestr += sym[L];//starts storing the number

					}
					if (sym[L] == ',')
					{
						scheck = true;//when 1st comma is reached set to true.
					}
					if (sym[L+1] == ',' && scheck == true)//when it reaches the 2nd comma, the "switch" will be off
					{
						scheck = false;//it is to stop getting any more characters from that line.
						break;
					}
	
				}
				for (int O = 0; O < sym.length(); O++)
				{
					if (tcheck2)
					{
						timestr += sym[O];
					}
					if (sym[O] == ','&& tcheck == true)
					{
						tcheck2 = true;
					}
					if (sym[O] == ',')
					{
						tcheck = true;
					}

				}
				allscores.push_back(stoi(scorestr));//change string to integer and store into allscores.
				alltime.push_back(stoi(timestr));

			}
			myfile.close();
		}
////////////////////////////////////////////////////////////////////////////for highscore////////////////////////////////////////////////////////////////
		for (int j = 0; j < 3; j++)//get three of the highscore
		{
			int tempo = 0;
			for (int i = 0; i < allscores.size(); i++)
			{

				if (allscores[i] > tempo)//will start comparing.
				{
					bool insidestorescore = false;                //check if is already inside the high score system.
					for (int k = 0; k < STORESCORES.size(); k++)
					{
						if (allscores[i] == STORESCORES[k])
						{
							insidestorescore = true;
						}
					}
					if (insidestorescore == false)
					{

						tempo = allscores[i];
					}
				}
			}
			STORESCORES.push_back(tempo);
		}
		for (int i = 0; i < 3; i++)
		{
			g_Console.writeToBuffer(a, to_string(STORESCORES[i]));//print out
			a.Y++;
		}
		
///////////////////////////////////////////////////////////////////////end of high score////////////////////////////////////////////////////////////////////////////
		//for time
		for (int q = 0; q < 3; q++)//get three of the highscore
		{
			int temporary = 0;
			for (int i = 0; i < alltime.size(); i++)
			{

				if (alltime[i] > temporary)//will start comparing.
				{
					bool insidestorestime = false;                
					for (int k = 0; k < STORETIME.size(); k++)
					{
						if (alltime[i] == STORETIME[k])
						{
							insidestorestime = true;
						}
					}
					if (insidestorestime == false)
					{

						temporary = alltime[i];
					}
				}
			}
			STORETIME.push_back(temporary);
		}
		for (int i = 0; i < 3; i++)
		{
			g_Console.writeToBuffer(t, to_string(STORETIME[i]));//print out
			t.Y++;
		}
		if (g_abKeyPressed[K_ESCAPE] && g_eGameState == S_LEADERBOARD)
		{
			g_eGameState = S_SPLASHSCREEN;
		}
        
}


//void FastTime(int time, string timename, int fastesttime[], string TimeName[])
//{
//	long int sub;
//	long int sub2;
//	string subname;
//	string subname2;
//	long int fasttesttime[3];
//	long int TIME;
//	string TIMENAME;
//	string fastesttimename[3];
//	if (time < fasttesttime[0])
//	{
//		sub = fastesttime[0];
//		subname = fasttesttime[0];
//		fasttesttime[0] = time;
//		fastesttimename[0] = time;
//		for (int i = 0; i < 3; i++)
//		{
//			sub2 = fastesttime[i];
//			subname2 = fastesttimename[i];
//			fastesttime[i] = sub;
//			fastesttimename[i] = subname;
//			sub = sub2;
//			subname = subname2;
//		}
//	}
//}
//string Leaderboard[5][2];
//
//
//void renderLeaderboard()
//{
//	LeaderboardMenu();
//}
//
//void LeaderboardMenu()
//{
//	COORD c = g_Console.getConsoleSize();
//	c.Y = c.Y / 2;
//	c.X = c.X / 2;
//	COORD a = g_Console.getConsoleSize();
//	a.Y = 5;
//	a.X = 10;
//
//	ostringstream highScore;
//	ostringstream fastTime;
//	ostringstream mes;
//	highScore.str("");
//	fastTime.str("");
//	highScore << "HIGHEST SCORES";
//	fastTime << "SHORTEST TIMES"; // shows the highest score + shortest time
//	g_Console.writeToBuffer(c.X - 7, c.Y, highScore.str(), 0x07);
//	g_Console.writeToBuffer(c.X - 7, c.Y + 1, fastTime.str(), 0x07);
//
//	mes.str("");
//	mes << "Press 'ESC' to return to the MAIN MENU";
//	g_Console.writeToBuffer(a.X + 12, a.Y + 19, mes.str(), 0x07);
//
//	 reads and writes leaderboard.txt for the leaderboard screen
//	string sym;
//	ifstream myfile("Leaderboard.txt");
//
//	if (myfile.is_open())
//	{
//		while (getline(myfile, sym))
//		{
//			g_Console.writeToBuffer(a, sym, 0x07);
//			a.Y++;
//		}
//		myfile.close();
//	}
//
//	renderArrow();
//	moveArrow();
//
//	if (g_abKeyPressed[K_ENTER] && arrow.Y == 15)
//	{
//		Highscore();
//	}
//	if (g_abKeyPressed[K_ENTER] && arrow.Y == 16)
//	{
//		FastTime();
//	}
//	 goes back to splash screen if escape is pressed
//	if (g_abKeyPressed[K_ESCAPE] && (g_eGameState == S_LEADERBOARD)){
//		g_eGameState = S_SPLASHSCREEN;
//	}
//}
//
//void LoadLeaderboard()
//{
//	ifstream File("Leaderboard.csv");
//
//		for (int columns = 0; columns <= 5; columns++)
//		{
//			for (int rows = 0; rows <= 2; rows++)
//			{
//				File >> Leaderboard[columns][rows];
//			}
//		}
//	File.close();
//}
//
//void Highscore()
//{
//	LoadLeaderboard();
//	if (Points > stoi(Leaderboard[0][1]))
//	{
//		Leaderboard[2][1] = Leaderboard[1][1];
//		Leaderboard[1][1] = Leaderboard[0][1];
//		OverallPoints >> Leaderboard[0][1];
//		Leaderboard[2][2] = Leaderboard[1][2];
//		Leaderboard[1][2] = Leaderboard[0][2];
//		OverallTime >> Leaderboard[0][2];
//		Leaderboard[2][0] = Leaderboard[1][0];
//		Leaderboard[2][0] = Leaderboard[0][0];
//		InputName >> Leaderboard[0][0];
//	}
//	else if ((Points > stoi(Leaderboard[1][1])) && (Points < stoi(Leaderboard[0][1])))
//	{
//		Leaderboard[2][1] = Leaderboard[1][1];
//		OverallPoints >> Leaderboard[1][1];
//		Leaderboard[2][1] = Leaderboard[1][1];
//		OverallTime >> Leaderboard[1][1];
//		Leaderboard[2][0] = Leaderboard[1][0];
//		InputName >> Leaderboard[1][0];
//	}
//	else if ((Points > stoi(Leaderboard[2][1])) && (Points < stoi(Leaderboard[1][1])) && (Points < stoi(Leaderboard[0][1])))
//	{
//		OverallPoints >> Leaderboard[2][1];
//		OverallTime >> Leaderboard[2][2];
//		InputName >> Leaderboard[2][0];
//	}
//}
//
//void FastTime()
//{
//	LoadLeaderboard();
//	if (Time < stoi(Leaderboard[3][1]))
//	{
//		Leaderboard[5][1] = Leaderboard[4][1];
//		Leaderboard[4][1] = Leaderboard[3][1];
//		OverallPoints >> Leaderboard[3][1];
//		Leaderboard[5][2] = Leaderboard[4][2];
//		Leaderboard[4][2] = Leaderboard[3][2];
//		OverallTime >> Leaderboard[3][2];
//		Leaderboard[5][0] = Leaderboard[4][0];
//		Leaderboard[4][0] = Leaderboard[3][0];
//		InputName >> Leaderboard[3][0];
//	}
//	else if ((Time < stoi(Leaderboard[4][1])) && (Time > stoi(Leaderboard[3][1])))
//	{
//		Leaderboard[5][1] = Leaderboard[4][1];
//		OverallPoints >> Leaderboard[5][1];
//		Leaderboard[5][1] = Leaderboard[4][1];
//		OverallTime >> Leaderboard[5][1];
//		Leaderboard[5][0] = Leaderboard[4][0];
//		InputName >> Leaderboard[5][0];
//	}
//	else if ((Time < stoi(Leaderboard[5][1])) && (Time > stoi(Leaderboard[4][1])) && (Time > stoi(Leaderboard[3][1])))
//	{
//		OverallPoints >> Leaderboard[5][1];
//		OverallTime >> Leaderboard[5][2];
//		InputName >> Leaderboard[5][0];
//	}
//}
//for (int i = 0; i < sym.length(); i++)
//{
//	if (sym[i]!=',')
//	g_Console.writeToBuffer(a, sym[i], 0x07);//everything remains the same
//	else
//		g_Console.writeToBuffer(a,' ', 0x07);//replace ',' with ' '
//	a.X++;
//}

//a.X = 5;
//a.Y++;
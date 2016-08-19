// This is the main file for the game logic and function
//
//
#include <string>
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdlib.h>
extern Console g_Console;

char MapOne[100][100];
char MapBonus[100][100];
char Map[100][100];

COORD arrow;
bool setArrow = false;
int LevelSelection = 1;

double  g_dElapsedTime;
int g_dTotalPoints;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(80, 30, "Crystal Temple");
//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;
	g_dTotalPoints = 0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

	Map[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] = Map[5][2];
	g_sChar.m_cLocation.X = 4;
	g_sChar.m_cLocation.Y = 21;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput(void)
{
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
	g_abKeyPressed[K_W] = isKeyPressed(VK_W);
	g_abKeyPressed[K_S] = isKeyPressed(VK_S);
	g_abKeyPressed[K_A] = isKeyPressed(VK_A);
	g_abKeyPressed[K_D] = isKeyPressed(VK_D);
	g_abKeyPressed[K_R] = isKeyPressed(VK_R);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
	if (g_eGameState == S_GAME){
		g_dElapsedTime += dt;
	}
		g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
		case S_GAME: gameplay(); // gameplay logic when we are in the game
			break;
		case S_PAUSE: renderPauseScreen();
			break;
		case S_SELECT:renderselectlevel();
			break;
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
		case S_GAME: renderGame();
			renderFramerate();
			break;
		case S_PAUSE: renderPauseScreen();
			break;
		case S_SELECT:renderselectlevel();
			break;
    }  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if ((g_eGameState == S_SPLASHSCREEN) && (g_abKeyPressed[K_ENTER])) // Press Enter to start game
        g_eGameState = S_GAME;
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter(); // moves the character, collision detection, physics, etc sound can be played here too.
	pointSystem(); // Points added (test).
}


void moveCharacter()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if ((g_abKeyPressed[K_W]) && (g_sChar.m_cLocation.Y > 0))//Move Up [W] Key
	{
		//Beep(1440, 30);
		if (Map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != '=' && Map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != '|' && Map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != 'r')
		if ((Map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X]) != '=' && (Map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X]) != '|')
		{
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
	}
	if ((g_abKeyPressed[K_UP]) && (g_sChar.m_cLocation.Y > 0))//Move Up [UP] Key
	{
		//Beep(1440, 30);
		if (Map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != '=' && Map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != '|' && Map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != 'r')
		if ((Map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X]) != '=' && (Map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != '|'))
		{
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
	}
	if ((g_abKeyPressed[K_A]) && (g_sChar.m_cLocation.X > 0))//Move Left [A] Key
	{
		//Beep(1440, 30);
		if (Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != '=' && Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != '|' && Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != 'r')
		if ((Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1]) != '=' && (Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != '|'))
		{
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
	}
	if ((g_abKeyPressed[K_LEFT]) && (g_sChar.m_cLocation.X > 0))//Move Left [LEFT] Key
    {
        //Beep(1440, 30);
		if (Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != '=' && Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != '|' && Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != 'r')
		if ((Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != '=') && (Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != '|'))
		{
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
    }
	if ((g_abKeyPressed[K_S]) && (g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1))//Move Down [S] Key
	{
		//Beep(1440, 30);
		if ((Map[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != '=') && (Map[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != '|') && (Map[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != 'r'))
		{
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
	}
	if ((g_abKeyPressed[K_DOWN]) && (g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1))//Move Down [DOWN] Key
    {
        //Beep(1440, 30);
		if ((Map[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X]) != '=' && (Map[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != '|') && (Map[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != 'r'))
		{
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
    }
	if ((g_abKeyPressed[K_D]) && (g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1))//Move Right [D] Key
	{
		//Beep(1440, 30);
		if (Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != '=' && Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != '|' && Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != 'r')
		if ((Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1]) != '=' && (Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != '|'))
		{
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}
	}
	if ((g_abKeyPressed[K_RIGHT]) && (g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1))//Move Right [RIGHT] Key
    {
        //Beep(1440, 30);
		if (Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != '=' && Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != '|' && Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != 'r')
		if ((Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != '=') && (Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != '|'))
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
		g_dBounceTime = g_dElapsedTime + 0.125 ; // 125ms should be enough
    }
}

void pointSystem()
{
	if ((Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X]) == '1')
	{
		MapBonus[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
		g_dTotalPoints += 100;
	}
	if ((Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X]) == '2')
	{
		MapBonus[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
		g_dTotalPoints += 200;
	}
	if ((Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X]) == '5')
	{
		MapBonus[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
		g_dTotalPoints += 500;
	}
	if ((Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X]) == 'A')
	{
		MapBonus[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
		g_dTotalPoints += 1000;
	}
}
	
void processUserInput()
{
    // pauses the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE]){
		g_eGameState = S_PAUSE;
	}
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x00);
}

void titleText() {
	COORD c = g_Console.getConsoleSize();
	c.Y = 4;
	c.X = 7;

	string sym;
	ifstream myfile("GameTitle.txt");

	if (myfile.is_open()){
		while (getline(myfile, sym)) {
			g_Console.writeToBuffer(c, sym, 0x0B);
			c.Y++;
		}
		myfile.close();
	}
}

void renderSplashScreen()  // renders the splash screen
{
	titleText();
    COORD c = g_Console.getConsoleSize();
    c.Y = c.Y / 2;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "Start Game", 0x07);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "Options", 0x07);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "Leaderboard", 0x07);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x07);
	renderarrow();

	if (g_abKeyPressed[K_ESCAPE]){
		g_bQuitGame = true;
	}
	movearrow();
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
}

void renderMap()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

	LevelFive();

/*	if (LevelSelection == 11)
	COORD c;
	c.X = 0;
	c.Y = 0;

	if (LevelSelection == 1)
	{
		for (int rows = 0; rows < 25; rows++)
		{

			for (int columns = 0; columns < 55; columns++)
			{
				Map[rows][columns] = MapOne[rows][columns];
			}
		}
	}
	else if (LevelSelection == 11)
	{
		for (int rows = 0; rows < 25; rows++)
		{
			for (int columns = 0; columns < 55; columns++)
			{
				Map[rows][columns] = MapBonus[rows][columns];
			}
		}
	}
	LevelClear(); */
=======

	LevelClear();

	for (int rows = 0; rows < 25; rows++)
	{
		c.Y = rows;
		for (int columns = 0; columns < 55; columns++)
		{
			if (Map[rows][columns] == 'i')
			{
				Map[rows][columns] = ' ';
			}
			c.X = columns;
			g_Console.writeToBuffer(c, Map[rows][columns], 0x0a);
		}
	}
}

void renderCharacter()
{
    // Draw the location of the character
	WORD charColor = 0x06;
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)232, charColor);
}

void renderarrow()
{
	if (setArrow == false)
	{
		arrow.X = 25;
		arrow.Y = 15;
		g_Console.writeToBuffer(arrow, ">");
		setArrow = true;
	}
	// Draw the location of the character
	WORD charColor = 0x06;
	g_Console.writeToBuffer(arrow, ">", charColor);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 11;
    c.Y = 1;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << (int) g_dElapsedTime << " secs";
    c.X = 2;
    c.Y = 1;
    g_Console.writeToBuffer(c, ss.str());

	// displays the points
	ss.str("");
	ss << "Points: " << g_dTotalPoints;
	c.X = 20;
	c.Y = 1;
	g_Console.writeToBuffer(c, ss.str());
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void pauseControls(){
	if (g_abKeyPressed[K_ENTER]){
		g_eGameState = S_GAME;
	}

	if (g_abKeyPressed[K_SPACE]){
		g_dElapsedTime = 0.0;
		g_dTotalPoints = 0;
		g_eGameState = S_SPLASHSCREEN;
	}
}

void renderPauseScreen(){
		COORD c = g_Console.getConsoleSize();
		c.Y = 7;
		c.X = 15;

		string sym;
		ifstream myfile("PauseScreen.txt");

		if (myfile.is_open()){
			while (getline(myfile, sym)) {
				g_Console.writeToBuffer(c, sym, 0x0B);
				c.Y++;
			}
			myfile.close();
		}
		pauseControls();
}
void movearrow()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;
	if (g_abKeyPressed[K_UP] && arrow.Y > 15)
	{
		arrow.Y--;
		bSomethingHappened = true;
		g_Console.writeToBuffer(arrow, ">");

	}
	if (g_abKeyPressed[K_DOWN] && arrow.Y < 18)
	{
		arrow.Y++;
		bSomethingHappened = true;
		g_Console.writeToBuffer(arrow, ">");
	}
	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}

void LevelClear()
{
	if (LevelSelection == 1 && (Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '2'))
		LevelSelection = 11;
	if (LevelSelection == 11 && (Map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'B'))
		LevelSelection = 1;
}
void renderselectlevel()
{
		COORD c = g_Console.getConsoleSize();
		c.Y = 0;
		c.X = 0;

		string sym;
		ifstream myfile("levelselection.txt");

		if (myfile.is_open())
		{
			while (getline(myfile, sym)) 
			{
				g_Console.writeToBuffer(c, sym, 0x0B);
				c.Y++;
			}
			myfile.close();
		}
		selectlevel();
}

void selectlevel()
{
	if (g_abKeyPressed[K_ENTER])
	{
		g_eGameState=S_SELECT;
	}
}

void LoadMaps()
{
	LevelOne();
	/*LevelTwo();
	LevelThree();
	LevelFour();
	LevelFive();
	LevelSix();
	LevelSeven();
	LevelEight();
	LevelNine();
	LevelTen();*/
	BonusRoom();
}
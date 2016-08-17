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

double  g_dElapsedTime;
int g_dTotalPoints;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

int g_dBoulders;
int g_dBonusKey;
int g_dMainKey;

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(80, 25, "Crystal Temple");

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

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
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
	g_abKeyPressed[K_ONE] = isKeyPressed(VK_ONE);
	g_abKeyPressed[K_TWO] = isKeyPressed(VK_TWO);
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
		case S_PAUSE: paused(); // game logic when game is paused
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
            break;
		case S_PAUSE: renderPauseScreen();
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_abKeyPressed[K_ENTER]){ // wait for 3 seconds to switch to game mode, else do nothing
		g_eGameState = S_GAME;
	}

	if (g_abKeyPressed[K_ESCAPE]){
		g_bQuitGame = true;
	}

	/* if (g_abKeyPressed[K_ONE]){
	g_eGameState = S_OPTIONS;
	}

	if (g_abKeyPressed[K_TWO]){
	g_eGameState = S_LEADERBOARD;
	} 
	
	-- Commented out because the game states S_OPTIONS and S_LEADERBOARD are not done yet.
	*/
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void moveCharacter()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (g_abKeyPressed[K_W] && g_sChar.m_cLocation.Y > 0)
	{
		//Beep(1440, 30);
		g_sChar.m_cLocation.Y--;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_UP]&& g_sChar.m_cLocation.Y > 0)
	{
		//Beep(1440, 30);
		g_sChar.m_cLocation.Y--;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_A] && g_sChar.m_cLocation.X > 0)
	{
		//Beep(1440, 30);
		
		g_sChar.m_cLocation.X--;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_LEFT]  && g_sChar.m_cLocation.X > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;
        bSomethingHappened = true;
    }
	if (g_abKeyPressed[K_S] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		//Beep(1440, 30);
		g_sChar.m_cLocation.Y++;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y-1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;
        bSomethingHappened = true;
    }
	if (g_abKeyPressed[K_D] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		//Beep(1440, 30);
		g_sChar.m_cLocation.X++;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_RIGHT]&& g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;
        bSomethingHappened = true;
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
void processUserInput()
{
    // quits the game if player hits the escape key
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

	std::string sym;
	std::ifstream myfile("GameTitle.txt");

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
    g_Console.writeToBuffer(c, "Enter - Start Game", 0x07);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "1 - Options", 0x07);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "2 - Leaderboard", 0x07);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "Esc - Quit Game", 0x07);
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

    COORD c;
    for (int i = 0; i < 12; ++i)
    {
        c.X = 6;
        c.Y = i + 3;
		colour(0x02);
		g_Console.writeToBuffer(c, "##########################", 0x02);
    } 
}

void renderCharacter()
{
    // Draw the location of the character
	WORD charColor = 0x06;
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)232, charColor);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
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

void paused(){
	renderPauseScreen();
	pauseScreenChoices();
}

void pauseScreenChoices(){
	if (g_abKeyPressed[K_ENTER]){
		g_eGameState = S_GAME;
	}
	if (g_abKeyPressed[K_SPACE]){
		g_dElapsedTime = 0.0;
		g_dBounceTime = 0.0;
		g_dTotalPoints = 0;
		g_eGameState = S_SPLASHSCREEN;
	}
}

void renderPauseScreen(){
		std::string sym;
		std::ifstream myfile("PauseScreen.txt");

		COORD c = g_Console.getConsoleSize();
		c.Y = 4;
		c.X = 15;

		if (myfile.is_open()){
			while (getline(myfile, sym)) {
				g_Console.writeToBuffer(c, sym, 0x07);
				c.Y++;
			}
			myfile.close();
		}
}

void OptionsChoices(){
	if (g_abKeyPressed[K_ENTER]){
		// enter options
	}

	if (g_abKeyPressed[K_UP] || g_abKeyPressed[K_W]){
		// move up
	}

	if (g_abKeyPressed[K_UP] || g_abKeyPressed[K_S]){
		// move down
	}

	if (g_abKeyPressed[K_ESCAPE]){
		g_eGameState = S_SPLASHSCREEN;
	}
}

void renderOptions(){
	std::string sym;
	std::ifstream myfile("options.txt");

	COORD c = g_Console.getConsoleSize();
	c.Y = 4;
	c.X = 15;

	if (myfile.is_open()){
		while (getline(myfile, sym)) {
			g_Console.writeToBuffer(c, sym, 0x07);
			c.Y++;
		}
		myfile.close();
	}
}

void renderLB(){
	std::string sym;
	std::ifstream myfile("Leaderboard.txt");

	COORD c = g_Console.getConsoleSize();
	c.Y = 4;
	c.X = 0;

	if (myfile.is_open()){
		while (getline(myfile, sym)) {
			g_Console.writeToBuffer(c, sym, 0x07);
			c.Y++;
		}
		myfile.close();
	}
}
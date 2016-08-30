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

char Map[20][100][100];

COORD arrow;
bool setArrowMenu = false;
bool setArrowSelect = false;
bool setArrowOption = false;
bool setArrowLeaderboard = false;
int LevelSelection = 1;
int AxeUses = 0;
int Battery = 0;
double g_dElapsedTime;
double g_dTimer;
double g_dMenuToSelectTimer;
double g_dDoorTime;
double g_dSpikeTime;
int g_dTotalPoints;
double  g_dDeltaTime;
bool g_abKeyPressed[K_COUNT];
bool bonusTimeKey;
bool treeAxe = false;
bool onRock = false;
int SavedPoints = 0;
bool playedGame;
bool playedGame1;
extern bool changes;
int i = 0;

// Game specific variables here
SGameChar g_sChar;
EnemyChar Enemy[3];
Leaderboard Leaders[6];
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
	g_dTimer = 0.0;
    g_dBounceTime = 0.0;
	g_dTotalPoints = 0;
	g_dMenuToSelectTimer = 0.0;
	g_dDoorTime = 0.0;

    // sets the initial state for the game
	g_eGameState = S_SPLASHSCREEN;
	PlaySound(TEXT("Menu.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Arial");
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
	g_abKeyPressed[K_C] = isKeyPressed(VK_C);
	g_abKeyPressed[K_B] = isKeyPressed(VK_B);
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
		g_dElapsedTime += dt;
		g_dDeltaTime = dt;

		if (g_eGameState == S_GAME)
		{
			g_dTimer += dt;
		}

		switch (g_eGameState)
		{
		case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
			break;
		case S_GAME: gameplay(); // gameplay logic when we are in the game
			break;
		case S_PAUSE: renderPauseScreen(); // logic for the pause screen
			break;
		case S_SELECT:renderSelectLevel(); // screen that follows starting the game, to pick your level
			break;
		case S_INSTRUCTIONS: renderInstructions(); // screen that shows game instructions
			break;
		case S_RESTART: restart(); // logic for restarting the game
			break;
		case S_LEADERBOARD:
			//leaderboard(); // logic for the leaderboard
			renderLeaderboard();
			break;
		case S_OPTION:renderOption(); // logic for the options
			break;
		case S_CREDITS:renderCredits(); // credits screen
			break;
		case S_STORY:renderStory();
			break;
		case S_GAMEOVER:rendergameover();
			break;
		case S_GAMEOVER2:rendergameover2();
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
        case S_SPLASHSCREEN: 
			renderArrow();
			moveArrow();
			renderSplashScreen();
            break;
		case S_GAME: renderGame();
			renderFramerate();
			break;
		case S_PAUSE: renderPauseScreen();
			break;
		case S_SELECT: renderSelectLevel();
			break;
		case S_INSTRUCTIONS: renderInstructions();
			break;
		case S_RESTART: restart();
			break;
		case S_LEADERBOARD:
			//leaderboard();
			renderLeaderboard();
			break;
		case S_OPTION:renderOption();
			break;
		case S_CREDITS:renderCredits();
			break;
		case S_STORY: renderStory();
			break;
		case S_GAMEOVER:rendergameover();
			break;
		case S_GAMEOVER2:rendergameover2();
			break;
    }  // renders everything required for the screens

	light();
    renderToScreen();
	// dump the contents of the buffer to the screen, one frame worth of game
}
void restart()
{
	// restart function for the game, checks for the level so the game will know which level to restart at
	switch (LevelSelection)
	{
	case 1: // level one
		LevelOne();
		break;

	case 2: // level two
		LevelTwo();
		break;

	case 3: // level three
		LevelThree();
		break;

	case 4: // level four
		LevelFour();
		break;

	case 5: // level five
		LevelFive();
		break;

	case 6: // level six
		LevelSix();
		break;

	case 7: // level seven
		LevelSeven();
		break;

	case 8: // level eight
		LevelEight();
		break;

	case 9: // level nine
		LevelNine();
		break;

	case 10: // level ten
		LevelTen();
		break;
	}
	g_eGameState = S_GAME;
	charSpawn();
	AiSpawn();
	treeAxe = false;
	AxeUses = 0;
	bonusTimeKey = false;
	g_dTotalPoints = SavedPoints;
}

void splashScreenWait() // checks the player input on the splash screen
{
	if ((g_eGameState == S_SPLASHSCREEN) && (g_abKeyPressed[K_ENTER]) && (arrow.Y == 15) && g_dElapsedTime >= g_dMenuToSelectTimer) // Level Selection
	{
		g_dMenuToSelectTimer = g_dElapsedTime + 0.25; // 0.25s delay in order to avoid sending player to level one automatically
		g_eGameState = S_SELECT;
	}
	if (g_eGameState == S_SPLASHSCREEN && g_abKeyPressed[K_ENTER] && arrow.Y == 16 && g_dElapsedTime >= g_dMenuToSelectTimer) // options
	{
		g_eGameState = S_OPTION;
		g_dMenuToSelectTimer = g_dElapsedTime + 0.25; // 0.25s delay in order to avoid making player change an option immediately
	}

	if ((g_eGameState == S_SPLASHSCREEN) && (g_abKeyPressed[K_ENTER]) && (arrow.Y == 17) && g_dElapsedTime >= g_dMenuToSelectTimer) // Instructions
	{
		g_eGameState = S_INSTRUCTIONS;
	}
	if (g_eGameState == S_SPLASHSCREEN && g_abKeyPressed[K_ENTER] && arrow.Y == 18 && g_dElapsedTime >= g_dMenuToSelectTimer) //leaderboard
	{
		g_eGameState = S_LEADERBOARD;
	}
	// preventing the arrows from sending the player to an unknown spot when coming back to screen
	setArrowOption = false;
	setArrowSelect = false;
	setArrowLeaderboard = false;
}

void gameplay()		// gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter(); // moves the character, collision detection, physics, etc sound can be played here too.
	AiMovement();
	Cut();
	pointSystem(); // Points added
	bonusKey(); // checks for bonus key
	treeAxeCheck(); // checks for axe
	doorSwitch(); // door switch to open doors
	spikes_on();
}

void doorSwitch(){
	if ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X]) == '&') // checks if player is on the switch
	{
		for (int Rows = 0; Rows < 24; Rows++)
		{
			for (int Columns = 0; Columns < 55; Columns++)
			{
				if ((Map[LevelSelection][Rows][Columns]) == '#'){
					Map[LevelSelection][Rows][Columns] = (char)158; // tries to find the locked door, then changes every instance of it into the exit
				}
			}
		}
	}
}

void spikes_on()
{
	if ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X]) == 'X')
	{
		g_eGameState = S_GAMEOVER;
		PlaySound(NULL, 0, 0);
	}
}

void pointSystem()
// checks to see if player is on point pick up spots, then turns it into nothing and adds total points
{
	if ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X]) == '1')
	{
		Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
		g_dTotalPoints += 100;
	}
	if ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X]) == '2')
	{
		Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
		g_dTotalPoints += 200;
	}
	if ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X]) == '5')
	{
		Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
		g_dTotalPoints += 500;
	}
	if ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X]) == 'A')
	{
		Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
		g_dTotalPoints += 1000;
	}
	if ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X]) == '.')
	{
		Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
		g_dTotalPoints += 10;
	}
}

void bonusKey(){
	// checks to see if player is on the point of the key, then sets bool to true and clears it.
	if ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X]) == '+')
	{
		Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
		g_dTotalPoints += 50;
		bonusTimeKey = true;
	}
}

void treeAxeCheck(){
	// checks to see if player is on the point of the axe, then sets bool to true and clears it.
	if ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X]) == (char)210)
	{
		Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
		treeAxe = true;
		AxeUses += 3;
	}
}
	
void processUserInput()
{
    // pauses the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE]){
		g_eGameState = S_PAUSE;
		PlaySound(NULL, 0, 0);
	}
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x00);
}

void titleText() {
	// to print out text files on the splash screen
	COORD c = g_Console.getConsoleSize();
	c.Y = 4;
	c.X = 7;

	string sym;
	ifstream myfile("GameTitle.txt"); // calls .txt file to print

	if (myfile.is_open()){
		while (getline(myfile, sym)) {
			g_Console.writeToBuffer(c, sym, 0x0B);
			c.Y++;
		}
		myfile.close();
	} // creates a loop to read the file line by line, then closes it.

	string art;
	ifstream temple("templeArt.txt"); // ascii art .txt file

	if (temple.is_open()){
		while (getline(temple, art)) {
			g_Console.writeToBuffer(c.X - 2, c.Y + 3, art, 0x0B);
			c.Y++;
		}
		temple.close();
	} // creates loop to print out the art line by line, then closes it.
}

void renderSplashScreen()  // renders the splash screen
{
	titleText();
    COORD c = g_Console.getConsoleSize();
    c.Y = c.Y / 2;
    c.X = 50;
    g_Console.writeToBuffer(c, "Start Game", 0x07);
    c.Y += 1;
	c.X = 50;
	g_Console.writeToBuffer(c, "Options", 0x07);
	c.Y += 1;
	c.X = 50;
	g_Console.writeToBuffer(c, "Instructions", 0x07);
	c.Y += 1;
	c.X = 50;
	g_Console.writeToBuffer(c, "Leaderboard", 0x07);
	c.Y += 1;
	c.X = 50;
	g_Console.writeToBuffer(c, "Quit Game", 0x07);

	renderArrow();
	moveArrow();
	setArrowOption = false;
	setArrowSelect = false;
	setArrowLeaderboard = false;
	// renders the arrow for the splash and level select screens

	if ((g_eGameState == S_SPLASHSCREEN) && (g_abKeyPressed[K_ENTER]) && (arrow.Y == 19)){
		g_bQuitGame = true; // quits game if arrow is on "Quit Game"
	}
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
	if ((LevelSelection == 4) || (LevelSelection == 9) || (LevelSelection == 10))
	{
		AiRender();			// renders AI into the buffer
	}
}



void renderStory(){
	switch (LevelSelection)
	{
	case 1: // level one
		StoryOne();
		break;

	case 2: // level two
		StoryTwo();
		break;

	case 3: // level three
		StoryThree();
		break;

	case 4: // level four
		StoryFour();
		break;

	case 5: // level five
		StoryFive();
		break;

	case 6: // level six
		StorySix();
		break;

	case 7: // level seven
		StorySeven();
		break;

	case 8: // level eight
		StoryEight();
		break;

	case 9: // level nine
		StoryNine();
		break;

	case 10: // level ten
		StoryTen();
		break;

	case 11: // level ten
		StoryEnd();
		break;
	}

	if (LevelSelection < 11){
		COORD c;
		c.X = 25;
		c.Y = 25;

		ostringstream ss;
		ss.str("");
		ss << "Press SPACE to move on with the game...";
		if (LevelSelection >= 1 || LevelSelection <= 4 || LevelSelection == 11){
			g_Console.writeToBuffer(c, ss.str(), 0x2F);
		}

		if (LevelSelection >= 5 || LevelSelection <= 10){
			g_Console.writeToBuffer(c, ss.str(), 0x1F);
		}

		if (g_abKeyPressed[K_SPACE]){
			charSpawn();
			AiSpawn();
			g_eGameState = S_GAME;
		}

		if (g_abKeyPressed[K_ESCAPE]){
			PlaySound(NULL, 0, 0);
			g_eGameState = S_PAUSE;
		}
	}
}

void renderMap()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

	COORD c;
	c.X = 0;
	c.Y = 0;
	// prints the maps, all called in LevelXXX.cpp files
	for (int rows = 0; rows < 25; rows++)
	{
		c.Y = rows;
		for (int columns = 0; columns < 55; columns++)
		{
			if (Map[LevelSelection][rows][columns] == 'i')
			{
				Map[LevelSelection][rows][columns] = ' '; // turns all 'i's in the .txt files to blank spaces to walk on.
			}
			if (Map[LevelSelection][rows][columns] == '.')
			{
				Map[LevelSelection][rows][columns] = '.'; // turns all 'i's in the .txt files to blank spaces to walk on.
			}

			if (Map[LevelSelection][rows][columns] == 'L')
			{
				Map[LevelSelection][rows][columns] = (char)158; // turns all 'L's in the .txt files to level clear special character.
			}

			if (Map[LevelSelection][rows][columns] == 'x')
			{
				Map[LevelSelection][rows][columns] = (char)233; // turns all 'x's in the .txt files to boulders to push around.
			}

			if (Map[LevelSelection][rows][columns] == 'm')
			{
				Map[LevelSelection][rows][columns] = (char)210; // turns all 'm's in the .txt files to axe special character.
			}

			c.X = columns;
			if (LevelSelection == 9 || LevelSelection == 10){
				g_Console.writeToBuffer(c, Map[LevelSelection][rows][columns], 0x00);
				
			}

			else {
				g_Console.writeToBuffer(c, Map[LevelSelection][rows][columns], 0x0a);
			}

			if (Map[LevelSelection][rows][columns] == '1' || Map[LevelSelection][rows][columns] == '2' || Map[LevelSelection][rows][columns] == '5' || Map[LevelSelection][rows][columns] == 'A' || Map[LevelSelection][rows][columns] == '.')
			{
				g_Console.writeToBuffer(c, Map[LevelSelection][rows][columns], 0x0E); // turns all point symbols to a different colour
			}

			if (Map[LevelSelection][rows][columns] == 'r')
			{
				g_Console.writeToBuffer(c, Map[LevelSelection][rows][columns], 0x0B); // turns the river to blue
			}

			if (Map[LevelSelection][rows][columns] == '+' || Map[LevelSelection][rows][columns] == (char)158 || Map[LevelSelection][rows][columns] == (char)210 || Map[LevelSelection][rows][columns] == 'b')
			{
				g_Console.writeToBuffer(c, Map[LevelSelection][rows][columns], 0x07); // turns bonus key, exit and axe to a different colour
			}

			if (Map[LevelSelection][rows][columns] == 'O' || Map[LevelSelection][rows][columns] == 'o' || Map[LevelSelection][rows][columns] == (char)233)
			{
				g_Console.writeToBuffer(c, Map[LevelSelection][rows][columns], 0x08); // turns bonus key, exit and axe to a different colour
			}

			if (Map[LevelSelection][rows][columns] == 'B')
			{
				g_Console.writeToBuffer(c, Map[LevelSelection][rows][columns], 0x02); // turns bonus door into another colour
			}

			if (Map[LevelSelection][rows][columns] == 'X')
			{
				g_Console.writeToBuffer(c, Map[LevelSelection][rows][columns], 0x04); // turns spikes into another colour
			}

			if (Map[LevelSelection][rows][columns] == 'T')
			{
				g_Console.writeToBuffer(c, Map[LevelSelection][rows][columns], 0x0A); // trees for level 10
			}

			if (Map[LevelSelection][rows][columns] == '#' || Map[LevelSelection][rows][columns] == '&')
			{
				g_Console.writeToBuffer(c, Map[LevelSelection][rows][columns], 0x05); // turns switch and door into another colour
			}
			
		 
		}
	}
	LevelClear(); // calls the function to check if player has arrived at the level clear character
	setArrowOption = false;
	setArrowSelect = false; 
	setArrowLeaderboard = false; // resets arrows to make sure player doesn't end up at strange places on main screen
}

void renderCharacter()
{
    // Draw the location of the character
	WORD charColor = 0x06;
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)232, charColor);
}

void renderArrow()
{
	// this renders the arrow that appears on the splashscreen
	if (setArrowMenu == false && g_eGameState == S_SPLASHSCREEN)
	{
		arrow.X = 44;
		arrow.Y = 15;
		g_Console.writeToBuffer(arrow, ">");
		setArrowMenu = true;
	}

	// this renders the arrow that appears on the select screen
	else if (setArrowSelect == false && g_eGameState == S_SELECT)
	{
		arrow.X = 33;
		arrow.Y = 16;
		g_Console.writeToBuffer(arrow, ">");
		setArrowSelect = true;
	}
	// this renders the arrow that appears on the option screen
	else if (setArrowOption == false && g_eGameState == S_OPTION)
	{
		arrow.X = 25;
		arrow.Y = 14;
		g_Console.writeToBuffer(arrow, ">");
		setArrowOption = true;
	}
	// Draws the arrow
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
    ss << (int) g_dTimer << " secs";
    c.X = 2;
    c.Y = 1;
    g_Console.writeToBuffer(c, ss.str());

	// displays the points
	ss.str("");
	ss << "Points: " << g_dTotalPoints;
	c.X = 20;
	c.Y = 1;
	g_Console.writeToBuffer(c, ss.str());

	// displays level
	if (LevelSelection < 11){
	ss.str("");
	ss << "Level: " << LevelSelection;
	c.X = 45;
	c.Y = 1;
	g_Console.writeToBuffer(c, ss.str());
	}

	else if (LevelSelection >= 11 && LevelSelection <= 15) {
		ss.str("");
		ss << "Level: BONUS";
		c.X = 45;
		c.Y = 1;
		g_Console.writeToBuffer(c, ss.str());
	}

	if (bonusTimeKey == true){
		c.X = 5;
		c.Y = 25;
		ss.str("");
		ss << "Bonus Key   1x use"; // tells player that they have the bonus key
		g_Console.writeToBuffer(c, ss.str());
		
		for (int Rows = 0; Rows < 24; Rows++)
		{
			for (int Columns = 0; Columns < 55; Columns++)
			{
				if ((Map[LevelSelection][Rows][Columns]) == 'b'){
					Map[LevelSelection][Rows][Columns] = 'B'; // changes the capitalisation of the bonus room door when key is true
				}
			}
		}
	}

	if (treeAxe == true){
		c.X = 30;
		c.Y = 25;
		ss.str("");
		ss << "Tree Axe   " << AxeUses << "x uses"; // shows the amount of remaining uses for the axe
		g_Console.writeToBuffer(c, ss.str());
	}
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void pauseControls(){
	// controls the player can use on the pause screen
	if (g_abKeyPressed[K_ENTER]){
		g_eGameState = S_GAME;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Game.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
		// enter brings player back to game
	}

	if (g_abKeyPressed[K_SPACE]){
		// space resets everything, then brings player back to the splash screen
		g_dTimer = 0.0;
		g_dTotalPoints = 0;
		SavedPoints = 0;
		charSpawn();
		AiSpawn();
		treeAxe = false;
		AxeUses = 0;
		bonusTimeKey = false;
		LoadMaps();
		g_eGameState = S_SPLASHSCREEN;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Menu.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}
	if (g_abKeyPressed[K_R])
	{
		// r resets everything but the timer, then restarts the level.
		g_dTotalPoints = 0;
		treeAxe = false;
		bonusTimeKey = false;
		g_eGameState = S_RESTART;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Game.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}
}

void renderPauseScreen()
{
	// calls coordinate for pause screen
		COORD c = g_Console.getConsoleSize();
		c.Y = 7;
		c.X = 15;

		// reads pausescreen.txt and writes it line by line
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

void moveArrow()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// checks the keys and moves accordingly to the key pressed and position of arrow
	if (g_abKeyPressed[K_UP] && arrow.Y > 15 && g_eGameState == S_SPLASHSCREEN)
	{
		arrow.Y--;
		bSomethingHappened = true;
		g_Console.writeToBuffer(arrow, ">");
	}
	if (g_abKeyPressed[K_DOWN] && arrow.Y < 19 && g_eGameState == S_SPLASHSCREEN)
	{
		arrow.Y++;
		bSomethingHappened = true;
		g_Console.writeToBuffer(arrow, ">");
	}

	if (g_abKeyPressed[K_UP] && arrow.Y > 16 && g_eGameState == S_SELECT)
	{
		arrow.Y--;
		bSomethingHappened = true;
		g_Console.writeToBuffer(arrow, ">");

	}
	if (g_abKeyPressed[K_DOWN] && arrow.Y < 26 && g_eGameState == S_SELECT)
	{
		arrow.Y++;
		bSomethingHappened = true;
		g_Console.writeToBuffer(arrow, ">");
	}
	if (g_abKeyPressed[K_UP] && arrow.Y > 14 && g_eGameState == S_OPTION)//reset leaderboard
	{
		arrow.Y--;
		bSomethingHappened = true;
		g_Console.writeToBuffer(arrow, ">");

	}
	if (g_abKeyPressed[K_DOWN] && arrow.Y < 15 && g_eGameState == S_OPTION)//credits
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
	// these conditions check if player has to be moved to another map
	if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == char(158)) // checks if player has reached the point to clear level
	{
		LevelSelection += 1;
		SavedPoints += g_dTotalPoints;
		g_eGameState = S_STORY;
		AiSpawn();
		charSpawn();
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'b') // checks if player is in bonus room and decided to leave
	{
		switch (LevelSelection)
		{
		case 11:
			LevelSelection = 2;
			break;
		case 12:
			LevelSelection = 4;
			break;
		case 13:
			LevelSelection = 6;
			break;
		case 14:
			LevelSelection = 8;
			break;
		case 15:
			LevelSelection = 10;
			break;
		}
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'B' && bonusTimeKey == true){ // checks if player is not in bonus room and has reached the bonus room door
		switch (LevelSelection)
		{
		case 2:
			LevelSelection = 11;
			bonusTimeKey = false;
			break;
		case 4:
			LevelSelection = 12;
			bonusTimeKey = false;
			break;
		case 6:
			LevelSelection = 13;
			bonusTimeKey = false;
			break;
		case 8:
			LevelSelection = 14;
			bonusTimeKey = false;
			break;
		case 10:
			LevelSelection = 15;
			bonusTimeKey = false;
			break;
		}
	}
}

void SelectLevel()
{
	// checks for enter key pressed and position of arrow, then brings player to the chosen level and starts the game
	if ((g_abKeyPressed[K_ENTER]) && (arrow.Y == 16) && (g_eGameState == S_SELECT) && (g_dElapsedTime >= g_dMenuToSelectTimer))
	{
		LevelSelection = 1;
		g_eGameState = S_STORY;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Game.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}

	if ((g_abKeyPressed[K_ENTER]) && (arrow.Y == 17) && (g_eGameState == S_SELECT) && (g_dElapsedTime >= g_dMenuToSelectTimer))
	{
		LevelSelection = 2;
		g_eGameState = S_STORY;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Game.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}

	if ((g_abKeyPressed[K_ENTER]) && (arrow.Y == 18) && (g_eGameState == S_SELECT) && (g_dElapsedTime >= g_dMenuToSelectTimer))
	{
		LevelSelection = 3;
		g_eGameState = S_STORY;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Game.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}	
	
	if ((g_abKeyPressed[K_ENTER]) && (arrow.Y == 19) && (g_eGameState == S_SELECT) && (g_dElapsedTime >= g_dMenuToSelectTimer))
	{
		LevelSelection = 4;
		g_eGameState = S_STORY;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Game.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}

	if ((g_abKeyPressed[K_ENTER]) && (arrow.Y == 20) && (g_eGameState == S_SELECT) && (g_dElapsedTime >= g_dMenuToSelectTimer))
	{
		LevelSelection = 5;
		g_eGameState = S_STORY;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Game.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}

	if ((g_abKeyPressed[K_ENTER]) && (arrow.Y == 21) && (g_eGameState == S_SELECT) && (g_dElapsedTime >= g_dMenuToSelectTimer))
	{
		LevelSelection = 6;
		g_eGameState = S_STORY;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Game.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}

	if ((g_abKeyPressed[K_ENTER]) && (arrow.Y == 22) && (g_eGameState == S_SELECT) && (g_dElapsedTime >= g_dMenuToSelectTimer))
	{
		LevelSelection = 7;
		g_eGameState = S_STORY;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Game.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}

	if ((g_abKeyPressed[K_ENTER]) && (arrow.Y == 23) && (g_eGameState == S_SELECT) && (g_dElapsedTime >= g_dMenuToSelectTimer))
	{
		LevelSelection = 8;
		g_eGameState = S_STORY;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Game.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}

	if ((g_abKeyPressed[K_ENTER]) && (arrow.Y == 24) && (g_eGameState == S_SELECT) && (g_dElapsedTime >= g_dMenuToSelectTimer))
	{
		LevelSelection = 9;
		g_eGameState = S_STORY;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Game.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}
	if ((g_abKeyPressed[K_ENTER]) && (arrow.Y == 25) && (g_eGameState == S_SELECT) && (g_dElapsedTime >= g_dMenuToSelectTimer))
	{
		LevelSelection = 10;
		g_eGameState = S_STORY;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Game.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}
	if ((g_abKeyPressed[K_ENTER]) && (arrow.Y == 26) && (g_eGameState == S_SELECT) && (g_dElapsedTime >= g_dMenuToSelectTimer))
	{
		setArrowMenu = false;
		g_dMenuToSelectTimer = g_dElapsedTime + 0.25;
		g_eGameState = S_SPLASHSCREEN;
	}
	// if player hits escape on select screen, game will close
	if ((g_eGameState == S_SELECT) && (g_abKeyPressed[K_ESCAPE]))
	{
		g_bQuitGame = true;
	}
	// sets arrow to false again to make sure it doesn't spawn at weird places after
	setArrowMenu = false;
	setArrowOption = false;
	setArrowLeaderboard = false;
}

void LoadMaps()
{
	// calls the map functions
	LevelOne();
	LevelTwo();
	LevelThree();
	LevelFour();
	LevelFive();
	LevelSix();
	LevelSeven();
	LevelEight();
	LevelNine();
	LevelTen();
	BonusRoom();
}

void renderInstructions()
{
	COORD c = g_Console.getConsoleSize();
	c.Y = 0;
	c.X = 0;

	// reads and writes instructions.txt for the instructions screen
	string sym;
	ifstream myfile("instructions.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x07);
			c.Y++;
		}
		myfile.close();
	}
	// goes back to splash screen if escape is pressed
	if (g_abKeyPressed[K_ESCAPE] && (g_eGameState == S_INSTRUCTIONS)){
		g_eGameState = S_SPLASHSCREEN;
	}
	setArrowMenu = false;
}

void renderCredits()
{
	COORD c = g_Console.getConsoleSize();
	c.Y = 0;
	c.X = 0;

	// reads and writes credits.txt for the leaderboard screen
	string sym;
	ifstream myfile("credits.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x07);
			c.Y++;
		}
		myfile.close();
	}

	// goes back to splash screen if escape is pressed
	if (g_abKeyPressed[K_ESCAPE] && (g_eGameState == S_CREDITS)){
		g_eGameState = S_SPLASHSCREEN;
	}
}

void renderOption()
{
	COORD c = g_Console.getConsoleSize();
	c.Y = 0;
	c.X = 0;

	// reads and writes options.txt for the options screen
	string sym;
	ifstream myfile("options.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x07);
			c.Y++;
		}
		myfile.close();
	}
	//reset the leaderboard
	if (g_abKeyPressed[K_ENTER] && (g_eGameState == S_OPTION) && arrow.Y == 14)
	{
		std::ofstream ofs;
		ofs.open("Leaderboard.csv", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		
	}
	// goes back to splash screen if escape is pressed
	if (g_abKeyPressed[K_ESCAPE] && (g_eGameState == S_OPTION)){
		g_eGameState = S_SPLASHSCREEN;
	}
	// checks for arrow location, then takes player to credit screen
	if (g_abKeyPressed[K_ENTER] && (g_eGameState == S_OPTION) && arrow.Y == 15 && g_dElapsedTime>=g_dMenuToSelectTimer){
		g_eGameState = S_CREDITS;
	}
	// turns all the other arrow choices false so it will work to only reach the range in options
	setArrowSelect = false;
	setArrowMenu = false;
	setArrowLeaderboard = false;
	renderArrow();
	moveArrow();
}

void rendergameover()
{
	COORD c = g_Console.getConsoleSize();
	c.Y = 0;
	c.X = 0;

	// reads and writes options.txt for the options screen
	string sym;
	ifstream myfile("gameover.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x07);
			c.Y++;
		}
		myfile.close();
	}

	// goes back to splash screen if escape is pressed
	if (g_abKeyPressed[K_ESCAPE] && (g_eGameState == S_GAMEOVER)){
		g_dTotalPoints = 0;
		g_dTimer = 0.0;
		treeAxe = false;
		AxeUses = 0;
		bonusTimeKey = false;
		g_eGameState = S_SPLASHSCREEN;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Menu.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}
	// restarts the level
	if (g_abKeyPressed[K_R] && (g_eGameState == S_GAMEOVER))
	{
		g_dTotalPoints = 0;
		treeAxe = false;
		AxeUses = 0;
		bonusTimeKey = false;
		restart();
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Game.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}
}
void rendergameover2()
{
	COORD c = g_Console.getConsoleSize();
	c.Y = 0;
	c.X = 0;

	// reads and writes options.txt for the options screen
	string sym;
	ifstream myfile("gameover2.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x07);
			c.Y++;
		}
		myfile.close();
	}

	// goes back to splash screen if escape is pressed
	if (g_abKeyPressed[K_ESCAPE] && (g_eGameState == S_GAMEOVER2)){
		g_dTotalPoints = 0;
		g_dTimer = 0.0;
		treeAxe = false;
		AxeUses = 0;
		bonusTimeKey = false;
		g_eGameState = S_SPLASHSCREEN;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Menu.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}
	// checks for arrow location, then takes player to credit screen
	if (g_abKeyPressed[K_R] && (g_eGameState == S_GAMEOVER2))
	{
		restart();
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("Game.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}
}
void Cut()
{
	// the function to be able to cut trees down.
	bool bSomethingHappened = false;
	if ((g_abKeyPressed[K_C]) && (g_abKeyPressed[K_A] || g_abKeyPressed[K_LEFT]) && ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1]) == 'T') && (treeAxe == true)) 
	{
			Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X-1] = ' ';
			g_dTotalPoints += 70;
			AxeUses--;
			bSomethingHappened = true;
	}
	// requiures player to press two buttons near a tree in order to cut it. player gains 70 points for cutting it.

	if ((g_abKeyPressed[K_C]) && (g_abKeyPressed[K_D] || g_abKeyPressed[K_RIGHT]) && ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1]) == 'T') && (treeAxe == true))
	{
			Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X +1 ] = ' ';
			g_dTotalPoints += 70;
			AxeUses--;
			bSomethingHappened = true;
	}

	if ((g_abKeyPressed[K_C]) && (g_abKeyPressed[K_W] || g_abKeyPressed[K_UP]) && ((Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X]) == 'T') && (treeAxe == true))
	{
			Map[LevelSelection][g_sChar.m_cLocation.Y-1][g_sChar.m_cLocation.X] = ' ';
			g_dTotalPoints += 70;
			AxeUses--;
			bSomethingHappened = true;
	}

	if ((g_abKeyPressed[K_C]) && (g_abKeyPressed[K_S] || g_abKeyPressed[K_DOWN]) && ((Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X]) == 'T') && (treeAxe == true))
	{
		Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] = ' ';
		g_dTotalPoints += 70;
		AxeUses--;
		bSomethingHappened = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}

	// if tree runs out of uses, the text will disappear.
	if (AxeUses == 0)
	{
		treeAxe = false;
	}
}
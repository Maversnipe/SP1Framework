#ifndef _GAME_H
#define _GAME_H

#include <Windows.h>
#include "Framework\timer.h"
#include <string>
#include "Levels.h"

using namespace std;

#define VK_A 0x41
#define VK_W 0x57
#define VK_S 0x53
#define VK_D 0x44
#define VK_ONE 0x31
#define VK_TWO 0x32
#define VK_R 0x52
#define VK_C 0x43
#define VK_B 0x42
extern CStopWatch g_swTimer;
extern bool g_bQuitGame;
extern Console g_Console;


// Enumeration to store the control keys that your game will have
enum EKEYS
{
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_ESCAPE,
	K_SPACE,
	K_W,
	K_A,
	K_S,
	K_D,
	K_ENTER,
	K_ONE,
	K_TWO,
	K_R,
	K_C,
	K_B, 
	K_COUNT // this is the last index code for checking the key.
};

// Enumeration for the different screen states
enum EGAMESTATES
{
	S_SPLASHSCREEN,
	S_PAUSE,
	S_GAME,
	S_SELECT,
	S_INSTRUCTIONS,
	S_RESTART,
	S_COUNT,
	S_LEADERBOARD,
	S_OPTION,
	S_CREDITS,

};


// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};

struct Enemy
{
	COORD m_cLocation;
};


void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void renderPauseScreen();
void renderArrow();
void moveArrow();
void paused();
void pauseScreenChoices();
void LoadMaps();
void pointSystem();
void LevelClear();
void SelectLevel();
void bonusKey();
void Cut();
void treeAxeCheck();
void renderInstructions();
void restart();
void renderleaderboard();
void renderOption();
void renderCredits();
#endif // _GAME_H
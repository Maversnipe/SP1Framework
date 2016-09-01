#ifndef _GAME_H
#define _GAME_H

#include <Windows.h>
#include "Framework\timer.h"
#include <string>
#include <fstream>
#include <sstream>
#include "Levels.h"
#include "Story.h"

using namespace std;

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A
#define VK_BS 0x08


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
	K_ENTER,
	K_BACKSPACE,
	K_A,
	K_B,
	K_C,
	K_D,
	K_E,
	K_F,
	K_G,
	K_H,
	K_I,
	K_J,
	K_K,
	K_L,
	K_M,
	K_N,
	K_O,
	K_P,
	K_Q,
	K_R,
	K_S,
	K_T,
	K_U,
	K_V,
	K_W,
	K_X,
	K_Y,
	K_Z,
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
	S_LEADERBOARD,
	S_OPTION,
	S_CREDITS,
	S_STORY,
	S_GAMEOVER,
	S_GAMEOVER2,
	S_INPUT_NAME,
	S_COUNT
};



struct SGameChar
{
	COORD m_cLocation;
	int points = 0;
	double time = 0;
	string Name = "";
	bool  m_bActive;
}
;

struct EnemyChar
{
	COORD m_cLocation;
};

struct Leaderboard
{
	string Name = "";
	int Score = 0;
	double Time = 0.0;
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
void renderPauseScreen();	// renders the pause screen
void renderArrow();			// renders the arrow that shows up on selection screens
void moveArrow();			// moves the arrow that renders on selection screen
void paused();				// function when the game is paused
void pauseScreenChoices();	// registers keys when game is paused
void LoadMaps();			// writes the maps
void pointSystem();			// point system for the game
void LevelClear();			// logic when level is cleared
void SelectLevel();			// screen to select level
void bonusKey();			// checks for bonus key
void Cut();					// mechanic to cut down trees
void treeAxeCheck();		// checks for axe
void renderInstructions();	// renders the game instructions
void charSpawn();			// spawn point for character
void restart();				// to restart the game
void renderleaderboard();	// renders the leaderboard screen
void renderOption();		// renders option screen
void renderCredits();		// renders credit screen
void light();				// light mechanic
void renderStory();			// renders story
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
void charSpawn();
void restart();
void renderLeaderboard();
void renderOption();
void renderCredits();
void light();
void rendergameover();
void rendergameover2();
void Highscore();
void FastTime();
void LeaderboardMenu();
void AiMovement();
void AiRender();
void AiSpawn();
void CharName();
void RenderInput();
#endif // _GAME_H
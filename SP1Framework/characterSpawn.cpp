#include "game.h"
extern int LevelSelection;
extern struct SGameChar;
extern SGameChar g_sChar;

void charSpawn()
{
	switch (LevelSelection)
	{
	case 1:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 22;
		break;
	case 2:
		g_sChar.m_cLocation.X = 6;
		g_sChar.m_cLocation.Y = 22;
		break;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:;
	}
}
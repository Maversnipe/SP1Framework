#include "game.h"
extern SGameChar g_sChar;
extern int LevelSelection;

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
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 5;
		break;
	case 4:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 21;
		break;
	case 5:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 5;
		break;
	case 6:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 21;
		break;
	case 7:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 21;
		break;
	case 8:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 21;
		break;
	case 9:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 21;
		break;
	case 10:
		g_sChar.m_cLocation.X = 5;
		g_sChar.m_cLocation.Y = 21;
		break;;
	}
}
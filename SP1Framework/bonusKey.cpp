#include <string>
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <iostream>
extern Console g_Console;

void bonusKey(){
	if ((Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X]) == '1')
	{
		Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] = ' ';
		g_dTotalPoints += 100;
	}
}
#include <iostream> 
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "game.h"
#include "Framework\console.h"

using namespace std;

void titleText(Console g_Console) {
	COORD c = g_Console.getConsoleSize();
	c.Y = 0;
	c.X = c.X / 2;

	string sym;
	ifstream myfile("crystemple.txt");

	if (myfile.is_open()){
		while (getline(myfile, sym)) {
			g_Console.writeToBuffer(c, sym, 0x0F);
			c.Y++;
		}
	}

	myfile.close();
}
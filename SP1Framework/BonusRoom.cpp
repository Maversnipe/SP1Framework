#include "BonusRoom.h"
extern Console g_Console;

void BonusRoom(){
	COORD c;
	c.Y = 4;
	c.X = 2;
	extern char Map[22][52];
	ifstream File("bonusroom.txt");

	if (File.is_open())
	{
		for (int Rows = 0; Rows < 21; Rows++){
			for (int Columns = 0; Columns < 52; Columns++){
				File >> Map[Rows][Columns];
			}
		}

		File.close();
		for (int Rows = 0; Rows < 21; Rows++){

			c.Y = Rows + 3;

			for (int Columns = 0; Columns < 52; Columns++){
				if (Map[Rows][Columns] == 'i'){
					Map[Rows][Columns] = ' ';
				}
				
				c.X = Columns + 3;
				
				g_Console.writeToBuffer(c, Map[Rows][Columns], 0x0A);
			}
		}
	}
}
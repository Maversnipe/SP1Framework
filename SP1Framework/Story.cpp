#include "Story.h"
extern Console g_Console;

void StoryOne()
{
	g_Console.clearBuffer(0x27);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("Stories/StoryOne.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x27);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryTwo()
{
	g_Console.clearBuffer(0x27);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("Stories/StoryTwo.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x27);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryThree()
{
	g_Console.clearBuffer(0x27);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("Stories/StoryThree.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x27);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryFour()
{
	g_Console.clearBuffer(0x27);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("Stories/StoryFour.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x27);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryFive()
{
	g_Console.clearBuffer(0x17);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("Stories/StoryFive.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x17);
			c.Y++;
		}
		myfile.close();
	}
}

void StorySix()
{
	g_Console.clearBuffer(0x17);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("Stories/StorySix.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x17);
			c.Y++;
		}
		myfile.close();
	}
}

void StorySeven()
{
	g_Console.clearBuffer(0x17);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("Stories/StorySeven.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x17);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryEight()
{
	g_Console.clearBuffer(0x17);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("Stories/StoryEight.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x17);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryNine()
{
	g_Console.clearBuffer(0x17);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("Stories/StoryNine.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x17);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryTen()
{
	g_Console.clearBuffer(0x17);
	COORD c;
	c.Y = 4;
	c.X = 4;
	string sym;
	ifstream myfile("Stories/StoryTen.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x17);
			c.Y++;
		}
		myfile.close();
	}
}

void StoryEnd()
{
	g_Console.clearBuffer(0x27);
	COORD c;
	c.Y = 4;
	c.X = 4;

	string sym;
	ifstream myfile("Stories/StoryLast.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, sym))
		{
			g_Console.writeToBuffer(c, sym, 0x27);
			c.Y++;
		}
		myfile.close();
	}
}
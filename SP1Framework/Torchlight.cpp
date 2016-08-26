#include "game.h"
extern char Map[20][100][100];
extern struct SGameChar g_sChar;
extern bool g_abKeyPressed[K_COUNT];
extern EGAMESTATES g_eGameState;
extern int LevelSelection;
void light()
{
	COORD c;
	c.X = g_sChar.m_cLocation.X;
	c.Y = g_sChar.m_cLocation.Y;
	if ((g_abKeyPressed[K_B]) && ((g_eGameState != S_GAMEOVER) || (g_eGameState != S_GAMEOVER2)))
	{
		//down is +y , up is -y, left is -x , left is +x,

		if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == ' ')
		{
			
			g_Console.writeToBuffer(c.X+1,c.Y, " ", 0x7B);
		}


		if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == ' ')
		{
			
			g_Console.writeToBuffer(c.X+2,c.Y, " ", 0x7B);
		}

		if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == ' ')
		{
			
			g_Console.writeToBuffer(c.X-1,c.Y, " ", 0x7B);
		}

		if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == ' ')
		{
			
			g_Console.writeToBuffer(c.X-2,c.Y, " ", 0x7B);
		}

		if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == ' ')
		{
			
			g_Console.writeToBuffer(c.X,c.Y +1, " ", 0x7B);
		}

		if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == ' ')
		{
			
			g_Console.writeToBuffer(c.X,c.Y+2, " ", 0x7B);
		}

		if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X ] == ' ')
		{
			
			g_Console.writeToBuffer(c.X,c.Y-1, " ", 0x7B);
		}

		if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X ] == ' ')
		{
			
			g_Console.writeToBuffer(c.X,c.Y-2, " ", 0x7B);
		}

		//square

		//y+1

		if (Map[LevelSelection][g_sChar.m_cLocation.Y+1][g_sChar.m_cLocation.X -1] == ' ')
		{

			g_Console.writeToBuffer(c.X-1, c.Y+1, " ", 0x7B);
		}

		if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X - 2] == ' ')
		{

			g_Console.writeToBuffer(c.X -2 , c.Y + 1, " ", 0x7B);
		}

		if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X + 1] == ' ')
		{

			g_Console.writeToBuffer(c.X + 1, c.Y + 1, " ", 0x7B);
		}
		if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X + 2] == ' ')
		{

			g_Console.writeToBuffer(c.X + 2, c.Y + 1, " ", 0x7B);
		}
		//y-1
		if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X -1] == ' ')
		{

			g_Console.writeToBuffer(c.X - 1, c.Y - 1, " ", 0x7B);
		}

		if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X - 2] == ' ')
		{

			g_Console.writeToBuffer(c.X - 2, c.Y - 1, " ", 0x7B);
		}

		if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X + 1] == ' ')
		{

			g_Console.writeToBuffer(c.X + 1, c.Y - 1, " ", 0x7B);
		}
   
		if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X + 2] == ' ')
		{

			g_Console.writeToBuffer(c.X + 2, c.Y - 1, " ", 0x7B);
		}

		// y +2
		if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X + 2] == ' ')
		{

			g_Console.writeToBuffer(c.X + 2, c.Y + 2, " ", 0x7B);
		}
		if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X + 1] == ' ')
		{

			g_Console.writeToBuffer(c.X +1, c.Y + 2, " ", 0x7B);
		}
		if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X - 2] == ' ')
		{

			g_Console.writeToBuffer(c.X - 2, c.Y + 2, " ", 0x7B);
		}
		if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X - 1] == ' ')
		{

			g_Console.writeToBuffer(c.X - 1, c.Y + 2, " ", 0x7B);
		}

		//y-2

		if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X -2] == ' ')
		{

			g_Console.writeToBuffer(c.X - 2, c.Y -2, " ", 0x7B);
		}


		if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X - 1] == ' ')
		{

			g_Console.writeToBuffer(c.X - 1, c.Y - 2, " ", 0x7B);

		}
		if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X + 1] == ' ')
		{

			g_Console.writeToBuffer(c.X+1, c.Y - 2, " ", 0x7B);

		}
		if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X + 2] == ' ')
		{

			g_Console.writeToBuffer(c.X + 2, c.Y - 2, " ", 0x7B);

		}
	//	//======================================Check if light is equal =================================================


		if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == '=')
		{
			
			g_Console.writeToBuffer(c.X+1,c.Y, "=", 0x7B);
		}

		if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == '=')
		{
			
			g_Console.writeToBuffer(c.X+2,c.Y, "=", 0x7B);
		}

		if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == '=')
		{
			
			g_Console.writeToBuffer(c.X-1,c.Y, "=", 0x7B);
		}

		if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == '=')
		{
			
			g_Console.writeToBuffer(c.X-2,c.Y, "=", 0x7B);
		}

		if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == '=')
		{
		
		g_Console.writeToBuffer(c.X,c.Y+1 ,"=", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == '=')
	{
		
		g_Console.writeToBuffer(c.X,c.Y+2, "=", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == '='){
		
		g_Console.writeToBuffer(c.X,c.Y-1, "=", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == '=')
	{
		
		g_Console.writeToBuffer(c.X,c.Y-2 ,"=", 0x7B);
	}

	//square

	//y+1

	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X - 1] == '=')
	{

		g_Console.writeToBuffer(c.X - 1, c.Y + 1, "=", 0x7B);
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X - 2] == '=')
	{

		g_Console.writeToBuffer(c.X - 2, c.Y + 1, "=", 0x7B);
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X + 1] == '=')
	{

		g_Console.writeToBuffer(c.X + 1, c.Y + 1, "=", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X + 2] == '=')
	{

		g_Console.writeToBuffer(c.X + 2, c.Y + 1, "=", 0x7B);
	}
	//y-1
	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X - 1] == '=')
	{

		g_Console.writeToBuffer(c.X - 1, c.Y - 1, "=", 0x7B);
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X - 2] == '=')
	{

		g_Console.writeToBuffer(c.X - 2, c.Y - 1, "=", 0x7B);
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X + 1] == '=')
	{

		g_Console.writeToBuffer(c.X + 1, c.Y - 1, "=", 0x7B);
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X + 2] == '=')
	{

		g_Console.writeToBuffer(c.X + 2, c.Y - 1, "=", 0x7B);
	}

	// y +2
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X + 2] == '=')
	{

		g_Console.writeToBuffer(c.X + 2, c.Y + 2, "=", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X + 1] == '=')
	{

		g_Console.writeToBuffer(c.X + 1, c.Y + 2, "=", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X - 2] == '=')
	{

		g_Console.writeToBuffer(c.X - 2, c.Y + 2, "=", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X - 1] == '=')
	{

		g_Console.writeToBuffer(c.X - 1, c.Y + 2, "=", 0x7B);
	}

	//y-2

	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X - 2] == '=')
	{

		g_Console.writeToBuffer(c.X - 2, c.Y - 2, "=", 0x7B);
	}


	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X - 1] == '=')
	{

		g_Console.writeToBuffer(c.X - 1, c.Y - 2, "=", 0x7B);

	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X + 1] == '=')
	{

		g_Console.writeToBuffer(c.X + 1, c.Y - 2, "=", 0x7B);

	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X + 2] == '=')
	{

		g_Console.writeToBuffer(c.X + 2, c.Y - 2, "=", 0x7B);

	}

	////=================================Check for if |

	if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == '|')
	{
		
		g_Console.writeToBuffer(c.X+1,c.Y, "|", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == '|')
	{
		
		g_Console.writeToBuffer(c.X+2,c.Y,"|", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == '|')
	{
	
		g_Console.writeToBuffer(c.X-1,c.Y, "|", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == '|')
	{
		
		g_Console.writeToBuffer(c.X-2,c.Y, "|", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == '|')
	{
		
		g_Console.writeToBuffer(c.X,c.Y+1, "|", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == '|')
	{
		
		g_Console.writeToBuffer(c.X,c.Y+2, "|", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == '|')
	{
		
		g_Console.writeToBuffer(c.X,c.Y-1 ,"|", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == '|')
	{
		
		g_Console.writeToBuffer(c.X,c.Y-2, "|", 0x7B);
	}


	//square

	//y+1

	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X - 1] == '|')
	{

		g_Console.writeToBuffer(c.X - 1, c.Y + 1, "|", 0x7B);
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X - 2] == '|')
	{

		g_Console.writeToBuffer(c.X - 2, c.Y + 1, "|", 0x7B);
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X + 1] == '|')
	{

		g_Console.writeToBuffer(c.X + 1, c.Y + 1, "|", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X + 2] == '|')
	{

		g_Console.writeToBuffer(c.X + 2, c.Y + 1, "|", 0x7B);
	}
	//y-1
	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X - 1] == '|')
	{

		g_Console.writeToBuffer(c.X - 1, c.Y - 1, "|", 0x7B);
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X - 2] == '|')
	{

		g_Console.writeToBuffer(c.X - 2, c.Y - 1, "|", 0x7B);
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X + 1] == '|')
	{

		g_Console.writeToBuffer(c.X + 1, c.Y - 1, "|", 0x7B);
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X + 2] == '|')
	{

		g_Console.writeToBuffer(c.X + 2, c.Y - 1, "|", 0x7B);
	}

	// y +2
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X + 2] == '|')
	{

		g_Console.writeToBuffer(c.X + 2, c.Y + 2, "|", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X + 1] == '|')
	{

		g_Console.writeToBuffer(c.X + 1, c.Y + 2, "|", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X - 2] == '|')
	{

		g_Console.writeToBuffer(c.X - 2, c.Y + 2, "|", 0x7B);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X - 1] == '|')
	{

		g_Console.writeToBuffer(c.X - 1, c.Y + 2, "|", 0x7B);
	}

	//y-2

	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X - 2] == '|')
	{

		g_Console.writeToBuffer(c.X - 2, c.Y - 2, "|", 0x7B);
	}


	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X - 1] == '|')
	{

		g_Console.writeToBuffer(c.X - 1, c.Y - 2, "|", 0x7B);

	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X + 1] == '|')
	{

		g_Console.writeToBuffer(c.X + 1, c.Y - 2, "|", 0x7B);

	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X + 2] == '|')
	{

		g_Console.writeToBuffer(c.X + 2, c.Y - 2, "|", 0x7B);

	}
	// Check for spikes


	if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == 'X')
	{

		g_Console.writeToBuffer(c.X + 1, c.Y, "X", 0x7C);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 2] == 'X')
	{

		g_Console.writeToBuffer(c.X + 2, c.Y, "X", 0x7C);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == 'X')
	{

		g_Console.writeToBuffer(c.X - 1, c.Y, "X", 0x7C);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 2] == 'X')
	{

		g_Console.writeToBuffer(c.X - 2, c.Y, "X", 0x7C);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == 'X')
	{

		g_Console.writeToBuffer(c.X, c.Y + 1, "X", 0x7C);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X] == 'X')
	{

		g_Console.writeToBuffer(c.X, c.Y + 2, "X", 0x7C);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == 'X')
	{

		g_Console.writeToBuffer(c.X, c.Y - 1, "X", 0x7C);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X] == 'X')
	{

		g_Console.writeToBuffer(c.X, c.Y - 2, "X", 0x7C);
	}

	//square


	//y+1

	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X - 1] == 'X')
	{

		g_Console.writeToBuffer(c.X - 1, c.Y + 1, "X", 0x7C);
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X - 2] == 'X')
	{

		g_Console.writeToBuffer(c.X - 2, c.Y + 1, "X", 0x7C);
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X + 1] == 'X')
	{

		g_Console.writeToBuffer(c.X + 1, c.Y + 1, "X", 0x7C);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X + 2] == 'X')
	{

		g_Console.writeToBuffer(c.X + 2, c.Y + 1, "X", 0x7C);
	}
	//y-1
	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X - 1] == 'X')
	{

		g_Console.writeToBuffer(c.X - 1, c.Y - 1, "X", 0x7C);
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X - 2] == 'X')
	{

		g_Console.writeToBuffer(c.X - 2, c.Y - 1, "X", 0x7C);
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X + 1] == 'X')
	{

		g_Console.writeToBuffer(c.X + 1, c.Y - 1, "X", 0x7C);
	}

	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X + 2] == 'X')
	{

		g_Console.writeToBuffer(c.X + 2, c.Y - 1, "X", 0x7C);
	}

	// y +2
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X + 2] == 'X')
	{

		g_Console.writeToBuffer(c.X + 2, c.Y + 2, "X", 0x7C);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X + 1] == 'X')
	{

		g_Console.writeToBuffer(c.X + 1, c.Y + 2, "X", 0x7C);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X - 2] == 'X')
	{

		g_Console.writeToBuffer(c.X - 2, c.Y + 2, "X", 0x7C);
	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y + 2][g_sChar.m_cLocation.X - 1] == 'X')
	{

		g_Console.writeToBuffer(c.X - 1, c.Y + 2, "X", 0x7C);
	}

	//y-2

	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X - 2] == 'X')
	{

		g_Console.writeToBuffer(c.X - 2, c.Y - 2, "X", 0x7C);
	}


	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X - 1] == 'X')
	{

		g_Console.writeToBuffer(c.X - 1, c.Y - 2, "X", 0x7C);

	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X + 1] == 'X')
	{

		g_Console.writeToBuffer(c.X + 1, c.Y - 2, "X", 0x7C);

	}
	if (Map[LevelSelection][g_sChar.m_cLocation.Y - 2][g_sChar.m_cLocation.X + 2] == 'X')
	{

		g_Console.writeToBuffer(c.X + 2, c.Y - 2, "X", 0x7C);

	}
  }	
}

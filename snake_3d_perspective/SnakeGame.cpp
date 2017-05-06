
#include "SnakeGame.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

void SnakeGame::play()
{
	// Print basic instructions
	std::cout << "\nq: to quit\n8: up\t5: down\t\t\t\t\t\t8: up\t5: down\n4: left\t6: right\t\t\t\t\t9: left\t3:right\n9: deeper\t3: surfacing\t\t\t\t4: deeper\t6: surfacing\n";
	// sets theSnake into board tiles and prints the board, tile by tile, to the console
	theBoard.display();
	// Pause lets user read the instructions and get themselves ready to play
	system("pause");

	// Player has pressed somthing causeing the game to start
	playing = true;

	while (playing)
	{
		// clears the console of printed information

		// Determines if keyboard character was hit and which one
		getUserInput();

		// 
		theBoard.update();
		theBoard.display();

		if (sleepTime > 0)
		{
			Sleep(sleepTime--);
		}

		playing = theBoard.isPlaying();
	}

	std::cout << "\nGAME OVER\n\n";
}

void SnakeGame::getUserInput()
{
	//_kbhit == keyboard hit
	if (_kbhit())
	{
		//_getch() == getchar() == get input
		theBoard.parseInput(_getch());
	}
}
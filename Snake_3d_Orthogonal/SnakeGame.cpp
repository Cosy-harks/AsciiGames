#include "SnakeGame.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

void SnakeGame::play()
{
	// sets theSnake into board tiles and prints the board, tile by tile, to the console
	theBoard.display();
	
	// Pause lets user read the instructions and get themselves ready to play
	system("pause"), getUserInput();

	// Player has pressed somthing causeing the game to start
	playing = true;

	while (playing)
	{

		// Determines if keyboard character was hit and which one
		getUserInput();

		// Places fruit in new spot and or moves the snake
		theBoard.update();

		// clears the console of printed information
		system("cls");

		theBoard.display();

		(sleepTime > 200) ? Sleep(sleepTime--) : Sleep(sleepTime); 
				
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
#include "SnakeGame.h"
#include <iostream>

using namespace std;


// Program starts at the "main()" function
int main()
{
	// Creates an object instance of SnakeGame
	SnakeGame *g = new SnakeGame;
	char play;

	do {
		g->play();
		delete g;
		g = new SnakeGame;
		getchar();
		// Sets up the game to be played

		cout << "\nDo you want to play again(y/n)?";
		cin >> play;
	} while (play == 'y');
	delete g;
	// Pauses display before exiting out.
	system("pause");
	return 0;
}
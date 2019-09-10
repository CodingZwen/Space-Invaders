#include <SFML\Graphics.hpp>
#include <iostream>
#include "Game.h"
#include <Windows.h>
#include <conio.h>
#include <tchar.h>
#include <strsafe.h>
#include <memory>

using namespace std;



void setFrame(int Frame) {
	int currentFrame = Frame < 10 ? Frame : 0;

	std::cout << "reingekommen: " << Frame <<
		" currentFrame: " << currentFrame << std::endl;

};


int main(int argc, TCHAR *argv[]) {

	srand(time(NULL));

	TCHAR szOldTitle[MAX_PATH];
	TCHAR szNewTitle[MAX_PATH];

	// Save current console title.

	if (GetConsoleTitle(szOldTitle, MAX_PATH))
	{
		// Build new console title string.

		StringCchPrintf(szNewTitle, MAX_PATH, TEXT("Space Invaders"));

		// Set console title to new title
		if (!SetConsoleTitle(szNewTitle))
		{
			_tprintf(TEXT("SetConsoleTitle failed (%d)\n"), GetLastError());
			return 1;
		}
		else
		{
			_tprintf(TEXT("SetConsoleTitle succeeded.\n"));
		}
	}
	

	//Game g(sf::Vector2i(480,320),40);
	Game g(sf::Vector2i(1280, 768), 99);

	while (g.isRunning())
	{
		g.run();
	}

	return 0;
}

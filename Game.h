#pragma once
#include <memory>
#include <iostream>
#include <fstream>
#include "StartMenue.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "SoundHandler.h"

class Game
{
	const std::string GAMENAME = "SPACE INVADERS";

	sf::Font font;
	bool fullScreen;
	bool showFPS;
	bool running;

	sf::ContextSettings windowSettings;
	std::vector<sf::VideoMode> videoModes;

	sf::View view;

	sf::Clock gameClock;
	sf::Clock fpsClock;

	sf::Time now;

	sf::Time passedTime;

	std::unique_ptr<State> currentState;

	
public:
	sf::Time frameDeltaTime;
	enum GameInstances { Startmenuestate, Playstate, Optionstate };
	sf::RenderWindow window;
	Game(sf::Vector2i resolution,const unsigned short maxFPS=40);
	~Game();

	void Game::updateMousePositions();
	void initStartMenue();
	void initByFile();
	void run();
	void start() { running = true; }

	void initSounds();

	bool isRunning() { return running; }
	void stopRunning() { running = false; }
	void changeState(GameInstances state);

	//getters machen
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	bool setview = false;

	AssetManager assetManager;
	SoundHandler soundHandler;
};


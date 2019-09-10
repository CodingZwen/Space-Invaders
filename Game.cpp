#include "Game.h"



Game::Game(sf::Vector2i resolution,unsigned short maxFPS)
{
	window.create(sf::VideoMode(resolution.x, resolution.y), "Space Invaders");
	running = true;
	window.setFramerateLimit(maxFPS);
	showFPS = true;


	if (font.loadFromFile("resources\\KenPixel Future.ttf"))
		printf("font geladen");
	else printf("font nicht geladne\n");

	//needs initalized font
	initStartMenue();
	initSounds();


	assetManager.LoadTextures();
	assetManager.LoadSounds();
	assetManager.LoadFonts();

	soundHandler.init(assetManager);

}


Game::~Game()
{
}

void Game::updateMousePositions()
{

		this->mousePosScreen = sf::Mouse::getPosition();
		this->mousePosWindow = sf::Mouse::getPosition(this->window);
		this->mousePosView = this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window));

	
}

void Game::initStartMenue()
{
	currentState = std::move(std::unique_ptr<StartMenue>(new StartMenue(&this->font, sf::Vector2i(window.getSize().x, window.getSize().y))));


}

void Game::initByFile()
{
	std::ifstream ifs("settings/settings.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode(); //current desktop resolution
	unsigned int Framerate = 120;
	bool verticalSync = false;
	bool fullScreen;

	if (ifs.is_open())
	{
		//erste zeile wird gelesen und in name gesdpeichert


		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullScreen;
		ifs >> Framerate;
		ifs >> verticalSync;
		std::cout << "Erfolgreich Ini geladen" << std::endl;
	}
	ifs.close();


	if (window_bounds.height > 1080 || window_bounds.height < 240
		|| window_bounds.width >1920 || window_bounds.width < 320)
	{
		std::cerr << "w: " << window_bounds.width << " height: " << window_bounds.height << std::endl;
		window_bounds.width = 800;
		window_bounds.height = 600;
		std::cerr << "Standard Screen Dimensions Loaded!\n";
	}

	this->fullScreen = fullScreen;
	this->windowSettings.antialiasingLevel = 0;

	if (this->fullScreen)
		window.create(window_bounds, GAMENAME, sf::Style::Fullscreen, windowSettings);
	else
		window.create(window_bounds, GAMENAME, sf::Style::Titlebar | sf::Style::Close, windowSettings);

	window.setFramerateLimit(Framerate);
	window.setVerticalSyncEnabled(verticalSync);
}

void Game::run()
{
	while (window.isOpen()) {

		now = gameClock.getElapsedTime();
		frameDeltaTime = (now - passedTime); //zeit zwischen den frames
		passedTime = now;
		currentState->HandleEvents(*this);
		updateMousePositions();


		if (showFPS)
		{
			sf::Time time = fpsClock.getElapsedTime();
			float fps = 1.0f / time.asSeconds();
			window.setTitle(std::to_string(fps));
			fpsClock.restart();

		}

		window.clear();

		soundHandler.update(frameDeltaTime);
		currentState->Update(*this);
		currentState->Draw(*this);
		window.display();
	}
}

void Game::initSounds()
{
	

}

void Game::changeState(GameInstances state)
{
	switch (state) {

	case  GameInstances::Startmenuestate:
		currentState = std::move(std::unique_ptr<StartMenue>(new StartMenue(&font,sf::Vector2i(window.getSize().x, window.getSize().y)))); break;
	case GameInstances::Playstate:
		currentState = std::move(std::unique_ptr<GameState>(new GameState(&this->window,this->assetManager,this->soundHandler))); break;
	case GameInstances::Optionstate:
		break;

	default:break;
	}

}


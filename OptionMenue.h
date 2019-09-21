#pragma once
#define RESOLUTIONS 4
#define XY 2
#include "State.h"
#include "Game.h"

constexpr int resolutions[RESOLUTIONS][XY] = {
	{ 1920, 1080 },
	{ 1600, 900 },
	{ 1280, 720 },
	{ 800, 600 }
};


class OptionMenue :
	public State
{

	
public:
	OptionMenue();
	virtual ~OptionMenue();

	void HandleEvents(Game &a);
	void Update(Game &a);
	void Draw(Game &a);
	void setSettings();//inifile
	void loadSettings();

	void RenderButtons(sf::RenderTarget &target);
	void updateButtons(Game &game);


};


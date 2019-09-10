#include "SoundHandler.h"



void SoundHandler::stopMusic()
{
	
	if (currentMusic!=nullptr)currentMusic->stop();
}

void SoundHandler::init(AssetManager & Amanager)
{
	
	currentMusic = nullptr;
	sounds["pew"].setBuffer(*Amanager.ptr_GetSound("pew"));
	sounds["select"].setBuffer(*Amanager.ptr_GetSound("select"));
	sounds["explosion"].setBuffer(*Amanager.ptr_GetSound("explosion"));

	
	lastsound = "";
	

//	Music["DesertMusic"].openFromFile("Spiel_Projekt_Protectyourisle_Assets\\Sounds\\Desert.ogg");
}

void SoundHandler::playSound(std::string soundName, bool loop)
{
	//if (soundTimer.asSeconds() > 0.3)
	if (lastsound != soundName)
	{
		lastsound = soundName;
		sounds[soundName].setVolume(50);
		sounds[soundName].play();
		sounds[soundName].setLoop(loop);
		soundTimer = soundTimer.Zero;
	}
	else
	{
		if (soundTimer.asSeconds() > 0.3)
		{
			lastsound = soundName;
			sounds[soundName].setVolume(50);
			sounds[soundName].play();
			sounds[soundName].setLoop(loop);
			soundTimer = soundTimer.Zero;
			

		}
	}
}

void SoundHandler::playMusic(std::string SongName, bool loop)
{
	if(currentMusic!=nullptr)currentMusic->stop();
	Music[SongName].setVolume(5.5);
	Music[SongName].play();
	Music[SongName].setLoop(loop);
	currentMusic = &Music[SongName];

}

void SoundHandler::update(sf::Time elapsed)
{
	soundTimer += elapsed;
}

SoundHandler::SoundHandler()
{
}


SoundHandler::~SoundHandler()
{
}

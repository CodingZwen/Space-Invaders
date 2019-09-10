#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include "AssetManager.h"
class SoundHandler
{

	std::map< std::string, sf::Sound > sounds;
	std::map< std::string, sf::Music > Music;


	sf::Music *currentMusic;
	std::string lastsound;


	sf::Time soundTimer;

public:

	void stopMusic();
	void init(AssetManager  & Amanager);
	void playSound(std::string soundName, bool loop = false);
	void playMusic(std::string SongName, bool loop = true);
	void update(sf::Time elapsed);

	SoundHandler();
	~SoundHandler();
};



/*
template <typename T, typename U>
class create_map
{
private:
	std::map<T, U> m_map;
public:
	create_map(const T& key, const U& val)
	{
		m_map[key] = val;
	}

	create_map<T, U>& operator()(const T& key, const U& val)
	{
		m_map[key] = val;
		return *this;
	}

	operator std::map<T, U>()
	{
		return m_map;
	}
};
*/
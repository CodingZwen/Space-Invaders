#pragma once
#include <map>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>


	//-> stdmap<name,texture>
	//1. png bild in vector laden -> ifstsream von bild.png einlesen
	//2. aus dem vector einen string machen und namen vorne dran machen bzw. 20 zeichen space
	//3. der string kann dann in einen vektor rein
	//wiedervon vorne
	class AssetManager
	{
	public:
		 AssetManager();
		~AssetManager();
			

		void LoadTexture(std::string  name, const char *fileName, bool smooth = false);
		sf::Texture &GetTexture(std::string name);

		void LoadFont(std::string name, std::string fileName);
		sf::Font *ptr_GetFont(std::string name);


		void LoadSound(std::string name, std::string fileName);
		sf::SoundBuffer *ptr_GetSound(std::string name);

		//macht aus der std map wenn sie von loadaalltexturesfromimages geladen wurde eine binäre datei
		//die dann mit loadfromfile wieder in std map umgewandelt werden kann
	
		void LoadTextures();
		void LoadSounds();
		void LoadFonts();

	private:
		

		
		std::vector<std::string> TexturesForFile;
		std::vector<std::string> vBinary;
				
		std::map < std::string, sf::Texture> _textures;
		std::map < std::string, sf::Font> _fonts;
		std::map < std::string, sf::SoundBuffer> _sounds;

		sf::Texture t_error;
	
	};



	/*
	
		std::map<std::string, int> wordMap = {
			{ "is", 6 }, { "the", 5 },
			{ "hat", 9 }, { "at", 6 }
										};
 
	// Create an iterator of map
	std::map<std::string, int>::iterator it;
 
	// Find the element with key 'hat'
	it = wordMap.find("hat");
 
	// Check if element exists in map or not
	if (it != wordMap.end()) {
		// Element with key 'hat' found
		std::cout << "'hat' Found" << std::endl;
 
		// Access the Key from iterator
		std::string key = it->first;
		// Access the Value from iterator
		int value = it->second;
 
		std::cout << "key = " << key << " :: Value = " << value << std::endl;
	} else {
		// Element with key 'hat' Not Found
		std::cout << "'hat' Not Found" << std::endl;
	}
 
	// Find the element with key 'hello'
	it = wordMap.find("hello");
 
	// Check if element exists in map or not
	if (it != wordMap.end()) {
		// Element with key 'hello' found
		std::cout << "'hello' Found" << std::endl;
 
		// Access the Key from iterator
		std::string key = it->first;
		// Access the Value from iterator
		int value = it->second;
 
		std::cout << "key = " << key << " :: Value = " << key << std::endl;
 
	} else {
		// Element with key 'hello' Not Found
		std::cout << "'hello' Not Found" << std::endl;
	}
	*/



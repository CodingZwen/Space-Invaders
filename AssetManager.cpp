#include "AssetManager.h"



AssetManager::AssetManager()
{


}


AssetManager::~AssetManager()
{
}



void AssetManager::LoadTexture(std::string name, const char * fileName, bool smooth)
{
	sf::Texture tex;
	if (tex.loadFromFile(fileName)) {

		tex.setSmooth(smooth);
		this->_textures[name] = tex;


	}
	else {

		printf("\nTextur mit Pfad: %s konnte nicht geladen werden!", fileName);

	}
}

//evtl rosa texture laden wenn name nicht trifft
	//anscheinend programmiere ich mit c++ 17 da c++ 20 bei map die funktion contains hat
	sf::Texture & AssetManager::GetTexture(std::string name)
	{
		std::map< std::string, sf::Texture >::iterator it;
		it = _textures.find(name);

		//ganz komisch, funktioniert wie eine while schleife
		if (it != _textures.end()) {
			
			//printf("\nTexture gefunden und geladen -> Name:  %s",  it->first);
			return this->_textures.at(name);
		}
		else {
			//printf("\nTexture mit dem Namen  %s konnte nicht gefunden werden",name);

			return this->t_error;
		}


	
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{


		sf::Font font;

		if (font.loadFromFile(fileName)) {

			this->_fonts[name] = font;
		}
		else {

			//printf("\nSound mit Pfad: %s konnte nicht geladen werden!", fileName);

		}

	}

	sf::Font * AssetManager::ptr_GetFont(std::string name)
	{
		std::map< std::string, sf::Font >::iterator it;
		it = _fonts.find(name);
		sf::Font *ptr_font;

		//ganz komisch, funktioniert wie eine while schleife
		if (it != _fonts.end()) {

			//printf("\nFont gefunden und geladen -> Name:  %s", it->first);
			ptr_font =&_fonts.at(name);
			return ptr_font;
		}
		else {
			//printf("\nFont mit dem Namen  %s konnte nicht gefunden werden", name);

			return nullptr;
		}
	}

	void AssetManager::LoadSound(std::string name, std::string fileName)
	{

		sf::SoundBuffer soundbuffer;

		if (soundbuffer.loadFromFile(fileName)) {

			this->_sounds[name] = soundbuffer;
		}
		else {

			//printf("\nSound mit Pfad: %s konnte nicht geladen werden!", fileName);

		}

	}

	sf::SoundBuffer * AssetManager::ptr_GetSound(std::string name)
	{
		std::map< std::string, sf::SoundBuffer >::iterator it;
		it = _sounds.find(name);
		sf::SoundBuffer *ptr_sound;

		//ganz komisch, funktioniert wie eine while schleife
		if (it != _sounds.end()) {

			//printf("\nSound gefunden und geladen -> Name:  %s", it->first);
			ptr_sound = &_sounds.at(name);
			return ptr_sound;
		}
		else {
		//	printf("\nSound mit dem Namen  %s konnte nicht gefunden werden", name);

			return nullptr;
		}
	}

	void AssetManager::LoadTextures()
	{
		LoadTexture("enemy1", "resources\\enemy1.png");
		LoadTexture("enemy2", "resources\\enemy2.png");
		LoadTexture("enemy3", "resources\\enemy3.png");
	}

	void AssetManager::LoadSounds()
	{
		LoadSound("pew", "resources\\Laser2.wav");
		LoadSound("select", "resources\\menueselect.wav");
		LoadSound("explosion", "resources\\Explosion.wav");
	}

	void AssetManager::LoadFonts()
	{
		LoadFont("font", "resources\\KenPixel Future.ttf");
	}


	

	




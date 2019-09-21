#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#define _OWNDEBUG 0
#define LISTSIZE 20


struct MyBytes
{

	unsigned char bytes[4];

	MyBytes()
	{
		bytes[0] = 0x00;
		bytes[1] = 0x00;
		bytes[2] = 0x00;
		bytes[3] = 0x00;
	}
	void reset()
	{
		bytes[0] = 0x00;
		bytes[1] = 0x00;
		bytes[2] = 0x00;
		bytes[3] = 0x00;
	}

	void setBytes(unsigned char Byte, unsigned int Position)
	{
		if (Position > 3)return;
		bytes[Position] = Byte;
	}

	uint32_t getBytesAsInt() {

		uint32_t foo;

		foo = (uint32_t)bytes[0] << 24;
		foo |= (uint32_t)bytes[1] << 16;
		foo |= (uint32_t)bytes[2] << 8;
		foo |= (uint32_t)bytes[3];

		return foo;
	}
};


class Highscore
{
	std::vector<std::string> Highscores;

	//help functions
	void printInttoBytes(const unsigned int   &i);
	std::string cutSpaces(const std::string  &name);//just return string without " "
	//construkt and returns the "highscore" string with name and highscore
	std::string addNametoHighscore(std::vector<unsigned char>& highscorebinary, std::string playername, unsigned int spacesForName = 30);


	//create functions
	//creates the binary vector for file
	std::vector<unsigned char> CreateBinaryVecReadyToPrint(const std::vector<std::string> &HighscoreVec);
	//creates the file out of the binary vector from foo about
	void createBinaryFile(std::vector<unsigned char> &bytesForFile, std::string outputfilename);

	bool printVector(std::vector<unsigned char> &v, int flag = 0);

	//readfile fehlt noch
	//readfunctions
	//to get amount of highscores in binary file ( vector<uchar>)
	uint32_t GetFirstBytesBinaryVecAsInt(std::vector<unsigned char>& v);
	std::vector<std::string> readBinaryCharVecToStringV(std::vector<unsigned char> &v);
	std::vector<unsigned char> getBytesFromFile(std::string path, bool print = false);



public:
	Highscore();
	~Highscore();

	//this funuctions uses addnametohighscore
	void pushHighscore(unsigned int _highscore,std::string const &name);
	void loadHighscoresFromFile(std::string filename);
	void saveHighscoresinFile();

	std::vector<unsigned char> getIntasBytes(unsigned int _Highscore);
	std::pair<std::string, unsigned int> getHighscoreWithname(std::string highscorestring);
	std::pair<std::string, unsigned int> getMaxscoreWithname();

	
	void printAllHighscores();
	//the string is  also be cuttet in this function
	//but its copy
	std::string getNameandHighscorefromHighscoreString(std::string highscorestring, int *highscore);

	void printHighscoreString(std::string const &highscorestring);


};

//funktionstemplate schreiben das einen char vector nimmt und string zurückgibt
//string bekommt und char vector zturückgibt


/*unsigned vorteile

it has no padding bits, that it where all storage bits contribute to the value of the data
no bitwise operation starting from a value of that type, when converted back into that type, can produce overflow, trap representations or undefined behavior
it may alias other data types without violating the "aliasing rules", that is that access to the same data through a pointer that is typed differently will be guaranteed to see all modifications

*/
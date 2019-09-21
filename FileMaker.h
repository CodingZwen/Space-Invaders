#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <map>

#include <SFML/Graphics.hpp>
using namespace std;

struct MyBytes
{

	unsigned char bytes[4];

	MyBytes()
	{
		bytes[0]= 0x00;
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


//manual means you ucan type the filename
class FileMaker
{
public:
	FileMaker();
	~FileMaker();

	//Erstellfunktionen
	std::string addFileNameToBinaryVec(std::vector<char> &v, string picName, unsigned int spaces = 30);
	std::vector<unsigned char> CreateBinaryVecReadyToPrint(vector<string> &v);
	void createBinaryFile(std::vector<unsigned char> &bytesForFile, string outputfilename);
	
	//Readfunktion
	std::vector<unsigned char> getBytesFromFile(std::string path, bool print = false);
	std::vector<vector<unsigned char>> readBinaryCharVecToStringV(vector<unsigned char> &v);
	std::map<std::string,sf::Texture> getBinaryFileAsMap(vector<vector<unsigned char>> &v);
	


	//helpfunctions
	std::string getNamefromCuttedVector(string &name);
	std::string cutVector(vector<unsigned char> &vecToCut, int cutCount = 30);

	
	void ReadTextFileManual();
	void CopyFileManual();
	void PrintAsHexa(string &thisAsHexaPls);
	std::ifstream::pos_type getFileSize(const char* filename);
	
	//der charvec der eingelesen wird mit mehreren bildern
	// hier in einzelne strings zerlegt
	//hier kommt der stringvector rein mit den namen + bilderstrings
	
	
	uint32_t GetFirstBytesFromFile(string filename);
	uint32_t GetFirstBytesBinaryVecAsInt(vector<unsigned char> &v);
	std::vector<char> ReadFile(const char *pngfilename);
	//todo flag 7 = 111 alles 
	bool printVector(vector<unsigned char> &v, int flag=0);
	void printFileHexadecimal(string filename, bool manual = 0);
	void PrintIntToBytes(int i);


	//sollte gehen, alternative zu copy
	void createBinaryFileAlternate(std::vector<unsigned char> &binaryCharVec, string outputfilename);
	
	//evlt wenn mehr skills vorhanden guckjen ob diese funtkioniert
	//und dann die alte ersetzen

	template <typename T>
	void createBinaryFileAnyData(std::vector<T> &bytesForFile, string outputfilename);



};


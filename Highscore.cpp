#include "Highscore.h"



Highscore::Highscore()
{
}


Highscore::~Highscore()
{
}

void Highscore::pushHighscore(unsigned int _highscore, std::string const & name)
{

	bool newHighscore = false;


	std::vector<unsigned char> binaryHighscore = getIntasBytes(_highscore);
	std::string highscorewithname = addNametoHighscore(binaryHighscore, name);

	Highscores.push_back(highscorewithname);

}

void Highscore::loadHighscoresFromFile(std::string filename)
{
	std::vector<unsigned char> highscoresbinary = getBytesFromFile("highscores.bin");
	this->Highscores = readBinaryCharVecToStringV(highscoresbinary);
}

void Highscore::saveHighscoresinFile()
{
	std::vector<unsigned char> binaryfile = CreateBinaryVecReadyToPrint(this->Highscores);
	createBinaryFile(binaryfile, "highscores.bin");
}

std::vector<unsigned char> Highscore::getIntasBytes(unsigned int _Highscore)
{
	unsigned int x = _Highscore;
	unsigned char bytes[sizeof x];
	std::vector<unsigned char> buffer;
	std::copy(static_cast<const unsigned char*>(static_cast<const void*>(&x)),
		static_cast<const unsigned char*>(static_cast<const void*>(&x)) + sizeof x,
		bytes);

	for (int j = 0; j < 4; j++) {

		buffer.insert(buffer.begin(), bytes[j]);
	}

	
	return buffer;

}

std::string Highscore::addNametoHighscore(std::vector<unsigned char>& highscorebinary, std::string playername, unsigned int spacesForName)
{

	std::string buffer = "                              ";//30 zeichen plkatz
	std::string sBinaryHighscoreWithName = "";
	size_t size = playername.length();
	if (size > spacesForName) { std::cerr << "name zu lang!";	return playername; }

	for (size_t i = 0; i < size; i++) // name in buffer reinschreiben
		buffer.at(i) = playername.at(i);

	sBinaryHighscoreWithName += buffer; //buffer bzw name in finalstring reinstecken


	//dann nach dem namen das bin#re bild noch hintendran
	for (std::vector<unsigned char>::const_iterator i = highscorebinary.begin();
		i != highscorebinary.end(); ++i)
	{
		sBinaryHighscoreWithName += *i;
	}

	

	return sBinaryHighscoreWithName;



}

std::vector<unsigned char> Highscore::CreateBinaryVecReadyToPrint(const std::vector<std::string>  & HighscoreVec)
{
	
	int HighscoreCount = HighscoreVec.size(); //anzahl der tatsächlichen highscores
	std::cout << "anzahl der highscores: " << HighscoreCount << '\n';
	std::vector<unsigned char> finalBinaryVec;
	std::vector<std::string>::const_iterator  it = HighscoreVec.begin();
	


	for (; it != HighscoreVec.end(); it++)
	{	//alle strings werden in char arrays umgewandelt und aneinandergereiht
		std::string s = *it;
		int size = s.length(); //sollte immer 34 sein
		for (int i = 0; i < size; i++) {

			finalBinaryVec.push_back(s[i]);
		}

	}

	

	//am ende schreiben vor die anzahl der highscores bzw. die anzahl der highscore strings 
	//an den anfang der datei damit wir wieder alles richtig einlesen können
	unsigned int x = HighscoreCount;
	unsigned char bytes[sizeof x];
	std::copy(static_cast<const unsigned char*>(static_cast<const void*>(&x)),
		static_cast<const unsigned char*>(static_cast<const void*>(&x)) + sizeof x,
		bytes);

	for (int j = 0; j < 4; j++) {

		finalBinaryVec.insert(finalBinaryVec.begin(), bytes[j]);
	}


	

	return finalBinaryVec;
}

void Highscore::createBinaryFile(std::vector<unsigned char>& bytesForFile, std::string outputfilename)
{
	std::ofstream output_file(outputfilename, std::ios::binary);
	std::ostream_iterator<unsigned char> output_iterator(output_file);
	std::copy(bytesForFile.begin(), bytesForFile.end(), output_iterator);

}

bool Highscore::printVector(std::vector<unsigned char>& v, int flag)
{
	const std::string codierung{ "0123456789ABCDEF" };
	unsigned int seiteneffekt = 0;

	if (v.size() < 1)
	{
		std::cerr << "Vector leer!\n";
		return false;
	}

	for (std::vector<unsigned char>::iterator it = v.begin(); it != v.end(); ++it) {
		std::cout << "Uchar: " << *it << " Hexa: ";
		unsigned int zahl = static_cast<unsigned int>(*it);

		std::cout << codierung.at(zahl / 16) << codierung.at(zahl % 16) << " ";

		if (++seiteneffekt % 10 == 0) { std::cout << '\n'; }

	}

	return true;
}

uint32_t Highscore::GetFirstBytesBinaryVecAsInt(std::vector<unsigned char>& v)
{
	const std:: string codierung{ "0123456789ABCDEF" };
	unsigned char code[4];
	uint32_t foo;
	code[0] = v.at(0);
	code[1] = v.at(1);
	code[2] = v.at(2);
	code[3] = v.at(3);

	//macht nicht viel sind da werte nicht 

	if (_OWNDEBUG)
	{
		std::cout << "eingehende bytes: " << code[0] << ":" << code[1] << ":"
			<< code[2] << ":" << code[3] << std::endl;
	}

	foo = (uint32_t)code[0] << 24;
	foo |= (uint32_t)code[1] << 16;
	foo |= (uint32_t)code[2] << 8;
	foo |= (uint32_t)code[3];

	printInttoBytes(foo);

	return foo;
}

std::vector<std::string> Highscore::readBinaryCharVecToStringV(std::vector<unsigned char>& v)
{

	uint32_t HighscoreCount = GetFirstBytesBinaryVecAsInt(v);//3
	std::cout << "HighscoreCount: " << HighscoreCount <<'\n';
	
	std::vector<std::string> highscorestrings;
	int count = 0;

	//wir fangen jetzt bei den highscorestrings an
	std::vector<unsigned char>::iterator it = v.begin() + 4;
	std::string buffer;

	count = 0;
	
	for (; it != v.end(); it++)
	{
		buffer.push_back(*it);
		count++;

		//thats shit here
		if (count == 34)
		{
			highscorestrings.push_back(buffer);
			count = 0;
			buffer.clear();

		}
	}

	std::cout << "anzahl der highscorestrings: " << highscorestrings.size() << '\n';
	return highscorestrings;
}

std::vector<unsigned char> Highscore::getBytesFromFile(std::string path, bool print)
{
	std::string Quelldateiname = path;
	std::streampos fileSize;
	std::ifstream file(Quelldateiname, std::ios::binary);


	file.seekg(0, std::ios::end);
	fileSize = file.tellg(); //tellg = getsize in bytes
	file.seekg(0, std::ios::beg);

	// read the data:
	std::vector<unsigned char> fileData(static_cast<int>(fileSize));
	file.read((char*)&fileData[0], fileSize);



	(print) ? printVector(fileData) : printf("Bild Geladen!");


	return fileData;
}

void Highscore::printInttoBytes(const unsigned int  &i)
{
	const std::string codierung{ "0123456789ABCDEF" };
	std::string buffer = "";

	unsigned int x = i;
	unsigned char bytes[sizeof x];
	std::copy(static_cast<const unsigned char*>(static_cast<const void*>(&x)),
		static_cast<const unsigned char*>(static_cast<const void*>(&x)) + sizeof x,
		bytes);

	std::cout << "Zahl: " << i << " als Hexa: ";
	for (int i = 3; i > -1; i--)
	{
		unsigned int zahl = static_cast<unsigned int>(bytes[i]);
		std::cout << codierung.at(zahl / 16) << codierung.at(zahl % 16) << " ";
		buffer += codierung.at(zahl / 16);
		buffer += codierung.at(zahl % 16);
		buffer += " ";

	}

	std::cout << '\n';
}

std::pair<std::string, unsigned int> Highscore::getHighscoreWithname(std::string highscorestring)
{

	std::string highscore;
	unsigned int cutcount = 30;
	std::vector<unsigned char> binaryHighscore;
	std::string playername = "";

	if (highscorestring.size() < cutcount)
	{

		std::cerr << "string  zum kuerzen ist kleiner als NameBuffer: " << cutcount << std::endl;
		
	}

	for (int i = 0; i < cutcount; i++)
	{
		playername += *highscorestring.begin();
		highscorestring.erase(highscorestring.begin());
	}


	//verbleibende bytes sollten die 4 von dem highscores sein
	for (auto &j : highscorestring)
	{
		binaryHighscore.push_back(j);
	}

	uint32_t score = GetFirstBytesBinaryVecAsInt(binaryHighscore);
	std::string finalname = cutSpaces(playername);

	std::pair <std::string, unsigned int > pairHighscore;
	pairHighscore.first = finalname;
	pairHighscore.second = static_cast<unsigned int>(score);

	return pairHighscore;
}

void Highscore::printAllHighscores()
{
	std::cout << "\nEs sind " << Highscores.size() << " Highscores vorhanden\n";

	for (auto &i : Highscores)
	{
		std::string currentHighscore = i;
		unsigned int highscore = getHighscoreWithname(i).second;
		std::string playername = getHighscoreWithname(i).first;
		std::cout << "Spielername: " << playername << " ";
		std::cout << "Higscoren: " << highscore << '\n';

	}
}


//return string until first " "
std::string Highscore::cutSpaces(const std::string  &name)
{
	std::string playername = "";
	auto it = name.begin();

	for (;; it++)
	{
		if (*it == ' ')return playername;
		playername += *it;
	}

	playername = "fehler";
	return playername;
}

std::string Highscore::getNameandHighscorefromHighscoreString(std::string highscorestring, int * highscore)
{
	
	unsigned int cutcount = 30;
	std::vector<unsigned char> binaryHighscore;
	std::string playername = "";

	if (highscorestring.size() < cutcount)
	{

		std::cerr << "string  zum kuerzen ist kleiner als NameBuffer: " << cutcount << std::endl;
		return 0;
	}

	for (int i = 0; i < cutcount; i++)
	{
		playername += *highscorestring.begin();
		highscorestring.erase(highscorestring.begin());
	}


	//verbleibende bytes sollten die 4 von dem highscores sein

	for (auto &j : highscorestring)
	{
		binaryHighscore.push_back(j);
	}

	uint32_t score = GetFirstBytesBinaryVecAsInt(binaryHighscore);
	std::cout << "Spielername ist: " << playername;
	std::cout << "\nmit dem Highscore: " << score;


	return playername;

}

void Highscore::printHighscoreString(std::string const &highscorestring)
{
	//std::string playername;
	//unsigned int highscore;


	//std::string namebuffer = highscorestring;

	


}

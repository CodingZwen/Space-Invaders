#include "FileMaker.h"



FileMaker::FileMaker()
{
}


FileMaker::~FileMaker()
{
}

std::string FileMaker::addFileNameToBinaryVec(std::vector<char>& v, string picName, unsigned int spaces)
{
    	string buffer = "                              ";//30 zeichen plkatz
		string sBinaryImageWithName = "";
		size_t size = picName.length();
		if (size > spaces){cout << "picname zu lang!" << picName << endl;	return "0";}

		for (size_t i = 0; i < size; i++) // name in buffer reinschreiben
		buffer.at(i) = picName.at(i);
	
		sBinaryImageWithName += buffer; //buffer bzw name in finalstring reinstecken


		//dann nach dem namen das bin#re bild noch hintendran
		for (std::vector<char>::const_iterator i = v.begin(); i != v.end(); ++i)
			sBinaryImageWithName += *i;


		return sBinaryImageWithName;
}

void FileMaker::printFileHexadecimal(string filename, bool manual)
{
	string Quelldateiname;

	if (manual)
	{
		cout << "Dateiname :";
		cin >> Quelldateiname;
	}
	else Quelldateiname = filename;

	ifstream quelle(Quelldateiname, ios::binary);
	if (!quelle) { cerr << Quelldateiname << " kann nicht geöffnet werden!\n";	exit(-1); }


	char c;  // signed!
	unsigned int count = 0;
	while (quelle.get(c)) {
		unsigned char uc = static_cast<unsigned char>(c);
		unsigned int zahl = static_cast<unsigned int>(uc);
		const string codierung{ "0123456789ABCDEF" };
		// 2 stellig ausgeben



		cout << codierung.at(zahl / 16) << codierung.at(zahl % 16) << endl;

		if (++count % 4 == 0) {	cout << '\n';}

	}

	quelle.close();
}


std::string FileMaker::getNamefromCuttedVector(string & name)
{
	string finalname = "";
	auto it = name.begin();

	for (;;it++)
	{
		if (*it == ' ')return finalname;
		finalname += *it;
	}

	finalname = "fehler";
	return finalname;
}

//schneidet leidligch die ersten 30 bytes aus dem
//vector raus -> standard parameter in .h
std::string FileMaker::cutVector(vector<unsigned char>& vecToCut, int cutCount)
{

	std::string texName = "";

	if (vecToCut.size() < cutCount)
	{	
		
		cerr << "vectir zum kuerzen ist kleiner als NameBuffer: " << cutCount << endl;
		return 0;
	}

	for (int i = 0; i < cutCount; i++)
	{ 
		texName += *vecToCut.begin();
		vecToCut.erase(vecToCut.begin());
	}

	

	return texName;

}

//evtl ein tempklate aus beiden funktionen bauen
//und dann testen in textdatei was passiert wenn ich int 
//reinschreibe oder bytes
//denk an das beispiel aus dem bucg bei dem ein double aray
//in datei geschrieben wird
//ich mnüsste hier mal eine datei erstelelen und lesen
//ka ob das hier alle datentypen richtig reinschreibt
template <typename T>
void FileMaker::createBinaryFileAnyData(std::vector<T>& bytesForFile, string outputfilename)
{
	std::ofstream output_file(outputfilename, std::ios::binary);
	std::ostream_iterator<T> output_iterator(output_file);
	std::copy(bytesForFile.begin(), bytesForFile.end(), output_iterator);


}

void FileMaker::createBinaryFile(std::vector<unsigned char>& binaryCharVec, string outputfilename)
{

	std::ofstream output_file(outputfilename, std::ios::binary);
	std::ostream_iterator<unsigned char> output_iterator(output_file);
	std::copy(binaryCharVec.begin(), binaryCharVec.end(), output_iterator);


}



void FileMaker::ReadTextFileManual()
{
	string dateiname;
	cout << "Quelldatei? ";
	cin >> dateiname;
	ifstream quelle(dateiname, ios::binary);  // Objekt für die Eingangsdatei
	// Zu \tt{ios::binary} siehe Text
	if (!quelle.good()) {  // Fehlerabfrage
		cerr << dateiname << " kann nicht geöffnet werden!\n";
		exit(-1);
	}

	char ch;
	int count = 0;
	while (quelle.get(ch)) {


		cout << ch << " ";
		if (++count % 20 == 0) {
			cout << '\n';
		}
	}
}

void FileMaker::CopyFileManual()
{

	string dateiname;
	string dateiname2;
	cout << "Quelldatei? ";
	cin >> dateiname;
	ifstream quelle(dateiname, ios::binary);  // Objekt für die Eingangsdatei

	const char * c = dateiname.c_str();
	cout << "Byte: " << FileMaker::getFileSize(c) << " KiloByte: " << (float)FileMaker::getFileSize(c) / 1024 << endl;

	if (!quelle.good()) {  // Fehlerabfrage
		cerr << dateiname << " kann nicht geöffnet werden!\n";
		exit(-1);
	}

	cout << "Zieldatei? ";
	cin >> dateiname2;
	// Definieren und Öffnen der Ausgabedatei
	ofstream ziel(dateiname2, ios::binary);
	if (!ziel.good()) {  // Fehlerabfrage
		cerr << dateiname2 << " kann nicht geöffnet werden!\n";
		exit(-1);
	}

	const char * cc = dateiname2.c_str();
	cout << "Byte: " << FileMaker::getFileSize(cc) << " KiloByte: " << (float)FileMaker::getFileSize(cc) / 1024 << endl;

	char ch;
	while (quelle.get(ch)) {
		ziel.put(ch);  // zeichenweise kopieren
	}






	quelle.close();
	ziel.close();
	cout << "Datei kopiert";

}

void FileMaker::PrintAsHexa(string & example)
{
	unsigned int size = example.length();
	char buffer;
	const string codierung{ "0123456789ABCDEF" };
	int count = 0;
	// 2 stellig ausgeben
	//cout << codierung.at(zahl / 16) << codierung.at(zahl % 16) << ' ';


	for (int i = 0; i < size; i++) {

		unsigned char uc = static_cast<unsigned char>(example.at(i));
		unsigned int zahl = static_cast<unsigned int>(uc);
		int zahl2 = static_cast<int>(uc);
		buffer = example.at(i);
		cout << "Normal: " << buffer << " static cast char: " << uc << endl << " static cast uint: " << zahl << " static cast int: " << zahl2;
		// 2 stellig ausgeben
		cout << " hexa: " << codierung.at(zahl / 16) << codierung.at(zahl % 16) << endl;

		//if (++count % 20 == 0)cout << '\n';


	}

}

std::ifstream::pos_type FileMaker::getFileSize(const char * filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

void FileMaker::createBinaryFileAlternate(std::vector<unsigned char>& binaryCharVec, string outputfilename)
{

	ofstream ziel;
	ziel.open(outputfilename, ios::binary);
	if (!ziel)
	{
		cerr << "binary file creating failed" << endl;
	}

	ziel.write(reinterpret_cast<const char*>(binaryCharVec[0]), binaryCharVec.size());
	ziel.close();
}

//aus der binäaren datei mit anzahl bilder + etc
//wird hier zerlegt und als string vector zurückgegeben
//bzw ´jeder string ist ein bild hat aber in der regel in den ersten
//30 bytes den namen der jeweiligen textur.
std::vector<vector<unsigned char>> FileMaker::readBinaryCharVecToStringV(vector<unsigned char> &v)
{
	uint32_t ImageCount = GetFirstBytesBinaryVecAsInt(v);//3
	cout << "imagecount: " << ImageCount << endl;
	vector<uint32_t> ImageSizes;//ich könnte hier schon den std map laden und mit 
	//der funktion die die ersten 30 zeichen abscheneidet den namen speichern aber ich mach erstmal char vector :D

	vector<vector<unsigned char>> bilder;
	
	int count = 0;
	MyBytes mb;
	std::vector<unsigned char>::iterator it = v.begin() + 4;


	//ein byte mehr lesen damit if trifft
	//holt die bild groessen
	
	for (; it != v.begin() + 4*ImageCount+5; it++)
	{
		if (count / 4 == 1) {
			count = 0;	
			cout << "bytes reset byte: "<< mb.getBytesAsInt() << endl;
			ImageSizes.push_back(mb.getBytesAsInt());
			mb.reset();
		}

		mb.setBytes(*it, count);
		count++;

	}
	cout << "anzahl bilder: " << ImageSizes.size() << endl;

		//wir überspringen den ersten int und die ints der bilderbytes und
	//fangen direkt bei den bilderchar arrays ab
		it = v.begin() + 4 * ImageCount +4;
		int index = std::distance(v.begin(), it);
		cout << "startposition: " << index << endl;

		int position = 0;
		int currentPicture = 0;
		count = 0;
		vector<unsigned char> buffer;
		for (; it != v.end() ; it++)
		{

			//cout << "buchstabe: " << *it << endl;
			buffer.push_back(*it);
			count++;
			
		//beim letzten biuld trifft das if nicht ein weil for shcleife zu ende
			if (count == ImageSizes[currentPicture])
			{
				bilder.push_back(buffer);
				count = 0;
				currentPicture++;
				cout << "bild fertig, wird in charvecreingemacht vectorsize:" << buffer.size() << endl;
				buffer.clear();	

			}
			
		}

	return bilder;
}

std::map<string, sf::Texture> FileMaker::getBinaryFileAsMap(vector<vector<unsigned char>>& v)
{


	std::map<string, sf::Texture> resourceMap;
	auto it = v.begin();
	std::vector<unsigned char> buffer;
	sf::Texture texBuffer;


	for (; it != v.end(); it++) {

		buffer = *it;
		string s(cutVector(buffer));
		string name = getNamefromCuttedVector(s);
		texBuffer.loadFromMemory(&buffer[0], buffer.size());
		//texBuffer.setSmooth(0);
		resourceMap[name] = texBuffer;
		//printf("name der in map gesp texture : %s", name);
		//printf("groesse des bildvectors: %d", buffer.size());
		
	}
	
	

	return resourceMap;
}

/*
std::vector<unsigned char>::iterator it = v.begin() + 4;

	for (; it != v.begin() + 4*ImageCount+4; it++)
	{
		BytesImageSizes.push_back(*it);

	}


____
std::vector<unsigned char>::iterator it = v.begin()+4;

	for (; it !=v.end(); it++)
	{

	}
*/
//diese funktion baut aus einem vector mit bilder strings,
//egal ob name im string oder nicht, eine binäre datei
//bei der man die ersten 4 bytes lesen kann und sieht wieviel bilder
//vorhanden sind, dann kommen die großen der strings
std::vector<unsigned char>  FileMaker::CreateBinaryVecReadyToPrint(vector<string>& v)
{
	vector<int> stringsizes; //groesse der einzelnen bilder + 30 namebuffer
	int imagecount = v.size(); //anzahl der tatsächlinen bilder
	cout << "Imagecount: " << imagecount << endl;
	std::vector<string>::iterator it = v.begin();

	for (; it != v.end(); it++)
	{
		//get lenghtss of strings for each pic
		stringsizes.push_back(it->length());
	}

	vector<unsigned char> finalBinaryVec;
	it = v.begin();


	for (; it != v.end(); it++)
	{	//char array bild string wird geholt und einzeln in char vec reingescshr
		string s = *it;
		int size = s.length();
		for (int i = 0; i < size; i++) {
		
			finalBinaryVec.push_back(s[i]);
		}

	}

	//danach die char array größen mit jeweils 4 bytes an anfang der datei
	//scxhreiben
	for (int i = stringsizes.size()-1; i > -1; i--) {

		unsigned int x = stringsizes[i];
		unsigned char bytes[sizeof x];
		std::copy(static_cast<const unsigned char*>(static_cast<const void*>(&x)),
			static_cast<const unsigned char*>(static_cast<const void*>(&x)) + sizeof x,
			bytes);
		for (int j = 0; j < 4; j++) {
		
			finalBinaryVec.insert(finalBinaryVec.begin(),bytes[j]);
		}


	}

	

	    unsigned int x = imagecount;
		unsigned char bytes[sizeof x];
		std::copy(static_cast<const unsigned char*>(static_cast<const void*>(&x)),
			static_cast<const unsigned char*>(static_cast<const void*>(&x)) + sizeof x,
			bytes);

		for (int j = 0; j < 4; j++) {

			finalBinaryVec.insert(finalBinaryVec.begin(), bytes[j]);
		}

	


		return finalBinaryVec;
	//vector string erstellen + name und zaehlen wieviel drin sind


}

void FileMaker::PrintIntToBytes(int i)
{
	const string codierung{ "0123456789ABCDEF" };
	string buffer = "";

	int x =i;
	cout << "sizeof i: " << sizeof(i) << endl;
	unsigned char bytes[sizeof x];
	std::copy(static_cast<const unsigned char*>(static_cast<const void*>(&x)),
		static_cast<const unsigned char*>(static_cast<const void*>(&x)) + sizeof x,
		bytes);

	cout << "Zahl: " << i << " als Hexa: ";
	for (int i = 3; i > -1; i--)
	{
	unsigned int zahl = static_cast<unsigned int>(bytes[i]);
	cout << codierung.at(zahl / 16) << codierung.at(zahl % 16) << " ";
	buffer += codierung.at(zahl / 16);
	buffer += codierung.at(zahl % 16);
	buffer += " ";

	}
	
	cout << endl;
	//return buffer;


}

uint32_t FileMaker::GetFirstBytesFromFile(string filename)
{
	//memblock wird eigentlich nicht gebraucht
	streampos size;
	char * memblock = nullptr;
	uint32_t myint = 0;
	vector<unsigned char> buffer;

	ifstream file(filename, ios::in | ios::binary | ios::ate);
	if (file.is_open())
	{

		size = file.tellg();
		memblock = new  char[size];
		cout << "datei hat " << size << " Bytes " << endl;
		//ByteImageCount = new char[1];
		file.seekg(0, ios::beg);
		file.read(reinterpret_cast<char*>(&myint), sizeof(uint32_t));
		//file.read(ByteImageCount, 1);
		file.read(memblock, size);
		file.close();
		cout << "the entire file content is in memory";
	}
	else cout << "Unable to open file";
	cout << "das war anzahl an bildern in der datei: " << myint << endl;

	buffer.push_back(memblock[0]);
	buffer.push_back(memblock[1]);
	buffer.push_back(memblock[2]);
	buffer.push_back(memblock[3]);
	GetFirstBytesBinaryVecAsInt(buffer);

	if (memblock != nullptr)delete[] memblock;
	return myint;
}

uint32_t FileMaker::GetFirstBytesBinaryVecAsInt(vector<unsigned char>& v)
{
	const string codierung{ "0123456789ABCDEF" };
	unsigned char code[4];
	uint32_t foo;
	code[0] = v.at(0);
	code[1] = v.at(1);
	code[2] = v.at(2);
	code[3] = v.at(3);

	//macht nicht viel sind da werte nicht 
	cout << "eingehende bytes: " << code[0] << ":" << code[1] << ":" << code[2] << ":" << code[3] << endl;

	foo = (uint32_t)code[0] << 24;
	foo |= (uint32_t)code[1] << 16;
	foo |= (uint32_t)code[2] << 8;
	foo |= (uint32_t)code[3];
	
	PrintIntToBytes(foo);

	return foo;


}



std::vector<unsigned char> FileMaker::getBytesFromFile(std::string path, bool print)
{

	string Quelldateiname = path;
	std::streampos fileSize;
	std::ifstream file(Quelldateiname, std::ios::binary);


	file.seekg(0, std::ios::end);
	fileSize = file.tellg(); //tellg = getsize in bytes
	file.seekg(0, std::ios::beg);

	// read the data:
	std::vector<unsigned char> fileData(fileSize);
	file.read((char*)&fileData[0], fileSize);

	

	(print) ? printVector(fileData) : printf("Bild Geladen!");


	return fileData;
}

std::vector<char> FileMaker::ReadFile(const char * pngfilename)
{
	vector<char> k;

	std::ifstream texture_file{ pngfilename, std::ifstream::binary };
	std::vector<char> buffer;
	if (texture_file) {
		// get length of file:
		texture_file.seekg(0, texture_file.end);
		const auto length = texture_file.tellg();
		if (!length) {
			std::cerr << "Cannot load zero byte texture file" << std::endl;
			return k;
		}
		buffer.resize(length); // reserve space

		texture_file.seekg(0, texture_file.beg);

		auto start = &*buffer.begin();
		texture_file.read(start, length);
		texture_file.close();
	}
	else {
		std::cerr << "Could not open texture file" << std::endl;
		return k;
	}

	return buffer;
}

bool FileMaker::printVector(vector<unsigned char> &v, int flag)
{
	const string codierung{ "0123456789ABCDEF" };
	unsigned int seiteneffekt=0;

	if(v.size() < 1)
	{
		cerr << "Vector leer!\n";
		return false;
	}

	for (std::vector<unsigned char>::iterator it = v.begin(); it != v.end(); ++it) {
		std::cout <<"Uchar: " <<  *it << " Hexa: ";
		unsigned int zahl = static_cast<unsigned int>(*it);
		
		cout << codierung.at(zahl / 16) << codierung.at(zahl % 16) << " ";

		if (++seiteneffekt % 10 == 0) {	cout << '\n';}

	}

	return true;
}


/*
'verstädnliches bsp

unsigned char bytes[4];
unsigned long n = 1024;

bytes[0] = (n >> 24) & 0xFF;
bytes[1] = (n >> 16) & 0xFF;
bytes[2] = (n >> 8) & 0xFF;
bytes[3] = n & 0xFF;

printf("%x %x %x %x\n", bytes[0], bytes[1], bytes[2], bytes[3]);


int num = 0;
for(int i = 0; i < 4; i++)
 {
 num <<= 8;
 num |= bytes[i];
 }


printf("number %d",num);
*/










/*
	if (currentPicture > ImageSizes.size())
			{
				cout << "currenpicture: " << currentPicture << "ImagesSizes:" << ImageSizes.size() << endl;
				cout << "rausgebreakt" << endl;
				break;
			}


	for (; it != v.end() ; it++)
		{

			cout << "buchstabe: " << *it << endl;
			if (currentPicture > ImageSizes.size())
			{
				cout << "currenpicture: " << currentPicture << "ImagesSizes:" << ImageSizes.size() << endl;
				cout << "rausgebreakt" << endl;
				break;
			}

			if (count < ImageSizes[currentPicture])
			{
				buffer.push_back(*it);
				cout << "byte reingemacht: " << *it << endl;
				count++;

			}
			else if (count == ImageSizes[currentPicture])
			{
				bilder.push_back(buffer);
				count = 0;
				currentPicture++;
				cout << "bild fertig, wird in charvecreingemacht vectorsize:" << buffer.size() << endl;
				buffer.clear();


			}
			//cout << "schleifenzaehler: " << schleifenzaehler++ << "kacki: " << v.size() << endl;

		}

*/

















/*

		//beim letzten biuld trifft das if nicht ein weil for shcleife zu ende
			if (count == ImageSizes[currentPicture])
			{
				bilder.push_back(buffer);
				count = 0;
				currentPicture++;
				cout << "bild fertig, wird in charvecreingemacht vectorsize:" << buffer.size() << endl;
				buffer.clear();


			}

			cout << "buchstabe: " << *it << endl;
			buffer.push_back(*it);


			count++;

*/
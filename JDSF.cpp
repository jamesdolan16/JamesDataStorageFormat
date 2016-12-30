/*
Title: JDSF( James' Data Storage Format )
Author(s): James Dolan
Build: 1.0.0
lastRevision: 30/12/16

***TODO***
		[]-Integrate a packing process for monotype data files.
			[x]-Develop prototype process for ints.
*/

#include <string>
#include <iostream>
#include <fstream>
//#include <map>
//#include <vector>

#include "JDSF.h"

JDSF::JDSF(std::string fileName)
{
	JDSF::iofile = fileName;
	fileContents = openFile(fileName);
}


JDSF::~JDSF()
{
}

std::map<std::string, int> JDSF::unpack()
{
	std::map<std::string, int> unpacked;
	fileData = tokenise(fileContents);
	unpacked = lexInt(fileData);

	return unpacked;
}

std::map<std::string, char> JDSF::unpackChar()
{
	std::map<std::string, char> unpacked;
	fileData = tokenise(fileContents);
	unpacked = lexChar(fileData);

	return unpacked;
}

std::map<std::string, std::string> JDSF::unpackString()
{
	std::map<std::string, std::string> unpacked;
	fileData = tokenise(fileContents);
	unpacked = lexString(fileData);
	return unpacked;
}

std::map<std::string, bool> JDSF::unpackBool()
{
	std::map<std::string, bool> unpacked;
	fileData = tokenise(fileContents);
	unpacked = lexBool(fileData);
	return unpacked;
}

std::map<std::string, float> JDSF::unpackFloat()
{
	std::map<std::string, float> unpacked;
	fileData = tokenise(fileContents);
	unpacked = lexFloat(fileData);
	return unpacked;
}

void JDSF::pack(std::map<std::string, int> toPack)
{
	std::ofstream file(iofile);
	for (const auto &element : toPack)
	{
		file << element.first << ":" << element.second << ";\n";
	}
}

void JDSF::pack(std::map<std::string, char> toPack)
{
	std::ofstream file(iofile);
	for (const auto &element : toPack)
	{
		file << element.first << ":" << element.second << ";\n";
	}
}

void JDSF::pack(std::map<std::string, std::string> toPack)
{
	std::ofstream file(iofile);
	for (const auto &element : toPack)
	{
		file << element.first << ":" << element.second << ";\n";
	}
}

void JDSF::pack(std::map<std::string, bool> toPack)
{
	std::ofstream file(iofile);
	for (const auto &element : toPack)
	{
		file << element.first << ":" << element.second << ";\n";
	}
}

void JDSF::pack(std::map<std::string, float> toPack)
{
	std::ofstream file(iofile);
	for (const auto &element : toPack)
	{
		file << element.first << ":" << element.second << ";\n";
	}
}


std::vector<std::string> JDSF::tokenise(std::string toTokenise)
{
	std::vector<std::string> tokenised;
	std::string token;
	bool isString = false;
	for (char i : toTokenise)
	{
		switch (i)
		{
		case '"':
			if (isString)
			{
				isString = false;
			}
			else
			{
				isString = true;
			}
			break;

		case ' ':
			if (isString)
			{
				continue;
			}
			else
			{
				break;
			}
			break;
		case ':':
			if (isString)
			{
				continue;
			}
			else
			{
				tokenised.push_back(token);
				token.clear();
				break;
			}
			
		case ';':
			if (isString)
			{
				continue;
			}
			else
			{
				tokenised.push_back(token);
				token.clear();
				break;
			}
		default:
			token.push_back(i);
		}
		/*std::cout << "i = " << i << std::endl << "token = " << token << std::endl << "tokenised = ";
		for (std::string tok : tokenised) { std::cout << tok << " "; }
		std::cout << std::endl;//*/
	}
	return tokenised;
}

std::map<std::string, int> JDSF::lexInt(std::vector<std::string> toLex)
{
	bool isValue = false;
	int it = 0;
	std::string curTok;

	/*std::cout << "toLex: ";
	for (std::string tok : toLex) { std::cout << tok << " "; }
	std::cout << std::endl;//*/

	std::map<std::string, int> mappedDataInt;
	std::pair<std::string, int> curDataInt;

	for (auto i = begin(toLex); i != end(toLex); ++i)
	{

		curTok = toLex[it];
		if (!isValue) //key
		{
			curDataInt.first = curTok;
			mappedDataInt.insert(curDataInt);
			isValue = true;
		}

		else //value
		{
			try
			{
				mappedDataInt[curDataInt.first] = std::stol(curTok);

			}
			catch (std::invalid_argument)
			{
				std::cout << "Value is not of type, set " << mappedDataInt[curDataInt.first] << " to default value." << std::endl;
				break;

			}

			isValue = false;
		}

		it++;
	}

	return mappedDataInt;
}

std::map<std::string, char> JDSF::lexChar(std::vector<std::string> toLex)
{
	bool isValue = false;
	int it = 0;
	std::string curTok;

	/*std::cout << "toLex: ";
	for (std::string tok : toLex) { std::cout << tok << " "; }
	std::cout << std::endl;//*/

	std::map<std::string, char> mappedData;
	std::pair<std::string, char> curData;

	for (auto i = begin(toLex); i != end(toLex); ++i)
	{

		curTok = toLex[it];
		if (!isValue) //key
		{
			curData.first = curTok;
			mappedData.insert(curData);
			isValue = true;
		}

		else //value
		{
			try
			{
				mappedData[curData.first] = curTok[0];

			}
			catch (std::invalid_argument)
			{
				std::cout << "Value is not of type Char, set " << mappedData[curData.first] << " to default value." << std::endl;
				break;


			}

			isValue = false;
		}

		it++;
	}

	return mappedData;

}

std::map<std::string, std::string> JDSF::lexString(std::vector<std::string> toLex)
{
	bool isValue = false;
	int it = 0;
	std::string curTok;

	/*std::cout << "toLex: ";
	for (std::string tok : toLex) { std::cout << tok << " "; }
	std::cout << std::endl;//*/

	std::map<std::string, std::string> mappedData;
	std::pair<std::string, std::string> curData;

	for (auto i = begin(toLex); i != end(toLex); ++i)
	{

		curTok = toLex[it];
		if (!isValue) //key
		{
			curData.first = curTok;
			mappedData.insert(curData);
			isValue = true;
		}

		else //value
		{
			try
			{
				mappedData[curData.first] = curTok;

			}
			catch (std::invalid_argument)
			{
				std::cout << "Value is not of type string, set " << mappedData[curData.first] << " to default value." << std::endl;
				break;


			}

			isValue = false;
		}

		it++;
	}

	return mappedData;
}

std::map<std::string, bool> JDSF::lexBool(std::vector<std::string> toLex)
{
	bool isValue = false;
	int it = 0;
	std::string curTok;

	/*std::cout << "toLex: ";
	for (std::string tok : toLex) { std::cout << tok << " "; }
	std::cout << std::endl;//*/

	std::map<std::string, bool> mappedData;
	std::pair<std::string, bool> curData;

	for (auto i = begin(toLex); i != end(toLex); ++i)
	{

		curTok = toLex[it];
		if (!isValue) //key
		{
			curData.first = curTok;
			mappedData.insert(curData);
			isValue = true;
		}

		else //value
		{
			try
			{
				mappedData[curData.first] = stoi(curTok);

			}
			catch (std::invalid_argument)
			{
				std::cout << "Value is not of type bool, set " << mappedData[curData.first] << " to default value." << std::endl;
				break;


			}

			isValue = false;
		}

		it++;
	}

	return mappedData;
}

std::map<std::string, float> JDSF::lexFloat(std::vector<std::string> toLex)
{
	bool isValue = false;
	int it = 0;
	std::string curTok;

	/*std::cout << "toLex: ";
	for (std::string tok : toLex) { std::cout << tok << " "; }
	std::cout << std::endl;//*/

	std::map<std::string, float> mappedData;
	std::pair<std::string, float> curData;

	for (auto i = begin(toLex); i != end(toLex); ++i)
	{

		curTok = toLex[it];
		if (!isValue) //key
		{
			curData.first = curTok;
			mappedData.insert(curData);
			isValue = true;
		}

		else //value
		{
			try
			{
				mappedData[curData.first] = stof(curTok);

			}
			catch (std::invalid_argument)
			{
				std::cout << "Value is not of type float, set " << mappedData[curData.first] << " to default value." << std::endl;
				break;


			}

			isValue = false;
		}

		it++;
	}

	return mappedData;
}

std::string JDSF::openFile(std::string fileToOpen)
{
	std::string lines;
	std::string line;
	std::ifstream file(fileToOpen);

	if (file.is_open()) {

		while (std::getline(file, line)) {
			/*std::cout << "Line: " << line << std::endl;
			std::cout << "All: " << lines << std::endl;
			//*/
			lines += line;
			line.clear();
		}
	}

	return lines;
}
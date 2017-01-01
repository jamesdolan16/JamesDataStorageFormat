#pragma once
#include <vector>
#include <map>

class JDSF
{
public:
	JDSF(std::string fileName);
	~JDSF();
	std::map<std::string, int> unpack();
	std::map<std::string, char> unpackChar();
	std::map<std::string, std::string> unpackString();
	std::map<std::string, bool> unpackBool();
	std::map<std::string, float> unpackFloat();

	//Pack function and its type overloads
	void pack(std::map<std::string, int> toPack);
	void pack(std::map<std::string, char> toPack);
	void pack(std::map<std::string, std::string> toPack);
	void pack(std::map<std::string, bool> toPack);
	void pack(std::map<std::string, float> toPack);

private:
	std::vector<std::string> tokenise(std::string toTokenise);
	std::map<std::string, int> lexInt(std::vector<std::string> toLex);
	std::map<std::string, char> lexChar(std::vector<std::string> toLex);
	std::map<std::string, std::string> lexString(std::vector<std::string> toLex);
	std::map<std::string, bool> lexBool(std::vector<std::string> toLex);
	std::map<std::string, float> lexFloat(std::vector<std::string> toLex);
	std::string fileContents;
	std::vector<std::string> fileData;
	std::string openFile(std::string fileToOpen);
	std::string iofile;
};
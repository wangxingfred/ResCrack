
#ifndef __INCLUDE_PACKPARSER_H__
#define __INCLUDE_PACKPARSER_H__

#include "BinFile.h"

enum ParseType
{
	XML,
	PNG
};

class PackParser
{
public:
	PackParser();
	~PackParser();

	ParseError parse(BinFile &binFile);
	ParseError saveToFile(char *pStart, std::size_t size, std::string name);

	ParseError bytesOperation(BinFile &binFile);

private:
	ParseError parseXML(char **ppStart, char **ppEnd, std::string id);
	ParseError parsePNG(char **ppStart, char **ppEnd, std::string id);
	ParseError parseJPG(char **ppStart, char **ppEnd, std::string id);

	ParseError parseEXIF(char **ppStart, char **ppEnd, std::string id);
	ParseError parseJFIF(char **ppStart, char **ppEnd, std::string id);

	ParseError parseJPG(char **ppStart, char **ppEnd, const char *HEAD, const size_t HEAD_LEN,
		const char *TAIL, const size_t TAIL_LEN, std::string id);

	ParseError searchStr(char **ppStart, char **ppEnd, const char *pStr, const int strSize);
};

#endif
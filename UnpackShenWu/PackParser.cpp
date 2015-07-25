#include "PackParser.h"
#include "Util.h"
#include <sstream>
#include <iostream>

PackParser::PackParser()
{
}

PackParser::~PackParser()
{
}

ParseError PackParser::parse(BinFile &binFile)
{
	if (binFile.size() <= 0) {
		return E_FILE_EMPTY;
	}

	std::size_t i = 0;
	ParseType currType = XML;

	char *pStart = (char *)binFile.getData();
	char *pEnd = pStart + binFile.size();

	bool goon = true;
	char str[20];

	ParseError error = E_SUCCESS;
	while (error == E_SUCCESS) {
		int num = Util::getInstance()->getUniqueInt();

		itoa(num, str, 10);
		std::string id(str);
		id = "exif\\" + id;

		error = parseEXIF(&pStart, &pEnd, id);
		//if (error == E_SUCCESS) {
		//	error = parsePNG(&pStart, &pEnd, id);
		//}
	}

	return error;
}

ParseError PackParser::saveToFile(char *pStart, std::size_t size, std::string name)
{
	FILE *pFile = fopen(name.c_str(), "wb");
	
	if (pFile == NULL) {
		Util::getInstance()->setLastError(name);
		return E_FILE_CREATE_FAILED;
	}

	fwrite(pStart, 1, size, pFile);
	fclose(pFile);

	return E_SUCCESS;
}

ParseError PackParser::bytesOperation( BinFile &binFile )
{
	if (binFile.size() <= 0) {
		return E_FILE_EMPTY;
	}

	std::size_t i = 0;

	char* const pStart = (char *)binFile.getData();
	char* const pEnd = pStart + binFile.size();
	char* pMove = pStart;

	while (pMove < pEnd) {
		*pMove = 0xFF - *pMove;
		++pMove;
	}

	std::string name = std::string(binFile.name());
	size_t pos = name.find_last_of(".");
	name = name.substr(0, pos).append("pkm");

	saveToFile(pStart, binFile.size(), name);
	return E_SUCCESS;
}

ParseError PackParser::parseXML(char **ppStart, char **ppEnd, std::string id) 
{
	std::size_t size = 0;

	const char XML_HEAD[] = "<?xml";
	const size_t XML_HEAD_LEN = 5;

	const char XML_TAIL[] = "</plist>";
	const size_t XML_TAIL_LEN = 8;

	if (searchStr(ppStart, ppEnd, XML_HEAD, XML_HEAD_LEN) != E_SUCCESS) {
		return E_XML_HEAD_NOT_FOUND;
	}

	char *pStartPos = *ppStart;

	if (searchStr(ppStart, ppEnd, XML_TAIL, XML_TAIL_LEN) != E_SUCCESS) {
		return E_XML_TAIL_NOT_FOUND;
	}

	char *pEndPos = (*ppStart) + XML_TAIL_LEN;
	size = pEndPos - pStartPos;

	std::string name = id + ".plist";
	saveToFile(pStartPos, size, name);

	return E_SUCCESS;
}

ParseError PackParser::parsePNG(char **ppStart, char **ppEnd, std::string id) 
{
	std::size_t size = 0;

	const char PNG_HEAD[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
	const size_t PNG_HEAD_LEN = 8;

	const char PNG_TAIL[] = {0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82};
	const size_t PNG_TAIL_LEN = 8;

	if (searchStr(ppStart, ppEnd, PNG_HEAD, PNG_HEAD_LEN) != E_SUCCESS) {
		return E_PNG_HEAD_NOT_FOUND;
	}

	char *pStartPos = *ppStart;

	if (searchStr(ppStart, ppEnd, PNG_TAIL, PNG_TAIL_LEN) != E_SUCCESS) {
		return E_PNG_TAIL_NOT_FOUND;
	}

	char *pEndPos = (*ppStart) + PNG_TAIL_LEN;
	size = pEndPos - pStartPos;

	std::string name = id + ".png";
	saveToFile(pStartPos, size, name);

	return E_SUCCESS;
}

ParseError PackParser::parseEXIF(char **ppStart, char **ppEnd, std::string id)
{
	const char EXIF_HEAD[] = {0xFF, 0xD8, 0xFF, 0xE1, 0x00, 0x18, 0x45, 0x78, 0x69, 0x66};
	const size_t EXIF_HEAD_LEN = 10;

	const char EXIF_TAIL[] = {0xFF, 0xD9};
	const size_t EXIF_TAIL_LEN = 2;

	return parseJPG(ppStart, ppEnd, EXIF_HEAD, EXIF_HEAD_LEN, EXIF_TAIL, EXIF_TAIL_LEN, id);
}

ParseError PackParser::parseJFIF(char **ppStart, char **ppEnd, std::string id)
{
	const char JFIF_HEAD[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46, 0x49, 0x46};
	const size_t JFIF_HEAD_LEN = 10;

	const char JFIF_TAIL[] = {0xFF, 0xD9};
	const size_t JFIF_TAIL_LEN = 2;

	return parseJPG(ppStart, ppEnd, JFIF_HEAD, JFIF_HEAD_LEN, JFIF_TAIL, JFIF_TAIL_LEN, id);
}

ParseError PackParser::parseJPG(char **ppStart, char **ppEnd, std::string id)
{
	const char JPG_HEAD[] = {0xFF, 0xD8};
	const size_t JPG_HEAD_LEN = 2;

	const char JPG_TAIL[] = {0xFF, 0xD9};
	const size_t JPG_TAIL_LEN = 2;

	return parseJPG(ppStart, ppEnd, JPG_HEAD, JPG_HEAD_LEN, JPG_TAIL, JPG_TAIL_LEN, id);
}

ParseError PackParser::parseJPG(char **ppStart, char **ppEnd, 
								const char *HEAD, const size_t HEAD_LEN,
								const char *TAIL, const size_t TAIL_LEN,
								std::string id) 
{
	std::size_t size = 0;

	if (searchStr(ppStart, ppEnd, HEAD, HEAD_LEN) != E_SUCCESS) {
		return E_PNG_HEAD_NOT_FOUND;
	}

	char *pStartPos = *ppStart;

	if (searchStr(ppStart, ppEnd, TAIL, TAIL_LEN) != E_SUCCESS) {
		return E_PNG_TAIL_NOT_FOUND;
	}

	char *pEndPos = (*ppStart) + TAIL_LEN;
	size = pEndPos - pStartPos;

	std::string name = id + ".jpg";
	saveToFile(pStartPos, size, name);

	return E_SUCCESS;
}

ParseError PackParser::searchStr(char **ppStart, char **ppEnd, const char *pStr, const int strSize)
{
	char *pStart = *ppStart;
	char *pEnd = *ppEnd;
	char *pMove = pStart;

	int index = 0;
	bool bingo = false;
	int count = 0;

	int max = 20;

	do {
		++count;
		//if (count <= 20) {
		//	std::cout << index << " " << *pMove << " " << pStr[index] << std::endl;
		//}

		// 判断是否匹配
		if (*pMove == pStr[index]) {
			if (index == 0) {
				// 匹配第一个，则记录开始位置
				pStart = pMove;
			} else if (index == strSize - 1) {
				// 匹配最后一个，则找到
				bingo = true;
			}

			++index;
		} else {
			// 不匹配则从头匹配
			index = 0;
		}
	} while (!bingo && ++pMove != pEnd);

	if (!bingo) {
		//std::cout << "head not found: count = " << count << std::endl;
		return E_STRING_NOT_FOUND;
	}

	// 保存开始位置
	*ppStart = pStart;
	return E_SUCCESS;
}

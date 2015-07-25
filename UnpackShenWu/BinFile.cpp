
#include "BinFile.h"
#include <sys/stat.h>
#include <iostream>

BinFile::BinFile(std::string &filename)
	: pData(NULL), fileSize(0), fileName(filename)
{
	struct stat fStat;

	if (stat(filename.c_str(), &fStat) == -1){
		isExist = false;
		return;
	}

	isExist = true;
	fileSize = fStat.st_size;
}

BinFile::~BinFile()
{
	if (pData) delete pData;
}

ParseError BinFile::load()
{
	FILE *pFile = NULL;
	std::size_t size;
	std::size_t result;

	// 1.���ļ�
	pFile = fopen(fileName.c_str(), "rb");
	if (pFile == NULL) {
		return E_FILE_NOT_EXIST;
	}

	// 2.��ȡ�ļ���С
	fseek(pFile, 0, SEEK_END);
	size = ftell(pFile);
	rewind(pFile);
	if (size == 0) {
		fclose(pFile);
		return E_FILE_EMPTY;
	}

	// 3.�����ڴ�
	pData = new char[size];
	if (pData == NULL) {
		fclose(pFile);
		return E_MEM_LOC_FAILED;
	}

	// 4.��ȡ�ļ����ڴ���
	result = fread(pData, 1, size, pFile);
	if (result != size) {
		fclose(pFile);
		SAFE_RELEASE(pData);
		return E_READ_INCOMPELETE;
	}
	fileSize = result;

	return E_SUCCESS;
}
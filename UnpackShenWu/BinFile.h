#ifndef __INCLUDE_BINFILE_H__
#define __INCLUDE_BINFILE_H__

#include <string>
#include "error.h"
#include "comm.h"
#include "util.h"

class BinFile
{
public:
	BinFile(std::string &);
	~BinFile();

	ParseError load();

	void *getData() { return pData; }

	bool exist() { return isExist; }
	std::size_t size() const { return fileSize; }
	const std::string& name() const { return fileName; }

private:
	void *pData;
	std::size_t fileSize;
	std::string fileName;
	bool isExist;
};

#endif
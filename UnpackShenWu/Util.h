
#ifndef __INCLUDE_UTIL_H__
#define __INCLUDE_UTIL_H__

#include <string>

class Util
{
public:

	static Util *getInstance();

	int getUniqueInt();

	std::string getLastError() const;
	void setLastError(std::string);
	
private:
	Util();
	~Util();

	int uInt;
	std::string lastError;
	static Util* pInstance;
};

#endif
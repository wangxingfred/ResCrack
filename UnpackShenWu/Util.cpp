
#include "Util.h"

Util::Util()
	:uInt(0)
{

}

Util::~Util()
{

}

Util* Util::getInstance()
{
	if (pInstance == NULL) {
		pInstance = new Util();
	}

	return pInstance;
}

int Util::getUniqueInt()
{
	return uInt++;	
}

std::string Util::getLastError() const
{
	return lastError;
}

void Util::setLastError(std::string error)
{
	lastError = error;
}

Util* Util::pInstance = NULL;
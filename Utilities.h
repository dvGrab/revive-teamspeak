#ifndef UTILITIES_H
#define UTILITIES_H

#include "Main.h"

class CUtilities {
public:
	std::wstring ConvertCharToWChar(const std::string& str);
};

extern CUtilities* Utilities;

#endif
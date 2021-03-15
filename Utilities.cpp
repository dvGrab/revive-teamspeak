#include "Utilities.h"

std::wstring CUtilities::ConvertCharToWChar(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.from_bytes(str);
}


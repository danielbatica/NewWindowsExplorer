#include "FileApiUtils.h"
#include <string>

using namespace WFind;
DWORD FileApiUtils::GetFullPathForStartingPoint(const WCHAR* startingPoint, LPWSTR* fullPath)
{
	*fullPath = new TCHAR[MAX_PATH];
	DWORD res = GetFullPathName(startingPoint, MAX_PATH, *fullPath, nullptr);

	return res;
}

void WFind::FileApiUtils::GetParrentForFolder(const WCHAR* fullPath, WCHAR** result)
{
	std::wstring string = std::wstring(fullPath);
	size_t lastSlash = string.rfind(FU_FOLDER_ENDING_CHARACTER);
	if (lastSlash > 0) {
		size_t len = wcslen(fullPath);
		(*result) = new wchar_t[len + 1];
		wcscpy_s((*result), len+1, std::wstring(string.substr(0, lastSlash)).c_str());
	}
}

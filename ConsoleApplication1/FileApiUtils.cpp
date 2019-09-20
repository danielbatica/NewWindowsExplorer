#include "FileApiUtils.h"
#include <string>

using namespace WFind;
DWORD FileApiUtils::GetFullPathForStartingPoint(const WCHAR* startingPoint, LPWSTR* fullPath)
{
	*fullPath = new TCHAR[MAX_PATH];
	DWORD res = GetFullPathNameW(startingPoint, MAX_PATH, *fullPath, nullptr);
	//TODO: check for res

	// add slash if not present


	return res;
}

void FileApiUtils::GetParrentForFolder(const WCHAR* fullPath, WCHAR** result)
{
	std::wstring string = std::wstring(fullPath);
	size_t lastSlash = string.rfind(FU_FOLDER_ENDING_CHARACTER);
	if (lastSlash > 0) {
		size_t len = wcslen(fullPath);
		(*result) = new wchar_t[len + 1];
		wcscpy_s((*result), len+1, std::wstring(string.substr(0, lastSlash)).c_str());
	}
}

void FileApiUtils::AddEndingSlashToFolder(const WCHAR* fullPath, WCHAR** result)
{
	size_t len = wcslen(fullPath);

	if (fullPath[len] != FU_FOLDER_ENDING_CHARACTER) {
		return;
	}

	std::wstring string = std::wstring(fullPath);
	string += FU_FOLDER_ENDING_CHARACTER;

	(*result) = new wchar_t[len + 2]; // because of the slash
	wcscpy_s((*result), len + 2, string.c_str());
}

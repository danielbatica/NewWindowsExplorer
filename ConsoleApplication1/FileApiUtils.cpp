#include "FileApiUtils.h"

using namespace WFind;
DWORD FileApiUtils::GetFullPathForStartingPoint(const WCHAR* startingPoint, LPWSTR* fullPath)
{
	*fullPath = new TCHAR[MAX_PATH];
	DWORD res = GetFullPathName(startingPoint, MAX_PATH, *fullPath, nullptr);

	return res;
}
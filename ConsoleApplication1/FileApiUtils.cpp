#include "FileApiUtils.h"

DWORD FileApiUtils::GetFullPathForStartingPoint(const TCHAR* startingPoint, LPWSTR* fullPath)
{
	*fullPath = new TCHAR[MAX_PATH];
	TCHAR** lppPart = nullptr;
	DWORD res = GetFullPathName(startingPoint, MAX_PATH, *fullPath, lppPart);

	delete lppPart;

	return res;
}

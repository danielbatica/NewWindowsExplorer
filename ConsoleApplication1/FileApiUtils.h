#pragma once
#include <Windows.h>
#include <tchar.h>


class FileApiUtils
{
	public:
		static DWORD GetFullPathForStartingPoint(const TCHAR* startingPoint, LPWSTR* fullPath);
};


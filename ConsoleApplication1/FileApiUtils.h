#pragma once
#include <Windows.h>
#include <wchar.h>

static const WCHAR* FU_CURRENT_DIRECTORY = L".";
static const WCHAR* FU_UPPER_DIRECTORY = L"..";

static const WCHAR FU_ALL_FILES_WILDCARD_CHARACTER = '*';
static const WCHAR FU_FOLDER_ENDING_CHARACTER = '\\';


class FileApiUtils
{
	public:
		static DWORD GetFullPathForStartingPoint(const WCHAR* startingPoint, LPWSTR* fullPath);
};


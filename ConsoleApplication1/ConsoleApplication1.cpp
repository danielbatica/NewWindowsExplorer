// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <fileapi.h>
#include "FinderController.h"

//void testCallOfFindFileW(const TCHAR* startingPoint);
//DWORD getFullPathForStartingPoint(const TCHAR* startingPoint, LPWSTR* fullPath);

int main(int argc, const TCHAR* argv[])
{
	if (argc < 3) {
		std::cout << "Usage: find [starting-point] [expression]" << std::endl;
		return 0;
	}

#ifdef _DEBUG
	//const TCHAR startingPoint[] = L"C:\\Users\\labuser\\source\\repos\\ConsoleApplication1\\ConsoleApplication1";
	const TCHAR startingPoint[] = L"./";
	const TCHAR expression[] = L"\*";

	/*const TCHAR expression[] = L"ConsoleApplication1.cpp";*/
#else
	const TCHAR* startingPoint = argv[1];
	const TCHAR* expression = argv[2];
#endif // DEBUG

    std::cout << "Starting Point: " << startingPoint << std::endl;
	std::cout << "Expression : " << expression << std::endl;

	FinderController::sharedInstance()->startSearchingForFile(startingPoint, expression, nullptr);

	std::cout << "Done";
	/*LPWSTR fullPathStartingPoint = nullptr;
	DWORD result = getFullPathForStartingPoint(startingPoint, &fullPathStartingPoint);
	if (!result) {
		std::cout << "Could not get full Path from starting point";
		return 0;
	}
	
	std::wstring fullQuerry(fullPathStartingPoint);
	delete fullPathStartingPoint;

	fullQuerry.append(expression);
*/
	//testCallOfFindFileW(fullQuerry.c_str());

}

/*DWORD getFullPathForStartingPoint(const TCHAR* startingPoint, LPWSTR* fullPath)
{
	*fullPath = new TCHAR[MAX_PATH];
	TCHAR** lppPart = nullptr;
	DWORD res = GetFullPathName(startingPoint, MAX_PATH, *fullPath, lppPart);

	delete lppPart;

	return res;
}

size_t getStringFromCharStr(const char* cStr, LPWSTR* lpStr)
{
	size_t wordNr = 0;
	errno_t err = mbsrtowcs_s(&wordNr, NULL, 0, &cStr, 0, NULL);
	if (err == errno_t(-1)) {
		return -1;
	}
	wordNr = min(MAX_PATH, wordNr);
	*lpStr = new wchar_t[wordNr]();
	err = mbsrtowcs_s(&wordNr, *lpStr, wordNr, &cStr, wordNr, NULL);
	return wordNr;
}


void testCallOfFindFileW(const TCHAR* startingPoint)
{
	WIN32_FIND_DATA findFileData{0};
	HANDLE hForNext = FindFirstFileW(startingPoint, &findFileData);
	if (INVALID_HANDLE_VALUE != hForNext) {
		std::cout << "Found a file";
	}

	
	//PathMatchSpecW

	FindClose(hForNext);
} */
// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "windows.h"
#include <fileapi.h>
#include "FinderController.h"

int main(int argc, const WCHAR* argv[])
{
	if (argc < 3) {
		std::cout << "Usage: find [starting-point] [expression]" << std::endl;
		return 0;
	}

#ifdef _DEBUG
	//const TCHAR startingPoint[] = L"C:\\Users\\labuser\\source\\repos\\ConsoleApplication1\\ConsoleApplication1";
	//const TCHAR startingPoint[] = L"../../../../";
	const WCHAR startingPoint[] = L"C:/";
	
	const WCHAR expression[] = L"*.txt";

	/*const TCHAR expression[] = L"ConsoleApplication1.cpp";*/
#else
	const WCHAR startingPoint[] = L"C:/";
	const WCHAR expression[] = L"ConsoleApplication1";

	//const WCHAR* startingPoint = argv[1];
	//const WCHAR* expression = argv[2];
#endif // DEBUG

    std::wcout << "Starting Point: " << startingPoint << std::endl;
	std::wcout << "Expression : " << expression << std::endl;

	WFind::FinderController::sharedInstance()->startSearchingForFile(startingPoint, expression, nullptr);

}
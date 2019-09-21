// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "windows.h"
#include <fileapi.h>
#include "FinderController.h"
#include "FileSearchDelegate.h"

using namespace WFind;
class FinderDelegateImpl : public FileSearchDelegate {

public:
	///////// WFind::FileSearchDelegate impl
	void onFileFound(const WFind::FileSearchDelegateResult* result, const WFind::FileSearchDelegateError* error) override {
		if (error || !result) {
			//todo
			return;
		}
		std::wcout << result->fileName << std::endl;
		return;
	}

	void onSearchComplete(const WCHAR* expression) override {
		std::wcout << L"Finished search for: " << expression;
	}
};

int wmain(int argc, const WCHAR* argv[])
{
	if (argc < 3) {
		std::cout << "Usage: find starting-point expression" << std::endl;
		return 0;
	}

#ifdef _DEBUG
	//const TCHAR startingPoint[] = L"C:\\Users\\labuser\\source\\repos\\ConsoleApplication1\\ConsoleApplication1";
	//const TCHAR startingPoint[] = L"../../../../";
	//const WCHAR startingPoint[] = L"C:/";
	
	//const WCHAR expression[] = L"*.txt";

	//const TCHAR expression[] = L"Fi?derController.cpp";
	const WCHAR* startingPoint = argv[1];
	const WCHAR* expression = argv[2];
#else
	const WCHAR* startingPoint = argv[1];
	const WCHAR* expression = argv[2];
#endif // DEBUG

    std::wcout << "Starting Point: " << startingPoint << std::endl;
	std::wcout << "Expression : " << expression << std::endl;

	FinderDelegateImpl* delegate = new FinderDelegateImpl();
	
	WFind::FinderController::sharedInstance()->startSearchingForFile(startingPoint, expression, delegate, WFind::FileSearchOptions(true, true, true));

	delete delegate;

}
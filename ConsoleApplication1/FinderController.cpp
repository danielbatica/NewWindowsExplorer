#include "FinderController.h"
#include "FileApiUtils.h"
#include <iostream>
#include <vector>
//#include <memory>
#include "Shlwapi.h"
#include "Strsafe.h"
#pragma comment(lib,"shlwapi.lib")


using std::wstring;
using std::wcout;
using std::shared_ptr;
using std::make_shared;

using namespace WFind;
FinderController::FinderController()
{

}

FinderController* FinderController::sharedInstance()
{
	static FinderController s_Instance;
	return &s_Instance;
}

void FinderController::startSearchingForFile(const WCHAR* startingPoint, const WCHAR* expression, FileSearchDelegate* delegate, const FileSearchOptions& options)
{
	LPWSTR fullPathStartingPoint = nullptr;
	//TODO: check if startingPoint is directory
	DWORD result = FileApiUtils::GetFullPathForStartingPoint(startingPoint, &fullPathStartingPoint);
	//TODO: check result

	wstring strFolder(fullPathStartingPoint);
	delete fullPathStartingPoint;

#ifdef _DEBUG
	wcout << "Will actually start from: " << startingPoint << std::endl;
#endif

	if (!result) {
		FileSearchDelegateError error{L"Could not get full path from start point param"};
		if (delegate) {
			delegate->onFileFound(nullptr, &error);
		}
		return;
	}
	
	this->findFileInFolder(strFolder, expression, this, options);
}

void FinderController::findFileInFolder(const wstring& strFolder, const WCHAR*& expression, FileSearchDelegate* delegate, const FileSearchOptions& options)
{
#ifdef _DEBUG
	int numfiles = 0;
#endif 

	std::unique_ptr<std::vector<wstring>> opperationQueue = std::make_unique<std::vector<wstring>>();
	opperationQueue->push_back(strFolder);

	while (opperationQueue->size()) {

		wstring currentFolderFullPath = opperationQueue->back();
		opperationQueue->pop_back();

		wstring allFilesQuerry = currentFolderFullPath + L"*";

		WIN32_FIND_DATA findFileData{ 0 };
		HANDLE hForNext = FindFirstFileW(allFilesQuerry.c_str(), &findFileData);

#ifdef _DEBUG
		++numfiles;
#endif
		do {
			if (INVALID_HANDLE_VALUE != hForNext) {

				// this needs to be set only when used
				if (PathMatchSpecW(findFileData.cFileName, expression)) {

					wstring fullFilePath = currentFolderFullPath + findFileData.cFileName;
					FileSearchDelegateResult result{ fullFilePath.c_str() };

					if (delegate) {
						delegate->onFileFound(&result, nullptr);
					}
				}


				if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
					wcscmp(findFileData.cFileName, FU_CURRENT_DIRECTORY) &&
					wcscmp(findFileData.cFileName, FU_UPPER_DIRECTORY)) {

					if (true == options.recursive) {
						opperationQueue->emplace_back(currentFolderFullPath + findFileData.cFileName + L"\\");
					}
				}
			}
			findFileData = WIN32_FIND_DATA{ 0 };

#ifdef _DEBUG
			++numfiles;
#endif		
		} while (FindNextFileW(hForNext, &findFileData) != 0);

		FindClose(hForNext);
	}

	if (delegate) {
		delegate->onSearchComplete(strFolder.c_str());
	}

#ifdef _DEBUG
	std::cout << "Searched in: " << numfiles << " files\r\n";
#endif
}


////////////// Delegate impl
void FinderController::onFileFound(const FileSearchDelegateResult* result, const FileSearchDelegateError* error) 
{
	if (error || !result) {
		//todo
		return;
	}
	wcout << result->result << std::endl;
	return;
}

void FinderController::onSearchComplete(const WCHAR* expression)
{
	wcout << L"Finished search for: " << expression;
}

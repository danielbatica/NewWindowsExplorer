#include "FinderController.h"
#include "FileApiUtils.h"


FinderController::FinderController()
{

}

FinderController* FinderController::sharedInstance()
{
	static FinderController s_Instance;
	return &s_Instance;
}

void FinderController::startSearchingForFile(const TCHAR* startingPoint, const TCHAR* expression, FileSearchDelegate* delegate)
{
	LPWSTR fullPathStartingPoint = nullptr;
	DWORD result = FileApiUtils::GetFullPathForStartingPoint(startingPoint, &fullPathStartingPoint);
	std::wstring strFolder(fullPathStartingPoint);
	delete fullPathStartingPoint;

	if (!result) {
		FileSearchDelegateError error{"Could not get full path from start point param"};
		if (delegate) {
			delegate->onFileFound(nullptr, &error);
		}
		return;
	}
	
	std::wstring allFiles(L"*");
	this->findFileInFolder(strFolder, allFiles, nullptr);

}

void FinderController::findFileInFolder(const std::wstring& folderPath, const std::wstring& fileName, FileSearchDelegate* delegate)
{
	std::wstring fullQuerry = folderPath + fileName;

	WIN32_FIND_DATA findFileData{ 0 };
	HANDLE hForNext = FindFirstFileW(fullQuerry.c_str(), &findFileData);

	if (INVALID_HANDLE_VALUE != hForNext) {
		FileSearchDelegateResult result{"Found file"};
		if (delegate) {
			delegate->onFileFound(&result, nullptr);
		}
	}

	//PathMatchSpecW

	FindClose(hForNext);
}

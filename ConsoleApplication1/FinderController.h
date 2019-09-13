#pragma once
#include <tchar.h>
#include "FileSearchDelegate.h"
#include <string>

class FinderController
{
	private:
		FinderController();
		~FinderController() = default;
		void findFileInFolder(const std::wstring& folderPath, const std::wstring& fileName, FileSearchDelegate* delegate);

	public:
		static FinderController* sharedInstance();
		FinderController(const FinderController&) = delete;
		FinderController& operator=(const FinderController&) = delete;

		//// API
		void startSearchingForFile(const TCHAR* startingPoint, const TCHAR* expression, FileSearchDelegate* delegate);
};


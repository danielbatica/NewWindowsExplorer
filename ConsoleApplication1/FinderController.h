#pragma once

#include "windows.h"
#include <string>
#include <memory>
#include "FileSearchDelegate.h"

struct FileSearchOptions {
	bool recursive;
	FileSearchOptions() : recursive(true) {};
	FileSearchOptions(bool _recursive) : recursive(_recursive) {};
};

static const FileSearchOptions DEFAULT_SEARCH_OPTIONS = FileSearchOptions();

class FinderController : FileSearchDelegate
{
	private:
		FinderController();
		~FinderController() = default;
		void findFileInFolder(const std::wstring& strFolder, const WCHAR*& expression, FileSearchDelegate* delegate, const FileSearchOptions& options = DEFAULT_SEARCH_OPTIONS);


	public:
		static FinderController* sharedInstance();
		FinderController(const FinderController&) = delete;
		FinderController& operator=(const FinderController&) = delete;

		//// API
		void startSearchingForFile(const WCHAR* startingPoint, const WCHAR* expression, FileSearchDelegate* delegate, const FileSearchOptions& options = DEFAULT_SEARCH_OPTIONS);

		//// Delegate impl for tests
		void onFileFound(const FileSearchDelegateResult* result, const FileSearchDelegateError* error) override;
		void onSearchComplete(const WCHAR* expression) override;

};


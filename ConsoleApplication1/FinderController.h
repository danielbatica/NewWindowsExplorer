#pragma once

#include "windows.h"
#include <string>
#include <memory>
#include "FileSearchDelegate.h"

namespace WFind
{
	struct FileSearchOptions {
		bool recursive;
		bool addFullPathInResults;
		bool ignoreLoopbacks;

		FileSearchOptions() : recursive(true), addFullPathInResults(true), ignoreLoopbacks(true) {};
		FileSearchOptions(bool _recursive, 
						  bool _addFullPathInResults,
						  bool _ignoreLoopbacks) :

						  recursive(_recursive),
						  addFullPathInResults(_addFullPathInResults),
						  ignoreLoopbacks(_ignoreLoopbacks) {};
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
		bool filePathMatchesExpression(const WCHAR* startingPoint, const WCHAR* expression);

		//// Delegate impl for tests
		void onFileFound(const FileSearchDelegateResult* result, const FileSearchDelegateError* error) override;
		void onSearchComplete(const WCHAR* expression) override;
	};
};

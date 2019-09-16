#pragma once
#include "windows.h"

namespace WFind
{
	struct FileSearchDelegateResult {
		const WCHAR* result;
	};

	struct FileSearchDelegateError {
		const WCHAR* message;
	};

	class FileSearchDelegate
	{
	public:
		virtual void onFileFound(const FileSearchDelegateResult* result, const FileSearchDelegateError* error) = 0;
		virtual void onSearchComplete(const WCHAR* expression) = 0;
	};
};
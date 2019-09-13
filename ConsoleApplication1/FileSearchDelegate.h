#pragma once

typedef struct _FileSearchDelegateResult {
	const char* result;
} FileSearchDelegateResult;

typedef struct _FileSearchDelegateError {
	const char* message;
} FileSearchDelegateError;

class FileSearchDelegate
{
public:
	virtual void onFileFound(FileSearchDelegateResult* result, FileSearchDelegateError* error) = 0;
};
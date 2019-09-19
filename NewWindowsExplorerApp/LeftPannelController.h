#pragma once
#include "FileSearchDelegate.h"
#include "FileModel.h"

namespace NewWindowsExplorerApp
{
	using namespace Platform;
	using namespace Platform::Collections;
	using namespace Windows::Foundation::Collections;

	class LeftPannelController : WFind::FileSearchDelegate
	{

	private:
		Vector<FileModel^>^ m_model;
		String^ m_rootPath;

	public:
		LeftPannelController();
		~LeftPannelController();

		///// API Controller
		void setRootFolder(String^ fullFolderPath);
		void listFolderContainer(String^ folderPath);

		///// API Model
		Vector<FileModel^>^ getLeftPannelFolders();

		///////// WFind::FileSearchDelegate impl
		void onFileFound(const WFind::FileSearchDelegateResult* result, const WFind::FileSearchDelegateError* error) override;
		void onSearchComplete(const WCHAR* expression) override;
	};
}


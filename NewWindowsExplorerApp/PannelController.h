#pragma once
#include "FileSearchDelegate.h"
#include "FileModel.h"

namespace NewWindowsExplorerApp
{
	using namespace Platform;
	using namespace Platform::Collections;
	using namespace Windows::Foundation::Collections;

	///
	class PannelController : WFind::FileSearchDelegate
	{

	private:
		Vector<FileModel^>^ m_leftModel;
		Vector<FileModel^>^ m_rightModel;
		Vector<FileModel^>^ m_rightModelFilter;

		String^ m_rootPath;
		bool addDataOnlyInRightPannel;// todo: use better mechanism than this, concurency issues

	public:
		PannelController();
		~PannelController();

		///// API Controller
		void setRootFolder(String^ fullFolderPath);
		void listFolderContainer(String^ folderPath);

		///// API Model
		Vector<FileModel^>^ getLeftPannelFolders();
		Vector<FileModel^>^ getRightPannelFolders();
		void filterRightPannelOnExpression(const WCHAR* expression);

		///////// WFind::FileSearchDelegate impl
		void onFileFound(const WFind::FileSearchDelegateResult* result, const WFind::FileSearchDelegateError* error) override;
		void onSearchComplete(const WCHAR* expression) override;
	};
}


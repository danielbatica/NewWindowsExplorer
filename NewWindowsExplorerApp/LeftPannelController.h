#pragma once
#include "FileSearchDelegate.h"

namespace NewWindowsExplorerApp
{
	using namespace Platform;
	using namespace Platform::Collections;
	using namespace Windows::Foundation::Collections;

	class LeftPannelController : WFind::FileSearchDelegate
	{
	private:
		Vector<String^>^ m_model;
	public:
		LeftPannelController(Vector<String^>^ model);
		~LeftPannelController();

		///// API
		void listFolderContainer(String^ folderPath);

		///////// WFind::FileSearchDelegate impl
		void onFileFound(const WFind::FileSearchDelegateResult* result, const WFind::FileSearchDelegateError* error) override;
		void onSearchComplete(const WCHAR* expression) override;
	};
}


#include "pch.h"
#include "LeftPannelController.h"
#include "FinderController.h"

using namespace NewWindowsExplorerApp;

///// Constructor
LeftPannelController::LeftPannelController(Vector<String^>^ model)
{
	m_model = model;
}

///// Destructor
LeftPannelController::~LeftPannelController()
{
	if (m_model) {
		m_model->Clear();
	}
}

///// API
void LeftPannelController::listFolderContainer(String^ folderPath)
{
	m_model->Clear();
	WFind::FileSearchOptions searchOptions = WFind::FileSearchOptions(false, false, false);
	//TODO: don't use constant here
	WFind::FinderController::sharedInstance()->startSearchingForFile(folderPath->Data(), L"*", this, searchOptions);
}


///////// WFind::FileSearchDelegate impl
void LeftPannelController::onFileFound(const WFind::FileSearchDelegateResult* result, const WFind::FileSearchDelegateError* error)
{
	if (m_model && !error) {
		String^ fileName = ref new String(result->result);
		m_model->Append(fileName);
	}
}

void LeftPannelController::onSearchComplete(const WCHAR* expression)
{
}

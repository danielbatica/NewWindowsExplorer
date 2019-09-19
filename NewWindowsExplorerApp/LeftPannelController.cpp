#include "pch.h"
#include "LeftPannelController.h"
#include "FinderController.h"

using namespace NewWindowsExplorerApp;

///// Constructor
LeftPannelController::LeftPannelController()
{
	m_model = ref new Vector<FileModel^>();
	m_rootPath = nullptr;
}

///// Destructor
LeftPannelController::~LeftPannelController()
{
	if (m_model) {
		m_model->Clear();
	}
}


///// API Controller
void NewWindowsExplorerApp::LeftPannelController::setRootFolder(String^ fullFolderPath)
{
	m_model->Clear();
	WFind::FileSearchOptions searchOptions = WFind::FileSearchOptions(false, false, true);
	//TODO: don't use constant here
	WFind::FinderController::sharedInstance()->startSearchingForFile(fullFolderPath->Data(), L"*", this, searchOptions);

	m_rootPath = fullFolderPath;
}

void LeftPannelController::listFolderContainer(String^ folderPath)
{
	m_model->Clear(); 
	WFind::FileSearchOptions searchOptions = WFind::FileSearchOptions(false, false, true);
	//TODO: don't use constant here
	WFind::FinderController::sharedInstance()->startSearchingForFile(folderPath->Data(), L"*", this, searchOptions);
}

///// API Model
Vector<FileModel^>^ NewWindowsExplorerApp::LeftPannelController::getLeftPannelFolders()
{
	return this->m_model;
}

///////// WFind::FileSearchDelegate impl
void LeftPannelController::onFileFound(const WFind::FileSearchDelegateResult* result, const WFind::FileSearchDelegateError* error)
{
	if (m_model && !error) {
		// add only folders
		if (result->isFolder) {
			FileModel^ fileDetails = ref new FileModel(result->fileName, result->isFolder);
			m_model->Append(fileDetails);
		}
	}
}

void LeftPannelController::onSearchComplete(const WCHAR* expression)
{
}

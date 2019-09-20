#include "pch.h"
#include "PannelController.h"
#include "FinderController.h"
#include "FileApiUtils.h"

using namespace NewWindowsExplorerApp;

///// Constructor
PannelController::PannelController()
{
	m_leftModel  = ref new Vector<FileModel^>();
	m_rightModel = ref new Vector<FileModel^>();
	m_rootPath = nullptr;
	addDataOnlyInRightPannel = false;
}

///// Destructor
PannelController::~PannelController()
{
	if (m_leftModel) {
		m_leftModel->Clear();
	}

	if (m_rightModel) {
		m_rightModel->Clear();
	}
}


///// API Controller
void PannelController::setRootFolder(String^ fullFolderPath)
{
	m_leftModel->Clear();
	m_rightModel->Clear();
	addDataOnlyInRightPannel = false;

	WFind::FileSearchOptions searchOptions = WFind::FileSearchOptions(false, false, true);
	WFind::FinderController::sharedInstance()->startSearchingForFile(fullFolderPath->Data(), WFind::FU_WILDCARD, this, searchOptions);

	m_rootPath = fullFolderPath;
}

void PannelController::listFolderContainer(String^ folderPath)
{
	m_rightModel->Clear();
	addDataOnlyInRightPannel = true;

	for (auto& file : m_leftModel) {
		file->IsOpened = (file->FileName->Equals(folderPath));
	}

	String^ fullPathFolder = m_rootPath + WFind::FU_FOLDER_ENDING_CHARACTER + folderPath;
	WFind::FileSearchOptions searchOptions = WFind::FileSearchOptions(false, false, true);
	WFind::FinderController::sharedInstance()->startSearchingForFile(fullPathFolder->Data(), WFind::FU_WILDCARD, this, searchOptions);
}

///// API Model
Vector<FileModel^>^ PannelController::getLeftPannelFolders()
{
	return this->m_leftModel;
}

Vector<FileModel^>^ PannelController::getRightPannelFolders()
{
	return this->m_rightModel;
}

///////// WFind::FileSearchDelegate impl
void PannelController::onFileFound(const WFind::FileSearchDelegateResult* result, const WFind::FileSearchDelegateError* error)
{
	if (!error) {
		// add only folders for left pannel
		FileModel^ fileDetails = ref new FileModel(result->fileName, result->isFolder);
		if (!addDataOnlyInRightPannel && m_leftModel && result->isFolder) { // if there are folders in left it must be a simple tap
			m_leftModel->Append(fileDetails);
		}

		if (m_rightModel) {
			m_rightModel->Append(fileDetails);
		}
	}
}

void PannelController::onSearchComplete(const WCHAR* expression)
{
}

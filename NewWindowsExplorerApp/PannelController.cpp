#include "pch.h"
#include "PannelController.h"
#include "FinderController.h"
#include "FileApiUtils.h"
#include <regex>

using namespace NewWindowsExplorerApp;

///// Constructor
PannelController::PannelController()
{
	m_leftModel  = ref new Vector<FileModel^>();
	m_rightModel = ref new Vector<FileModel^>();
	m_rightModelFilter = ref new Vector<FileModel^>();

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

	if (m_rightModelFilter) {
		m_rightModelFilter->Clear();
	}
}


///// API Controller
void PannelController::setRootFolder(String^ fullFolderPath)
{
	m_leftModel->Clear();
	m_rightModel->Clear();
	m_rightModelFilter->Clear();

	addDataOnlyInRightPannel = false;

	WFind::FileSearchOptions searchOptions = WFind::FileSearchOptions(false, false, true);
	WFind::FinderController::sharedInstance()->startSearchingForFile(fullFolderPath->Data(), WFind::FU_WILDCARD, this, searchOptions);

	m_rootPath = fullFolderPath;
}

void PannelController::listFolderContainer(String^ folderPath)
{
	m_rightModel->Clear();
	m_rightModelFilter->Clear();
	addDataOnlyInRightPannel = true;

	for (auto& file : m_leftModel) {
		file->IsOpened = (file->FileName->Equals(folderPath));
	}

	String^ fullPathFolder = m_rootPath + WFind::FU_FOLDER_ENDING_CHARACTER + folderPath;
	WFind::FileSearchOptions searchOptions = WFind::FileSearchOptions(false, false, true);
	WFind::FinderController::sharedInstance()->startSearchingForFile(fullPathFolder->Data(), WFind::FU_WILDCARD, this, searchOptions);
}

void NewWindowsExplorerApp::PannelController::filterRightPannelOnExpression(const WCHAR* expression)
{
	String^ strExpression = ref new String(expression);
	if (!strExpression->Length()) {
		strExpression = ref new String(WFind::FU_WILDCARD);
	}
	m_rightModelFilter->Clear();

	
	
	std::cmatch narrowMatch;
	std::basic_regex<WCHAR> rx;
	try {
		rx = std::basic_regex<WCHAR>(strExpression->Begin(), std::regex_constants::grep | std::regex_constants::icase);
	} catch (const std::regex_error& e) {
		wprintf(L"Error when searching %hs", e.what());
		return;
	}

	for (auto& fileModel : m_rightModel) {
		bool found = std::regex_search(fileModel->FileName->Begin(), rx);
		found |= WFind::FinderController::sharedInstance()->filePathMatchesExpression(fileModel->FileName->Begin(), strExpression->Begin());
		if (found) {
			m_rightModelFilter->Append(fileModel);
		}
	}
}

///// API Model
Vector<FileModel^>^ PannelController::getLeftPannelFolders()
{
	return this->m_leftModel;
}

Vector<FileModel^>^ PannelController::getRightPannelFolders()
{
	return this->m_rightModelFilter;
	//return this->m_rightModel;
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
			m_rightModelFilter->Append(fileDetails);
		}
	}
}

void PannelController::onSearchComplete(const WCHAR* expression)
{
}

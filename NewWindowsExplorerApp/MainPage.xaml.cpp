//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <iostream>
#include "FinderController.h"

using namespace std;
using namespace NewWindowsExplorerApp;
using namespace concurrency;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;


MainPage::MainPage()
{
	InitializeComponent();
	this->fileDataVector = ref new Vector<FileModel^>();
	this->leftPannelController = std::make_unique<LeftPannelController>(LeftPannelController(this->fileDataVector));

}


void NewWindowsExplorerApp::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FolderPicker^ folderPicker = ref new FolderPicker();
	folderPicker->SuggestedStartLocation = PickerLocationId::Desktop;
	folderPicker->FileTypeFilter->Append("*");

	create_task(folderPicker->PickSingleFolderAsync()).then([this](StorageFolder^ folder) {
		this->nameInput->Text = folder->Path;
		//TODO: do this hardcode in the lib
		this->leftPannelController->listFolderContainer(folder->Path + "\\");
	});
}

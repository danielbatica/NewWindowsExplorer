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

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

// https://docs.microsoft.com/en-us/windows/uwp/get-started/create-a-basic-windows-10-app-in-cpp
MainPage::MainPage()
{
	InitializeComponent();
	this->fileDataVector = ref new Vector<String^>();

	for (int i = 0; i < 100; ++i) {
		this->fileDataVector->Append("Some Text" + i);
	}
}


void NewWindowsExplorerApp::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FolderPicker^ folderPicker = ref new FolderPicker();
	folderPicker->SuggestedStartLocation = PickerLocationId::Desktop;
	folderPicker->FileTypeFilter->Append("*");

	create_task(folderPicker->PickSingleFolderAsync()).then([this](StorageFolder^ folder) {
		this->nameInput->Text = folder->Path;
		WFind::FinderController::sharedInstance()->startSearchingForFile(folder->Path->Data(), L"*", nullptr);
	});
}

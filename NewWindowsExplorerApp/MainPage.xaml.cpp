//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <iostream>
#include "FinderController.h"
#include "FileApiUtils.h"

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
	this->leftPannelController = std::make_shared<LeftPannelController>(LeftPannelController());
}


void NewWindowsExplorerApp::MainPage::ButtonSearch_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FolderPicker^ folderPicker = ref new FolderPicker();
	folderPicker->SuggestedStartLocation = PickerLocationId::Desktop;
	folderPicker->FileTypeFilter->Append("*");

	TextBox^ fullRootPathInput = this->fullRootPathInput;
	std::shared_ptr<LeftPannelController> leftPannelController = this->leftPannelController;
	create_task(folderPicker->PickSingleFolderAsync()).then([fullRootPathInput, leftPannelController](StorageFolder^ folder) {
		
		fullRootPathInput->Text = folder->Path;
		leftPannelController->setRootFolder(folder->Path);
	});
}


void NewWindowsExplorerApp::MainPage::ParrentFolder_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	WCHAR* c_ParrentStr = nullptr;
	WFind::FileApiUtils::GetParrentForFolder(this->fullRootPathInput->Text->Begin(), &c_ParrentStr);

	if (c_ParrentStr) {
		String^ newPath = ref new String(c_ParrentStr);
		this->fullRootPathInput->Text = newPath;
		this->leftPannelController->setRootFolder(newPath);
	}
 
	delete c_ParrentStr;
}


void NewWindowsExplorerApp::MainPage::LeftFolder_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	
	TextBlock^ tb = safe_cast<TextBlock^>(sender);

	String^ newRootPath = this->fullRootPathInput->Text + "\\" + tb->Text;
	this->fullRootPathInput->Text = newRootPath;
	this->leftPannelController->setRootFolder(newRootPath);
}

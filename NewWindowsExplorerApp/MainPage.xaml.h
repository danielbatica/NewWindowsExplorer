//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once
#include <memory>
#include "MainPage.g.h"
#include "LeftPannelController.h"
#include "FileModel.h"


namespace NewWindowsExplorerApp
{
	using namespace Platform;
	using namespace Platform::Collections;
	using namespace Windows::Foundation::Collections;

	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

		//// Models used by Page
		property IVector<FileModel^>^ LeftPannelFoldersModel
		{
			IVector<FileModel^>^ get() { return this->leftPannelController->getLeftPannelFolders(); };
		}

	private:
		std::unique_ptr<LeftPannelController> leftPannelController;
		void ButtonSearch_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ParrentFolder_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
		void LeftFolder_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
	};
}

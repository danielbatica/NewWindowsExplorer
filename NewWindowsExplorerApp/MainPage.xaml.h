//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once
#include <memory>
#include "MainPage.g.h"
#include "LeftPannelController.h"



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
		property IVector<String^>^ FileDataModel
		{
			IVector<String^>^ get() { return this->fileDataVector; };
		}

	private:
		std::unique_ptr<LeftPannelController> leftPannelController;
		Vector<String^>^ fileDataVector;
		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}

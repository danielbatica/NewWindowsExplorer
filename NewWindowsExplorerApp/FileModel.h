#pragma once

namespace NewWindowsExplorerApp
{
	using namespace Windows::UI::Xaml::Data;

	static Platform::String^ OPEN_FOLDER_ICON = "/Assets/open_folder.png";
	static Platform::String^ CLOSED_FOLDER_ICON = "/Assets/closed_folder.png";
	static Platform::String^ FILE_ICON = "/Assets/file.png";


	public ref class FileModel sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged
	{
	private:
		bool m_bIsOpened;

	internal:
		FileModel(const WCHAR* c_fileName, bool _isFolder) {
			this->FileName = ref new Platform::String(c_fileName);
			this->IsFolder = _isFolder;
		}
		void OnPropertyChanged(Platform::String^ propertyName) {

			PropertyChanged(this, ref new PropertyChangedEventArgs(propertyName));
		}

	public:

		virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

		property Platform::String^ FileName;
		property Platform::Boolean IsFolder;
		property Platform::Boolean IsOpened {
			Platform::Boolean get() { return m_bIsOpened; }
			void set(Platform::Boolean value) {
				m_bIsOpened = value;
				OnPropertyChanged("FileIconPath");
			} 
		}

		
		property Platform::String^ FileIconPath
		{
			Platform::String^ get() {
				if (this->IsFolder && this->IsOpened) {
					return OPEN_FOLDER_ICON;
				}
				else if (!this->IsFolder) {
					return FILE_ICON;
				}
				else {
					return CLOSED_FOLDER_ICON;
				}
			}
		}
	};
};


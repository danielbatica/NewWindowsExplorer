#pragma once

namespace NewWindowsExplorerApp
{
	static Platform::String^ OPEN_FOLDER_ICON = "/Assets/open_folder.png";
	static Platform::String^ CLOSED_FOLDER_ICON = "/Assets/closed_folder.png";


	public ref class FileModel sealed
	{
	internal:
		FileModel(const WCHAR* c_fileName, bool _isFolder) {
			this->FileName = ref new Platform::String(c_fileName);
			this->IsFolder = _isFolder;
		}
	public:
		property Platform::String^ FileName;
		property Platform::Boolean IsFolder;
		property Platform::Boolean IsOpened;

		
		property Platform::String^ FileIconPath
		{
			Platform::String^ get() {
				if (this->IsFolder && this->IsOpened) {
					return OPEN_FOLDER_ICON;
				}
				else {
					return CLOSED_FOLDER_ICON;
				}
			}
		}
	};
};


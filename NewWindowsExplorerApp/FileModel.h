#pragma once

namespace NewWindowsExplorerApp
{
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

		

		property Platform::Boolean isFolderOpened
		{
			Platform::Boolean get() { return this->IsFolder && this->IsOpened; }
		}
	};
};


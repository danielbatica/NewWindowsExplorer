# NewWindowsExplorer

NewWindowsExplorer is a solution comprised of three buildable units:
* Console app that wraps FindFirstFileW
* Static lib that embeds the wrapper from the console app
* UWP app that acts as a file explorer and static links to the lib above

## Building Targets

The following targets are available:

* Debug App - only for NewWindowsExplorerApp
* Debug Lib - only for WFind project
* Release Lib - only for WFind project
* Release - both projects
* Debug - only for WFInd console app

Note: Debug and Realease of UI app require that the lib was prebuilt using the corresponding Debug Lib/ Release Lib targets

### Running the Console app

Select target Debug/Release.
Right click on "WFind" project then hit Debug->Start New instance

The Console app takes two params as required ones. 
First is the place where the search should start, the second is the name of the file or expression (e.g: *.txt);
The Debug/Release targets are preconfigured to use "C:\" and "*.txt" as input params

### Build the Lib (used by the UI app)

Select target Debug Lib/Release Lib
Hit Build then Build WFind

### Running the UI app (NewWindowsExplorer)

Prerequisites:
* build the lib

Select target Debug App for debug or Release
Right click on NewWindowsExplorerApp then  hit Debug->Start New instance

## Usage Description

### Console app

args: start_folder expression

The app itself does a recursive search starting from the first input parameter.
When `expression` matches a file name it encounters, it's full path is outputed to the console.
(the match is made via `PathMatchSpecW`) specs.

Known Limitations:
* `start_folder` is not verified internally as being a folder

### UI App or New

Visual Description:
* `Search In`: button:
 Opens a file picker dialog where the root folder is set
* `Top inoput text`: disabled from user input, specifies the current root path
* `Left Pannel`: subdirs of the root paths are displayed in it.
Items in the list support tap (ON TEXT) and double tap. 
When a subdir is tapped, the right pannel is populated with the contents of the dir.
When a subdir is double tapped, the root path is appeneded with the selected subdir.
This results in both left and right pannels reload.
* `Parrent Folder`: Tap on it to go up a dir. 
[Bug found here: C:\ is not listed properly, use `Search In` to point the app to a different folder]
* `Filter input`: Used to filter files listed in the right pannel.
Grep matching `std::regex_constants::grep` and `PathMatchSpecW` are embedded.
Filtering is made as the user taps. Removing text from the filter will display the full contents of the opened dir.

## Future Improvements

* Enable the `PannelController.cpp` to use async tasks so that the UI is not blocked 

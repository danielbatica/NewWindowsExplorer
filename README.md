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
Right click on NewWindowsExplorerApp 


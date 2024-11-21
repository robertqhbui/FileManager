Description
===========
This Microsoft Visual Studio consists of two projects:
FileManager
FileManagerTest - A placeholder project to hold unit tests.


Currently test code is inside FileManager.cpp. This should be moved to FileManagerTest project.

Build
=====
Open the solution inside Visual Studio 2022, C++20.
Only the Release for x64 build configuration is setup. I have not tested with other configurations yet.
Therefore, ensure your build configuration is set to Release for x64 before attempting to build.

Test
=====
Copy the two folders from the TestData to the following location:
C:\Temp

Once build, open a command prompt window and navigate to the location of the built executable.
Run FileManager.exe inside the command prompt.


To Do List
===========
1. Move all test code to FileManagerTest
2. Define all the indexed/scanned/backup file types inside a configuration file
3. Set the build process to create .DLL files






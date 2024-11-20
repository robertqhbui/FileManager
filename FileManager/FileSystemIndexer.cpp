#include "FileSystemIndexer.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <queue>    


// Initialise static members
FileSystemIndexer*				FileSystemIndexer::mInstance = nullptr;
std::mutex						FileSystemIndexer::mMutex;
std::map<FileType, bool>		FileSystemIndexer::mFileIndexableMap = {};
std::map<FileType, bool>		FileSystemIndexer::mFileBackupMap = {};

//---------------------------------------------------------------------------------------------------------------------
// Name			:	getInstance
// Description	:	Gets an instance object of the FileSystemIndexer
// Parameter	:	NonemIndexableMap
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
FileSystemIndexer* FileSystemIndexer::getInstance() {

	// Acquire lock before checking instance
	std::lock_guard<std::mutex> lock(mMutex); 	// Automatically releases lock
	if (mInstance == nullptr)
	{
		mInstance = new FileSystemIndexer();				// Create the instance only once

		//We could initialise the map at the top in the Initialise Static Member section
		//Chose to do it here to demonstrate the step to programmically adding to the map
		//so we the map could be initialise from a resource file/config file.
		addIndexableMap(UNKNOWN_FILETYPE, false);
		addIndexableMap(DIRECTORY_FILETYPE);
		addIndexableMap(TEXT_FILETYPE, true);
		addIndexableMap(XML_FILETYPE, true);
		addIndexableMap(EXECUTABLE_FILETYPE, true);
		addIndexableMap(MSDOCUMENT_FILETYPE, true);
		addIndexableMap(MSEXCEL_FILETYPE, true);
		addIndexableMap(MSPOWERPOINT_FILETYPE, true);

		addBackupMap(MSDOCUMENT_FILETYPE, true);
		addBackupMap(MSEXCEL_FILETYPE, true);
	}
	return mInstance;
}


//---------------------------------------------------------------------------------------------------------------------
// Name			:	process
// Description	:	Index all files for specified path and its subdirectories
// Parameter	:	path - string for location to index
// Returne		:	Unique Pointer for FileSystemNode
//---------------------------------------------------------------------------------------------------------------------
std::unique_ptr<FileSystemNode>	FileSystemIndexer::process(const std::string & path)
{
	std::unique_ptr<FileSystemNode> root;


	//Early return when the path is invalid
	if (!std::filesystem::exists(path))
		return root;
	
	root = std::make_unique<FileSystemDirectory>(path);

	//Processing children of this directory
	if (std::filesystem::is_directory(path))
	{
		for (auto const& dir_entry : std::filesystem::directory_iterator{ path })
		{
			std::unique_ptr<FileSystemNode> node;
			
			if (std::filesystem::is_directory(dir_entry.path()))
			{
				//Recursively processing subdirectories
				node = process(dir_entry.path().string());
				root->addChild(std::move(node));
			}
			else
			{
				FileType fileType = FileSystemNode::lookupFileType(dir_entry.path().extension().string());

				if (isIndexable(fileType))
				{
					node = std::make_unique<FileSystemFile>(dir_entry.path().string()); 
					root->addChild(std::move(node));
				}
			}	
		}	
	}
	return root;
}


//---------------------------------------------------------------------------------------------------------------------
// Name			:	isIndexable
// Description	:	Checks if we wamt to index this file extension
// Parameter	:	nodeExtension - File extension
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
bool FileSystemIndexer::isIndexable(FileType fileType)
{
	std::map<FileType, bool>::iterator mapIterator = mFileIndexableMap.find(fileType);
	if (mapIterator != mFileIndexableMap.end())
	{
		return mapIterator->second;
	}
	return false;
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	addIndexableMap
// Description	:	Add FileType to the map for indexing process
// Parameter	:	fileType - FileType to add to map
//					isIndexable - boolean indicating to index/not index
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
void FileSystemIndexer::addIndexableMap(FileType fileType, bool isIndexable)
{
	mFileIndexableMap[fileType] = isIndexable;
}


//---------------------------------------------------------------------------------------------------------------------
// Name			:	isBackupable
// Description	:	Checks if we wamt to backup this file
// Parameter	:	nodeExtension - File extension
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
bool FileSystemIndexer::isBackupable(FileType fileType)
{
	std::map<FileType, bool>::iterator mapIterator = mFileBackupMap.find(fileType);
	if (mapIterator != mFileBackupMap.end())
	{
		return mapIterator->second;
	}
	return false;
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	addIndexableMap
// Description	:	Add FileType to the map for indexing process
// Parameter	:	fileType - FileType to add to map
//					isIndexable - boolean indicating to index/not index
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
void FileSystemIndexer::addBackupMap(FileType fileType, bool isIndexable)
{
	mFileBackupMap[fileType] = isIndexable;
}
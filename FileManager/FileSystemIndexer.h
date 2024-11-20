#pragma once
#include <mutex>
#include "FileSystemNode.h"
#include <map>


class FileSystemIndexer
{
private:


	FileSystemIndexer() {}

	//Not allowing create an instance using new or copy 
	FileSystemIndexer(const FileSystemIndexer&) = delete;


	FileSystemIndexer&						operator=(const FileSystemIndexer&) = delete;

	static std::mutex						mMutex; // Mutex for thread safety
	static FileSystemIndexer*				mInstance;
	static std::map<FileType, bool>			mFileIndexableMap;
	static std::map<FileType, bool>			mFileBackupMap;
	

public:
	static FileSystemIndexer*				getInstance();
	static std::unique_ptr<FileSystemNode>	process(const std::string& path);

	static bool								isIndexable(FileType fileType);
	static void								addIndexableMap(FileType fileType, bool isIndexable = false);

	static bool								isBackupable(FileType fileType);
	static void								addBackupMap(FileType fileType, bool isIndexable);

};

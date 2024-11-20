#include "FileSystemNode.h"
#include <iostream>
#include <filesystem>
#include <format>

std::map<std::string, FileType>	FileSystemNode::mFileExtensionTypeMap
{
    {".txt", TEXT_FILETYPE},
    {".xml", XML_FILETYPE},
    {".exe", EXECUTABLE_FILETYPE},
    {".doc", MSDOCUMENT_FILETYPE},
    {".xls", MSEXCEL_FILETYPE},
    {".ppt", MSPOWERPOINT_FILETYPE }
};


//---------------------------------------------------------------------------------------------------------------------
// Name			:	FileSystemNode
// Description	:	Default Constructor 
// Parameter	:	None
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
FileSystemNode::FileSystemNode(): mFileType(UNKNOWN_FILETYPE)
{

}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	FileSystemNode
// Description	:	Constructor 
// Parameter	:	path - string for the node's path.
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
FileSystemNode::FileSystemNode(const std::string& path):    mNodePath(path),
                                                            mFileType(UNKNOWN_FILETYPE)
{
    std::filesystem::path filePath = path;
    mNodeName = filePath.filename().string();
    mNodeExtension = filePath.extension().string();
    mNodeDrive = filePath.root_path().string();
    mSize = std::filesystem::file_size(filePath);

    if (std::filesystem::is_directory(filePath))
    {
        mFileType = DIRECTORY_FILETYPE;
    }
    else
    {
        mFileType = FileSystemNode::lookupFileType(mNodeExtension);
    }
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	getDrive
// Description	:	Get the node's drive
// Parameter	:	None.
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
FileSystemNode::~FileSystemNode()
{

}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	getDrive
// Description	:	Get the node's drive
// Parameter	:	None.
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
std::string	FileSystemNode::getDrive() const
{
    return mNodeDrive;
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	getName
// Description	:	Get the node's name
// Parameter	:	None.
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
std::string	FileSystemNode::getName() const
{
    return mNodeName;
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	getPath
// Description	:	Get the node's path
// Parameter	:	None.
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
std::string	FileSystemNode::getPath() const
{
    return mNodePath;
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	getExtension
// Description	:	Get the node's extension
// Parameter	:	None.
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
std::string  FileSystemNode::getExtension() const
{
    return mNodeExtension;
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	FileSystemDirectory
// Description	:	Constructor
// Parameter	:	nodePath - standard string specifying the file system path for this node.
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
FileType FileSystemNode::getFileType() const
{
    return mFileType;
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	lookupFileType
// Description	:	Static method to find the FileType base on extension
// Parameter	:	nodeExtension - File extension
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
FileType FileSystemNode::lookupFileType(const std::string& nodeExtension)
{
    std::map<std::string, FileType>::iterator mapIterator = mFileExtensionTypeMap.find(nodeExtension);
    if (mapIterator != mFileExtensionTypeMap.end())
        return mapIterator->second;
    return UNKNOWN_FILETYPE;
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	FileSystemDirectory
// Description	:	Constructor
// Parameter	:	nodePath - standard string specifying the file system path for this node.
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
FileSystemDirectory::FileSystemDirectory(const std::string& directoryPath) : FileSystemNode(directoryPath)
{
    //Nothing to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	~FileSystemDirectory
// Description	:	Default destructor
// Parameter	:	None
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
FileSystemDirectory::~FileSystemDirectory()
{
    //Nothing to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	addChild
// Description	:	Add a child to the node. 
// Parameter	:	child - an unique pointer to FileSystemNode
// Returne		:	false
//---------------------------------------------------------------------------------------------------------------------
bool FileSystemDirectory::addChild(std::unique_ptr<FileSystemNode> child)
{
    mChildren.push_back(std::move(child));
    return true;
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	list
// Description	:	Print the node path and its children to standard output 
// Parameter	:	fileType - FileType to print
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
void FileSystemDirectory::list(const FileType fileType) const
{
    for (const auto& entry : mChildren)
    {
        entry->list(fileType);
    }
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	list
// Description	:	Print the node's children to standard output
// Parameter	:	None
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
void FileSystemDirectory::list() const
{
    for (const auto& entry : mChildren)
    {
        entry->list();
    }
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	FileSystemFile
// Description	:	Constructor
// Parameter	:	nodePath - standard string specifying the file system path for this node.
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
FileSystemFile::FileSystemFile(const std::string& nodePath): FileSystemNode(nodePath)
{
    //Nothing to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	~FileSystemFile
// Description	:	Default destructor
// Parameter	:	None
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
FileSystemFile::~FileSystemFile()
{
    //Nothing to do
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	addChild
// Description	:	Add a child to the node. This should not be called for a file.
// Parameter	:	child - an unique pointer to FileSystemNode
// Returne		:	false
//---------------------------------------------------------------------------------------------------------------------
bool FileSystemFile::addChild(std::unique_ptr<FileSystemNode> child)
{
    return false;
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	list
// Description	:	Print the node path to standard output 
// Parameter	:	fileType - FileType to print
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
void FileSystemFile::list(const FileType fileType) const
{
    if (mFileType == fileType)
        list();
}

//---------------------------------------------------------------------------------------------------------------------
// Name			:	list
// Description	:	Print the node path to standard output
// Parameter	:	None
// Returne		:	None
//---------------------------------------------------------------------------------------------------------------------
void FileSystemFile::list() const
{
    std::string formatted_str = std::format("{0: <30}", getName());
    std::cout << formatted_str << FileSizeForHumanEye{ mSize }  << std::endl;
}
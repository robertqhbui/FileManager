#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <cmath>
//#include <fstream>
#include <iostream>

enum FSType
{
	FS_DIRECTORY_TYPE = 0,
	FS_FILE_TYPE
};

enum FileType
{
	UNKNOWN_FILETYPE = 0,
	DIRECTORY_FILETYPE,
	TEXT_FILETYPE,
	XML_FILETYPE,
	EXECUTABLE_FILETYPE,
	MSDOCUMENT_FILETYPE,
	MSEXCEL_FILETYPE,
	MSPOWERPOINT_FILETYPE
};

//Reuse from example - https://en.cppreference.com/w/cpp/filesystem/file_size
struct FileSizeForHumanEye
{
	std::uintmax_t size{};

private:
	friend std::ostream& operator<<(std::ostream& os, FileSizeForHumanEye hr)
	{
		int o{};
		double mantissa = hr.size;
		for (; mantissa >= 1024.; mantissa /= 1024., ++o);
		os << std::ceil(mantissa * 10.) / 10. << "BKMGTPE"[o];
		return o ? os << "B (" << hr.size << ')' : os;
	}
};

class FileSystemNode
{
private:
	FileSystemNode();
	

protected:
	std::string										mNodeName;
	std::string										mNodeDrive;
	std::string										mNodePath;
	std::string										mNodeExtension;
	std::uintmax_t 									mSize{};
	std::vector<std::unique_ptr<FileSystemNode>>	mChildren;
	FileType										mFileType;

	static std::map<std::string, FileType>			mFileExtensionTypeMap;

public:

	FileSystemNode(const std::string& nodePath);
	~FileSystemNode();	

	static	FileType		lookupFileType(const std::string& nodeExtension);

	std::string				getDrive() const;
	std::string				getName() const;
	std::string				getPath() const;
	std::string				getExtension() const;
	FileType				getFileType() const;

	virtual	bool			addChild(std::unique_ptr<FileSystemNode> child) = 0;
	virtual void			list(const FileType fileType) const = 0;
	

	virtual void			list() const = 0;
	

};

class FileSystemDirectory : public FileSystemNode
{
public:
	FileSystemDirectory(const std::string& nodePath);
	~FileSystemDirectory();

	bool					addChild(std::unique_ptr<FileSystemNode> child);
	void					list(const FileType fileType) const;
	void					list() const;
};

class FileSystemFile : public FileSystemNode
{
public:
	FileSystemFile(const std::string& nodePath);
	~FileSystemFile();

	bool					addChild(std::unique_ptr<FileSystemNode> child);
	void					list(const FileType fileType) const;
	void					list() const;
	
};
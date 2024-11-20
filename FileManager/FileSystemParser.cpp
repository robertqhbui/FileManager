#include "FileSystemParser.h"

NTFSFileSystemParser::NTFSFileSystemParser()
{

}
NTFSFileSystemParser::~NTFSFileSystemParser()
{

}
bool NTFSFileSystemParser::open(const std::string path)
{
	return false;
}
bool NTFSFileSystemParser::close()
{
	return false;
}
std::vector<std::string> NTFSFileSystemParser::getChildren()
{
	std::vector<std::string> children;

	return children;
}


Ext4FileSystemParser::Ext4FileSystemParser()
{

}
Ext4FileSystemParser::~Ext4FileSystemParser()
{

}
bool Ext4FileSystemParser::open(const std::string path)
{
	return false;
}
bool Ext4FileSystemParser::close()
{
	return false;
}
std::vector<std::string> Ext4FileSystemParser::getChildren()
{
	std::vector<std::string> children;

	return children;
}
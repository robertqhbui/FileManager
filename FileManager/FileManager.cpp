#include <iostream>
#include "FileSystemIndexer.h"
#include "FileSystemNode.h"
#include <string>

int main()
{
    using namespace std::string_literals;
   

    FileSystemIndexer* indexer = FileSystemIndexer::getInstance();
   
    std::unique_ptr<FileSystemNode> rootA = indexer->process("C:\\Temp\\TestFolder1");

    std::cout << "----------------- All Indexed Files -------------------\n";
    if (rootA)
    {
        rootA->list();
    }
    std::cout << "----------------- Indexed Text Files -------------------\n";
    if (rootA)
    {
        rootA->list(TEXT_FILETYPE);
    }
    std::unique_ptr<FileSystemNode> rootB = indexer->process("C:\\Temp\\TestFolder2");

    std::cout << "----------------- All Indexed Files -------------------\n";
    if (rootB)
    {
        rootB->list();
    }
    std::cout << "----------------- Indexed Microsoft Excel Files -------------------\n";
    if (rootB)
    {
        rootB->list(MSEXCEL_FILETYPE);
    }
}


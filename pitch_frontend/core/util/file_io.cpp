#include "file_io.h"

#include <fstream>

std::string readFile(const std::string& fileName)
{
    auto fin = std::fstream(fileName);
    std::string reader;
    std::string result;

    while(std::getline(fin, reader))
    {
        result.append(reader);
    }

    return result;
}

#include "file_io.h"

#include <algorithm>
#include <fstream>

#ifndef STB_IMAGE_IMPLEMENTATION
#   define STB_IMAGE_IMPLEMENTATION
#   include "stb_image.h"
#endif

#include "algorithm.h"

std::string readFile(const std::string& fileName)
{
    auto fin = std::fstream(fileName);

    if(fin.fail())
    {
        throw std::runtime_error("Unable to open file " + fileName);
    }

    std::string reader;
    std::string result;

    while(std::getline(fin, reader))
    {
        result.append(reader);
        result.push_back('\n');
    }

    return result;
}

namespace
{
FileType typeOf(const std::string& fileName)
{
    const auto periodIndex = findLast(fileName.begin(), fileName.end(), '.');

    if(periodIndex == fileName.end())
    {
        throw std::runtime_error("Unknown file type");
    }

    const auto suffix = std::string(periodIndex, fileName.end());

    if(suffix == ".png")
    {
        return FileType::Png;
    }
    if(suffix == ".jpeg")
    {
        return FileType::Jpeg;
    }
    if(suffix == ".jpg")
    {
        return FileType::Jpg;
    }

    throw std::runtime_error("Unkown file type " + suffix);
}
}

TextureInfo loadTextureInfo(const std::string& fileName)
{
    TextureInfo result;
    result.data = stbi_load(fileName.c_str(), &result.width, &result.height, &result.channelCount, 0);

    if(!result.data)
    {
        //throw std::runtime_error("Failed to load texture data");
    }

    result.fileType = typeOf(fileName);

    return result;
}

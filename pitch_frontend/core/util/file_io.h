#ifndef FILE_IO_H
#define FILE_IO_H

#include <memory>
#include <string>

enum class FileType
{
    Jpeg,
    Jpg,
    Png
};

struct TextureInfo
{
    unsigned char* data;
    int width;
    int height;
    int channelCount;
    FileType fileType;
};

std::string readFile(const std::string& fileName);

TextureInfo loadTextureInfo(const std::string& fileName);

#endif //FILE_IO_H

#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>

enum class FileType
{
    Jpeg,
    Jpg,
    Png
};

struct TextureInfo
{
    TextureInfo() = default;
    TextureInfo(const TextureInfo& rhs);
    TextureInfo(TextureInfo&& rhs);
    ~TextureInfo();

    TextureInfo& operator=(const TextureInfo& rhs);
    TextureInfo& operator=(TextureInfo&& rhs) noexcept;

    unsigned char* data;
    int width;
    int height;
    int channelCount;
    FileType fileType;
};

std::string readFile(const std::string& fileName);

TextureInfo loadTextureInfo(const std::string& fileName);

#endif //FILE_IO_H

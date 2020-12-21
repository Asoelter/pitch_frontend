#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include <string>

#include "file_io.h"

class ResourceLoader
{
public:
    static std::string loadShader(const std::string& fileName);
    static TextureInfo loadTexture(const std::string& fileName);
};

#endif //RESOURCE_LOADER_H

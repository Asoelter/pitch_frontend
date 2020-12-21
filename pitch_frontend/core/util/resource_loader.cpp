#include "resource_loader.h"

#include <stdexcept>

std::string ResourceLoader::loadShader(const std::string& fileName)
{
#ifndef PITCH_SHADER_DIRECTORY
    throw std::runtime_error("Must define the shader directory");
#endif
    
    const auto shaderDir = std::string(PITCH_SHADER_DIRECTORY);
    const auto fullFilePath = shaderDir + "/" + fileName;
    return readFile(fullFilePath);
}

TextureInfo ResourceLoader::loadTexture(const std::string& fileName)
{
#ifndef PITCH_TEXTURE_DIRECTORY
    throw std::runtime_error("Must define the texture directory");
#endif

    const auto textureDir = std::string(PITCH_TEXTURE_DIRECTORY);
    const auto fullFilePath = textureDir + "/" + fileName;
    return loadTextureInfo(fullFilePath);
}

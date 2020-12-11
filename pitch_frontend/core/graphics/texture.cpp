#include "texture.h"

#include <glad/glad.h>

bool Texture::initialized_ = false;

Texture::Texture(const TextureInfo& info)
    : id_(0)
{
    if(!initialized_)
    {
        staticInit();
    }

    glGenTextures(1, &id_);
    bind();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, info.width, info.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, info.data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::Texture(Texture&& rhs) noexcept
{
    id_ = rhs.id_;
    rhs.id_ = 0;
}

Texture& Texture::operator=(Texture&& rhs) noexcept
{
    id_ = rhs.id_;
    rhs.id_ = 0;

    return *this;
}

void Texture::bind() noexcept
{
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::unbind() noexcept
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::staticInit() noexcept
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    initialized_ = true;
}

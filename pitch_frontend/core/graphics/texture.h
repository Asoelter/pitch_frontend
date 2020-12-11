#ifndef TEXTURE_H
#define TEXTURE_H

#include "../util/file_io.h"

class Texture
{
public:
    Texture(const TextureInfo& info);
    Texture(const Texture& rhs) = delete;
    Texture(Texture&& rhs) noexcept;
    ~Texture() = default;

    Texture& operator=(const Texture& rhs) = delete;
    Texture& operator=(Texture&& rhs) noexcept;

    void bind() noexcept;
    void unbind() noexcept;

private:
    static void staticInit() noexcept;

private:
    unsigned id_;

private:
    static bool initialized_;
};

#endif //TEXTURE_H

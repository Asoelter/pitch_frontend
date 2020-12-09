#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "shader.h"

class ShaderProgram
{
public:
    ShaderProgram(VertexShader&& vertexShader, FragmentShader&& fragmentShader);
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram(ShaderProgram&& rhs) noexcept;
    ~ShaderProgram() = default;

    ShaderProgram& operator=(const ShaderProgram&) = delete;
    ShaderProgram& operator=(ShaderProgram&& rhs) noexcept;

    void bind() noexcept;
    void unbind() noexcept;

private:
    void init(VertexShader&& vertexShader, FragmentShader&& fragmentShader) noexcept;
    void throwIfError() const;

private:
    unsigned id_;
};

#endif //SHADER_PROGRAM_H

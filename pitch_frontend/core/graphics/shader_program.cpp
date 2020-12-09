#include "shader_program.h"


#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

ShaderProgram::ShaderProgram(VertexShader&& vertexShader, FragmentShader&& fragmentShader)
    : id_(0)
{
    init(std::move(vertexShader), std::move(fragmentShader));
}

ShaderProgram::ShaderProgram(ShaderProgram&& rhs) noexcept
{
    id_ = rhs.id_;
    rhs.id_ = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& rhs) noexcept
{
    id_ = rhs.id_;
    rhs.id_ = 0;

    return *this;
}

void ShaderProgram::bind() noexcept
{
    glUseProgram(id_);
}

void ShaderProgram::unbind() noexcept
{
    glUseProgram(0);
}

void ShaderProgram::init(VertexShader&& vertexShader, FragmentShader&& fragmentShader) noexcept
{
    //Bind the shaders to local variables so that their destructors will
    //free the shaders once they got out of scope
    const auto lvalVertexShader = std::move(vertexShader);
    const auto lvalFragmentShader = std::move(fragmentShader);

    id_= glCreateProgram();
    glAttachShader(id_, lvalVertexShader.id());
    glAttachShader(id_, lvalFragmentShader.id());
    glLinkProgram(id_);

    throwIfError();
}

void ShaderProgram::throwIfError() const
{
    int success;
    glGetProgramiv(id_, GL_LINK_STATUS, &success);

    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(id_, 512, nullptr, infoLog);
        const auto errorMessage = std::string("Shader program failed to link: ") + infoLog;
        throw std::runtime_error(errorMessage);
    }
}

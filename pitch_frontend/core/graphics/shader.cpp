#include "shader.h"

#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shader::Shader(const std::string& text, unsigned shaderType)
    : id_(0)
{
    init(text, shaderType);
}

Shader::Shader(Shader&& rhs)
{
    id_ = rhs.id_;
    rhs.id_ = 0;
}

Shader::~Shader()
{
    glDeleteShader(id_);
}

Shader& Shader::operator=(Shader&& rhs)
{
    id_ = rhs.id_;
    rhs.id_ = 0;

    return *this;
}

unsigned Shader::id() const noexcept
{
    return id_;
}

void Shader::throwIfError() const
{
    int success;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(id_, 512, nullptr, infoLog);
        const auto errorMessage = std::string("shader failed to compile: ") + infoLog;
        throw std::runtime_error(errorMessage);
    }
}

void Shader::init(const std::string& text, unsigned shaderType)
{
    id_ = glCreateShader(shaderType);
    const auto cText = text.c_str();

    glShaderSource(id_, 1, &cText, nullptr);
    glCompileShader(id_);

    int success;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &success);

    throwIfError();
}

VertexShader::VertexShader(const std::string& text)
    : Shader(text, GL_VERTEX_SHADER)
{
    
}

FragmentShader::FragmentShader(const std::string& text)
    : Shader(text, GL_FRAGMENT_SHADER)
{
    
}

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

void ShaderProgram::setUniform(const std::string& name, float value)
{
    const auto location = glGetUniformLocation(id_, name.c_str());
    glUniform1f(location, value);
}

void ShaderProgram::setUniform(const std::string& name, const Vec3& value)
{
    const auto location = glGetUniformLocation(id_, name.c_str());
    glUniform3fv(location, 1, value.data());
}

void ShaderProgram::setUniform(const std::string& name, const Mat4& value)
{
    const auto location = glGetUniformLocation(id_, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, value.data());
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

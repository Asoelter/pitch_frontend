#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader
{
public:
    Shader(const std::string& text, unsigned shaderType);
    Shader(const Shader& rhs) = delete;
    Shader(Shader&& rhs);
    virtual ~Shader();

    Shader& operator=(const Shader& rhs) = delete;
    Shader& operator=(Shader&& rhs);

    unsigned id() const noexcept;

private:
    void throwIfError() const;
    void init(const std::string& text, unsigned shaderType);

private:
    unsigned id_;
};

struct VertexShader : public Shader
{
    VertexShader(const std::string& text);
};

struct FragmentShader : public Shader
{
    FragmentShader(const std::string& text);
};

#endif //SHADER_H

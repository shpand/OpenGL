#include "string";
#include "unordered_map";

#include "vendor/glm/glm.hpp";

struct ShaderProgramSource
{
    std::string Vertex;
    std::string Fragment;
};


#pragma once
class Shader
{
private:
    unsigned int programID;
    std::string filepath;
    std::unordered_map<std::string, int> uniformLocationCache;
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform1i(const std::string& name, int value);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string & name, const glm::mat4 matrix);

private:
    unsigned int GetUniformLocation(const std::string& name);
    ShaderProgramSource ParseShader(const std::string & filepath) const;
    unsigned int CreateShader(const std::string & vertexShader, const std::string & fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string & source);
};


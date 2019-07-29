#include "Shader.h"

#include <iostream>
#include <fstream>

#include <string>
#include <sstream>

#include <GL/glew.h>
#include "utils/Asserter.h"

Shader::Shader(const std::string & filepath) :filepath(filepath)
{
    ShaderProgramSource programShader = ParseShader(filepath);
    programID = CreateShader(programShader.Vertex, programShader.Fragment);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(programID));
}

void Shader::Bind() const
{
    glUseProgram(programID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform1i(const std::string & name, int value)
{
    const auto uniformLocation = GetUniformLocation(name);
    GLCall(glUniform1i(uniformLocation, value));
}

void Shader::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
    const auto uniformLocation = GetUniformLocation(name);
    GLCall(glUniform4f(uniformLocation, v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string & name, const glm::mat4 matrix)
{
    const auto uniformLocation = GetUniformLocation(name);
    GLCall(glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &matrix[0][0]));
}

unsigned int Shader::GetUniformLocation(const std::string & name)
{
    if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
        return uniformLocationCache[name];
    }

    const auto location = glGetUniformLocation(programID, name.c_str());

    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
    }

    uniformLocationCache[name] = location;

    return location;
}


ShaderProgramSource Shader::ParseShader(const std::string& filepath) const
{
    enum class ShaderType
    {
        None = -1,
        Vertex = 0,
        Fragment = 1
    };

    std::ifstream stream(filepath);

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::None;
    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::Vertex;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::Fragment;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}


unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = static_cast<char*>(alloca(length * sizeof(char)));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment/pixel") << " shader!" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);

        return 0;
    }

    return id;
}

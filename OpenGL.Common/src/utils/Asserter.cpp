#include "Asserter.h"
#include <iostream>


void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
    {

    }
}

bool GLCheckError(const char* functionName, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL error] (" << error << "). " << functionName << file << line << std::endl;
        return false;
    }

    return true;
}

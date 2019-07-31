#pragma once
#include <glm/vec3.hpp>

namespace  OpenGLEngine
{
    class GameObject
    {
    public:
        GameObject();
        ~GameObject();
    private:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    };
}


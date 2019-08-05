#pragma once
#include <glm/vec3.hpp>

namespace  open_gl_engine
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


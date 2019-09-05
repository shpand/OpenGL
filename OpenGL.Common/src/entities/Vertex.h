#pragma once

#include "glm/glm.hpp"

namespace  open_gl_engine {

	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
}
#pragma once

#include <string>

namespace  open_gl_engine {

	struct Texture {
		unsigned int id;
		std::string type;
		std::string path;
	};
}
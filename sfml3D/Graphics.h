#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

//#include "Mesh.h"
#include <SDL3/SDL.h>
#include "Vertices.h"

namespace Render {

	enum DrawMode {
		TRIANGLE,
		WIREFRAME
	};

	class Graphics {
		public:
			static void drawTriangle(SDL_Renderer*& renderer, utils::Vertices const& vertices, DrawMode mode = DrawMode::TRIANGLE);
		private:



	};
}



#endif
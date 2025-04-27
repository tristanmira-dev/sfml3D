#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "Mesh.h"
#include <SFML/Graphics.hpp>


namespace Render {

	enum DrawMode {
		TRIANGLE,
		WIREFRAME
	};

	class Graphics {
		public:
			static void drawTriangle(sf::RenderWindow &context, utils::Mesh::Vertices const &vertices, DrawMode mode = TRIANGLE);
		private:



	};
}



#endif
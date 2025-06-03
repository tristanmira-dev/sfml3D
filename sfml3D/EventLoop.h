#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include "Mesh.h"
#include "GameObject.h"
#include "Matrix.h"
#include "Graphics.h"
#include <SFML/Graphics.hpp>

namespace Main {

	class EventLoop {

		public:
			EventLoop() = default;

			void addGameObject(Entity::GameObject<> const& gameObj);

			void clear();
			void draw(sf::RenderWindow &context, utils::Matrix4x4 &projectionMtx);
			
			Entity::GameObject<> &operator[](int idx);

		private:
			std::vector<Entity::GameObject<>> gameObjCollection;
			utils::TriangleContainer verticesToRender;
	};
}






#endif
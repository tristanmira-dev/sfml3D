#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <SDL3/SDL.h>
#include "Mesh.h"
#include "GameObject.h"
#include "Matrix.h"
#include "Graphics.h"

namespace Main {

	class EventLoop {

		public:
			EventLoop() = default;

			void addGameObject(Entity::GameObject<> const& gameObj);

			void clear();
			void draw(SDL_Renderer*& renderer, SDL_Window*& window, utils::Matrix4x4& projectionMtx, Uint32* pixelBuff);
			
			Entity::GameObject<> &operator[](int idx);

		private:
			std::vector<Entity::GameObject<>> gameObjCollection;
			utils::TriangleContainer verticesToRender;
	};
}






#endif
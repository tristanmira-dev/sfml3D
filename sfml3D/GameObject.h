#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <array>
#include "Mesh.h"
#include "Vector3D.h"
#include "Matrix.h"

/*TODO ALLOW A SIMPLE INTERFACE 3D OBJECTS WITH*/

namespace Entity {

	template<int numOfMesh = 1>
	class GameObject {
		public:


		private:
			std::array<utils::Mesh, numOfMesh> model;
			struct properties {
				utils::Vector3D position;
				utils::Matrix4x4 transformation;
			};
			
	};
}


#endif
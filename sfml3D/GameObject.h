#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <array>
#include "Mesh.h"
#include "Vector3D.h"
#include "Matrix.h"
#include "Color.h"
#include "Camera.h"
#include <string>
#include <initializer_list>

/*TODO ALLOW A SIMPLE INTERFACE 3D OBJECTS WITH*/

namespace Entity {
	struct ModelData {
		utils::Mesh mesh;
		struct Properties {
			utils::Vector3D prevPosition;
			utils::Vector3D position;
			utils::TriangleContainer verticesToRender;
			utils::Matrix4x4 transformation;
		} props;

		void setTransform(utils::Matrix4x4 const& transform);

	};
}

namespace Entity {

	struct EntityInitializer {
		std::string modelPath;
		utils::Color defaultColor;
	};

	template<int numOfMesh = 1>
	class GameObject {
		public:
			utils::Vector3D getCurrentPosition();
			GameObject(std::initializer_list<EntityInitializer> initList, utils::Camera &camera);

			void prepToRender(sf::RenderWindow& context, utils::Matrix4x4 const& projectionMtx);

			void draw(sf::RenderWindow& context, utils::Matrix4x4 const& projectionMtx);

			ModelData& operator[](int idx);



		private:
			std::array<ModelData, numOfMesh> model;
			utils::Camera &camera;
			
	};

}

#include "GameObject_T.h"


#endif
#include "FileManager.h"
#include "GameObject.h"
#include "Graphics.h"
#include "Mesh.h"
#include <SFML/Graphics.hpp>

class SortCriterion {
public:
	bool operator()(utils::VerticesContainerData const& prev, utils::VerticesContainerData const& next) {
		float prevMidZ{};
		float nextMidZ{};
		for (int i{}; i < 3; ++i) {
			prevMidZ += prev.container[i].coordinates.z;
			nextMidZ += next.container[i].coordinates.z;
		}

		return prevMidZ / 2.f > nextMidZ / 2.f;
	}
};

template<int numOfMesh>
utils::Vector3D GameObject<numOfMesh>::getCurrentPosition() { return this->model[0].props.position; }

template<int numOfMesh>
GameObject<numOfMesh>::GameObject(std::initializer_list<EntityInitializer> initList) {

	int idx{};
	for (EntityInitializer const& entity : initList) {
		manager::FileManager::readVertex(entity.modelPath, model[idx].mesh, entity.defaultColor);

		idx++;
	}
}

template<int numOfMesh>
inline void Entity::GameObject<numOfMesh>::prepToRender(sf::RenderWindow& context, utils::Matrix4x4 const& projectionMtx) {


	for (ModelData& modelData : model) {

		modelData.props.verticesToRender = utils::VerticesContainer{};
		for (utils::VerticesContainerData const& vertices : modelData.mesh.verticesContainer.data) {
			utils::Mesh::Vertices translated = vertices.container;
			utils::Mesh::Vertices projected;


			/*ROTATION AROUND Y THEN TRANSLATION BY Z AXIS*/
			utils::Matrix4x4 finalTransform = utils::Matrix4x4{ {1,0,0,0}, {0,1,0,0}, {0,0,1,1.f}, {0,0,0,1} };
			utils::Mesh::transformVertice(finalTransform, translated);
			/*-------------------------------*/

			utils::Vector3D vec1, vec2, normal;

			/*CALCULATE THE NORMAL OF EACH TRIANGLE FACE IN THE PLANE*/
			vec1 = translated[1].coordinates - translated[0].coordinates;
			vec2 = translated[2].coordinates - translated[0].coordinates;
			normal = vec1.cross(vec2); //CROSS PRODUCT BETWEEN TWO VECTORS TO GET THE NORMAL VECTOR
			/*------------------------------------------------------*/

            /*TODO DYNAMIC CAMERA*/
            /*SET THE VECTOR FROM TRIANGLE PT TO CAMERA(0,0,0) IN ORDER TO DO 'CULLING'*/
            utils::Vector3D lineFromCam = translated[0].coordinates /* - Camera Position (Currently at 0,0,0)*/;

            /*CHECK IF THE ANGLE BETWEEN THE NORMAL AND VECTOR FROM CAM IS NEGATIVE(IN FRONT OF THE BACK) THEN CONTINUE WITH PERSPECTIVE PROJECTION*/
            if (lineFromCam.dot(normal) < 0.0f) {

                projected.push_back({ projectionMtx.pMultiply(translated[0].coordinates), translated[0].colorVal });
                projected.push_back({ projectionMtx.pMultiply(translated[1].coordinates), translated[1].colorVal });
                projected.push_back({ projectionMtx.pMultiply(translated[2].coordinates), translated[2].colorVal });

                normal.normalize();


                utils::Vector3D light{
                    0.f,
                    0.f,
                    1.0f
                };
                //light.normalize();

                float dist{ std::fabs(normal.dot(light)) };

                float halfDistX{ context.getSize().x * 0.5f };
                float halfDistY{ context.getSize().y * 0.5f };

                /*SCALE UP TO WINDOW DIMENSIONS AND THEN TRANSLATE TO MIDDLE OF SCREEN*/
                utils::Matrix4x4 transform2 = utils::Matrix4x4{
                    {1, 0, 0, halfDistX},
                    {0, 1, 0, halfDistY},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}
                } *utils::Matrix4x4{
                    {4.f * static_cast<float>(context.getSize().x), 0, 0, 0},
                    {0, 4.f * static_cast<float>(context.getSize().y), 0, 0},
                    {0, 0, 1, 0},
                    {0,0,0,1}
                };

                utils::Mesh::transformVertice(transform2, projected);


                /*TODO FIX LIGHT CALCULATION*/
                projected[0].colorVal = projected[0].colorVal * dist;
                projected[1].colorVal = projected[1].colorVal * dist;
                projected[2].colorVal = projected[2].colorVal * dist;

				modelData.props.verticesToRender.data.push_back(utils::VerticesContainerData{
					projected,
					utils::VerticeData{}
				});

            }
			
		}
	}

}

template<int numOfMesh>
inline void Entity::GameObject<numOfMesh>::draw(sf::RenderWindow &context, utils::Matrix4x4 const& projectionMtx) {
	prepToRender(context, projectionMtx);

	for (ModelData &modelData : model) {
		/*SORT THE PROJECTED VERTICES STARTING FROM THE VERTICES WITH A LARGER Z VALUE(GOING FURTHER FROM PLAYER)
		TO THE VERTICES WITH THE SMALLER Z VALUE(GOING TOWARDS PLAYER) TO DRAW THE VERTICES BEHIND FIRST*/
		std::sort(modelData.props.verticesToRender.data.begin(), modelData.props.verticesToRender.data.end(), SortCriterion{});

		for (utils::VerticesContainerData& vertices : modelData.props.verticesToRender.data) {
			Render::Graphics::drawTriangle(context, vertices.container);
		}
	}

	
}

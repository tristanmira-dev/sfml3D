#include "FileManager.h"
#include "GameObject.h"
#include "Graphics.h"
#include "Camera.h"
#include "Plane.h"
#include "Mesh.h"
#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Entity {
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
	GameObject<numOfMesh>::GameObject(std::initializer_list<EntityInitializer> initList, utils::Camera& camera) : camera{ camera } {

		int idx{};
		for (EntityInitializer const& entity : initList) {
			manager::FileManager::readVertex(entity.modelPath, model[idx].mesh, entity.defaultColor);

			idx++;
		}
	}


	template<int numOfMesh>
	void Entity::GameObject<numOfMesh>::prepToRender(sf::RenderWindow& context, utils::Matrix4x4 const& projectionMtx) {


		for (ModelData& modelData : model) {

			modelData.props.verticesToRender = utils::Mesh::VerticesContainer{};
			for (utils::VerticesContainerData& vertices : modelData.mesh.verticesContainer) {
				utils::VerticesContainerData translated = vertices;
				utils::VerticesContainerData projected;



				/*ROTATION AROUND Y THEN TRANSLATION BY Z AXIS*/
				utils::Mesh::transformVertice(modelData.props.transformation, translated.container);
				/*-------------------------------*/


				/*USED FOR CALCULATING THE NORMAL*/
				utils::Vector3D vec1, vec2;

				/*CALCULATE THE NORMAL OF EACH TRIANGLE FACE IN THE PLANE*/
				vec1 = translated.container[1].coordinates - translated.container[0].coordinates;
				vec2 = translated.container[2].coordinates - translated.container[0].coordinates;
				vertices.data.normal = vec1.cross(vec2); //CROSS PRODUCT BETWEEN TWO VECTORS TO GET THE NORMAL VECTOR
				/*------------------------------------------------------*/

				/*CALCULATE VECTOR FORMED FROM CAMERA TO VERTEX IN WORLD SPACE (LINE FROM CAMERA TO CURRENT VERTICE)*/
				/*SET THE VECTOR FROM TRIANGLE PT TO CAMERA(0,0,0) IN ORDER TO DO 'CULLING'*/
				utils::Vector3D lineFromCam = translated.container[0].coordinates - camera.getPosition();




				/*CAMERA TRANSFORM*/
				utils::Mesh::transformVertice(camera.getTransformation(), translated.container);
				/*-------------------------------*/


				/*CLIPPING*/
				std::array<utils::VerticesContainerData, 2> trianglesFormed{};
				trianglesFormed[0].container.resize(3);
				trianglesFormed[1].container.resize(3);


				utils::triClipAgainstPlane(utils::Vector3D{ 0.f, 0.f, 0.1f }, utils::Vector3D{ 0.f,0.f,1.f }, translated, trianglesFormed[0], trianglesFormed[1]);

				for (int n{}; n < 2; ++n) {
					if (vertices.data.normal.dot(lineFromCam) < 0.0f) {

						projected.container.push_back({ projectionMtx.pMultiply(trianglesFormed[n].container[0].coordinates), trianglesFormed[n].container[0].colorVal });
						projected.container.push_back({ projectionMtx.pMultiply(trianglesFormed[n].container[1].coordinates), trianglesFormed[n].container[1].colorVal });
						projected.container.push_back({ projectionMtx.pMultiply(trianglesFormed[n].container[2].coordinates), trianglesFormed[n].container[2].colorVal });

						vertices.data.normal.normalize();


						utils::Vector3D light{
							0.f,
							0.f,
							1.0f
						};

						float dist{ std::fabs(vertices.data.normal.dot(light)) };

						float halfDistX{ context.getSize().x * 0.5f };
						float halfDistY{ context.getSize().y * 0.5f };

						/*SCALE UP TO WINDOW DIMENSIONS AND THEN TRANSLATE TO MIDDLE OF SCREEN*/
						utils::Matrix4x4 transform2 = utils::Matrix4x4{
							{1, 0, 0, halfDistX},
							{0, 1, 0, halfDistY},
							{0, 0, 1, 0},
							{0, 0, 0, 1}
						} *utils::Matrix4x4{
							{static_cast<float>(context.getSize().x), 0, 0, 0},
							{0, static_cast<float>(context.getSize().y), 0, 0},
							{0, 0, 1, 0},
							{0,0,0,1}
						};

						utils::Mesh::transformVertice(transform2, projected.container);


						/*TODO FIX LIGHT CALCULATION*/
						projected.container[0].colorVal = projected.container[0].colorVal * dist;
						projected.container[1].colorVal = projected.container[1].colorVal * dist;
						projected.container[2].colorVal = projected.container[2].colorVal * dist;

						modelData.props.verticesToRender.push_back(utils::VerticesContainerData{
							projected.container,
							utils::VerticeData{}
							});

					}
				}




			}
		}

	}

	template<int numOfMesh>
	void Entity::GameObject<numOfMesh>::draw(sf::RenderWindow& context, utils::Matrix4x4 const& projectionMtx) {
		prepToRender(context, projectionMtx);

		for (ModelData& modelData : model) {
			/*SORT THE PROJECTED VERTICES STARTING FROM THE VERTICES WITH A LARGER Z VALUE(GOING FURTHER FROM PLAYER)
			TO THE VERTICES WITH THE SMALLER Z VALUE(GOING TOWARDS PLAYER) TO DRAW THE VERTICES BEHIND FIRST*/
			std::sort(modelData.props.verticesToRender.begin(), modelData.props.verticesToRender.end(), SortCriterion{});

			for (utils::VerticesContainerData& vertices : modelData.props.verticesToRender) {
				Render::Graphics::drawTriangle(context, vertices.container);
			}
		}


	}

	template<int numOfMesh>
	ModelData& Entity::GameObject<numOfMesh>::operator[](int idx)
	{
		return model[idx];
	}
}



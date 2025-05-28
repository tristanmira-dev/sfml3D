#include "FileManager.h"
#include "GameObject.h"
#include "Graphics.h"
#include "Camera.h"
#include "Plane.h"
#include "Mesh.h"
#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

namespace Entity {
	class SortCriterion {
	public:
		bool operator()(utils::Triangle const& prev, utils::Triangle const& next) {
			float prevMidZ{};
			float nextMidZ{};
			for (int i{}; i < 3; ++i) {
				prevMidZ += prev.vertices[i].coordinates.z;
				nextMidZ += next.vertices[i].coordinates.z;
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

			modelData.props.verticesToRender = utils::TriangleContainer{};
			for (utils::Triangle& triangle : modelData.mesh.triangleContainer) {
				utils::Triangle translated = triangle;
				utils::Triangle projected;



				/*TRANSFORMATION SET BY USER*/
				utils::Mesh::transformVertice(modelData.props.transformation, translated.vertices);
				/*-------------------------------*/


				/*USED FOR CALCULATING THE NORMAL*/
				utils::Vector3D vec1, vec2;

				/*CALCULATE THE NORMAL OF EACH TRIANGLE FACE IN THE PLANE*/
				vec1 = translated.vertices[1].coordinates - translated.vertices[0].coordinates;
				vec2 = translated.vertices[2].coordinates - translated.vertices[0].coordinates;
				triangle.data.normal = vec1.cross(vec2); //CROSS PRODUCT BETWEEN TWO VECTORS TO GET THE NORMAL VECTOR
				triangle.data.normal.normalize();
				/*------------------------------------------------------*/

				/*CALCULATE VECTOR FORMED FROM CAMERA TO VERTEX IN WORLD SPACE (LINE FROM CAMERA TO CURRENT VERTICE)*/
				/*SET THE VECTOR FROM TRIANGLE PT TO CAMERA(0,0,0) IN ORDER TO DO 'CULLING'*/
				utils::Vector3D lineFromCam = translated.vertices[0].coordinates - camera.getPosition();




				/*CAMERA TRANSFORM*/
				utils::Mesh::transformVertice(camera.getTransformation(), translated.vertices);
				/*-------------------------------*/


				/*CLIPPING*/
				std::array<utils::Triangle, 2> trianglesFormed{};

				utils::CLIP_STATUS status{ utils::triClipAgainstPlane(utils::Vector3D{ 0.f, 0.f, 0.1f }, utils::Vector3D{ 0.f,0.f,1.f }, translated, trianglesFormed[0], trianglesFormed[1]) };

				switch (status) {
					case utils::CLIP_REJECTED:
						continue;

					case utils::ONE_TRI_FORMED:
							if (triangle.data.normal.dot(lineFromCam) < 0.0f) {

								projected.vertices[0] = utils::VertexData { 
									projectionMtx.pMultiply(trianglesFormed[0].vertices[0].coordinates), 
									trianglesFormed[0].vertices[0].colorVal 
								};
								projected.vertices[1] = utils::VertexData{
									projectionMtx.pMultiply(trianglesFormed[0].vertices[1].coordinates), 
									trianglesFormed[0].vertices[1].colorVal
								};
								projected.vertices[2] = utils::VertexData {
									projectionMtx.pMultiply(trianglesFormed[0].vertices[2].coordinates), 
									trianglesFormed[0].vertices[2].colorVal
								};



								utils::Vector3D light{
									0.f,
									0.f,
									1.0f
								};

								float dist{ std::fabs(triangle.data.normal.dot(light)) };

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

								utils::Mesh::transformVertice(transform2, projected.vertices);


								/*TODO FIX LIGHT CALCULATION*/
								projected.vertices[0].colorVal = projected.vertices[0].colorVal * dist;
								projected.vertices[1].colorVal = projected.vertices[1].colorVal * dist;
								projected.vertices[2].colorVal = projected.vertices[2].colorVal * dist;

								modelData.props.verticesToRender.push_back(
									utils::Triangle{
										projected.vertices,
										utils::VerticeMetaData{}
									}
								);

							}
						continue;

					case utils::TWO_TRI_FORMED:
						for (int n{}; n < 2; ++n) {
							if (triangle.data.normal.dot(lineFromCam) < 0.0f) {

								projected.vertices[0] = utils::VertexData { projectionMtx.pMultiply(trianglesFormed[n].vertices[0].coordinates), trianglesFormed[n].vertices[0].colorVal };
								projected.vertices[1] = utils::VertexData { projectionMtx.pMultiply(trianglesFormed[n].vertices[1].coordinates), trianglesFormed[n].vertices[1].colorVal };
								projected.vertices[2] = utils::VertexData { projectionMtx.pMultiply(trianglesFormed[n].vertices[2].coordinates), trianglesFormed[n].vertices[2].colorVal };

								


								utils::Vector3D light{
									0.f,
									0.f,
									1.0f
								};

								float dist{ std::fabs(triangle.data.normal.dot(light)) };

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

								utils::Mesh::transformVertice(transform2, projected.vertices);


								/*TODO FIX LIGHT CALCULATION*/
								projected.vertices[0].colorVal = projected.vertices[0].colorVal * dist;
								projected.vertices[1].colorVal = projected.vertices[1].colorVal * dist;
								projected.vertices[2].colorVal = projected.vertices[2].colorVal * dist;

								modelData.props.verticesToRender.push_back(
									utils::Triangle{
										projected.vertices,
										utils::VerticeMetaData{}
									}
								);

							}
						}
						continue;
				}

			}
		}

	}

	template<int numOfMesh>
	void Entity::GameObject<numOfMesh>::draw(sf::RenderWindow& context, utils::Matrix4x4 const& projectionMtx) {
		prepToRender(context, projectionMtx);

		struct planeData {
			utils::Vector3D normal;
			utils::Vector3D point;

			planeData(utils::Vector3D normal, utils::Vector3D point) : normal{ normal }, point{ point } {}
		};

		std::vector<planeData> clippingPlanes{
			planeData{utils::Vector3D{0.f, 1.f, 0.f}, utils::Vector3D{0.f, 0.f, 0.f}}, //TOP
			planeData{utils::Vector3D{-1.f, 0.f, 0.f}, utils::Vector3D{(float)context.getSize().x, 0.f, 0.f}}, //RIGHT
			planeData{utils::Vector3D{1.f, 0.f, 0.f}, utils::Vector3D{0.f, 0.f, 0.f}}, //LEFT
			planeData{utils::Vector3D{0.f, -1.f, 0.f}, utils::Vector3D{0.f, (float)context.getSize().y, 0.f}} //BOTTOM
		};

		//std::vector<utils::VerticesContainerData> verticesClipped{};
		

		for (ModelData& modelData : model) {

			std::sort(modelData.props.verticesToRender.begin(), modelData.props.verticesToRender.end(), SortCriterion{});


			for (utils::Triangle & triangle : modelData.props.verticesToRender) {
				std::vector<utils::Triangle> clippedTri;

				std::array<utils::Triangle, 2> currentTriData;


				utils::CLIP_STATUS clipStatus{ utils::triClipAgainstPlane(clippingPlanes[0].point, clippingPlanes[0].normal, triangle, currentTriData[0], currentTriData[1]) };

				switch (clipStatus) {
					case utils::CLIP_STATUS::CLIP_REJECTED:
						//clippedTri.push_back(currentTriData);
						continue;
					case utils::CLIP_STATUS::ONE_TRI_FORMED:

						clippedTri.push_back(currentTriData[0]);
						
						break;
					case utils::CLIP_STATUS::TWO_TRI_FORMED:

						clippedTri.push_back(currentTriData[0]);
						clippedTri.push_back(currentTriData[1]);

						break;
				}

				for (int i{ 1 }; i < clippingPlanes.size(); ++i) {
					std::vector<utils::Triangle> currentClippedTri;

					for (utils::Triangle & tri : clippedTri) {
						utils::CLIP_STATUS clipStatus{ utils::triClipAgainstPlane(clippingPlanes[i].point, clippingPlanes[i].normal, tri, currentTriData[0], currentTriData[1]) };

						switch (clipStatus) {
						case utils::CLIP_STATUS::CLIP_REJECTED:
							continue;
							
						case utils::CLIP_STATUS::ONE_TRI_FORMED:

							currentClippedTri.push_back(currentTriData[0]);
							continue;
						case utils::CLIP_STATUS::TWO_TRI_FORMED:

							currentClippedTri.push_back(currentTriData[0]);
							currentClippedTri.push_back(currentTriData[1]);
							continue;
						}

					}

					clippedTri = currentClippedTri;
					
				
				}

				for (utils::Triangle const &tri: clippedTri) {
					Render::Graphics::drawTriangle(context, tri.vertices);
				}

			}



		}


	}

	template<int numOfMesh>
	ModelData& Entity::GameObject<numOfMesh>::operator[](int idx)
	{
		return model[idx];
	}
}



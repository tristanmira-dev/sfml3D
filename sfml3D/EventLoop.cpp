#include "EventLoop.h"
#include "Graphics.h"
#include "Plane.h"
#include "Mesh.h"

namespace {
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
}

namespace Main {

	void EventLoop::addGameObject(Entity::GameObject<> const& gameObj) {
		gameObjCollection.push_back(gameObj);
	}

	void EventLoop::clear() {
		verticesToRender = std::vector<utils::Triangle>{};
	}

	void EventLoop::draw(sf::RenderWindow& context, utils::Matrix4x4& projectionMtx) {
		for (Entity::GameObject<>& gameObj : gameObjCollection) {
			gameObj.prepToRender(context, projectionMtx, verticesToRender);
		}

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


		std::sort(verticesToRender.begin(), verticesToRender.end(), SortCriterion{});




		for (utils::Triangle& triangle : verticesToRender) {


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

					for (utils::Triangle& tri : clippedTri) {
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

				for (utils::Triangle const& tri : clippedTri) {
					Render::Graphics::drawTriangle(context, tri.vertices);
				}

			}



		
	}


	Entity::GameObject<> &EventLoop::operator[](int idx) {
		return gameObjCollection[idx];
	}

}

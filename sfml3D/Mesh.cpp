#include "Mesh.h"

namespace utils {
	

	/*READ INDEXES CONTAINED IN A VECTOR OF INDEXES(srcIdx) FROM SRC VERTICE*/
	Mesh::Mesh(Vertices const& srcVertice, std::vector<VerticeIdx> const& srcIdx) {
		for (const VerticeIdx& verticeIdx : srcIdx) {
			Vertices vertices;
			vertices.reserve(3);
			for (const int& idx : verticeIdx) {
				vertices.push_back(

					{

						Vector3D{ srcVertice[idx].coordinates.x, srcVertice[idx].coordinates.y, srcVertice[idx].coordinates.z },
						0.0f
					
					}
				
				);
			}
			this->verticesContainer.push_back(vertices);
		}

	}

	Mesh& Mesh::operator=(Mesh::Init_List src) {

		for (std::initializer_list<float> const &coords : src) {
			
			int idx{}; //Every 3 coordinates, reset to 0
			Mesh::Vertices vertices;
			float tempCoordinates[3]{};

			for (float const &val : coords) {
				if (idx == 2) {
					vertices.push_back(
						{
							Vector3D{
							tempCoordinates[0],
							tempCoordinates[1],
							val
							},
							0.0f
						});


					idx = 0;
					continue;
				}

				tempCoordinates[idx] = val;

				idx++;
			}
			verticesContainer.push_back(vertices);
		}
		
		return *this;
	}
	VertexData::VertexData(Vector3D coordinates, float colorVal) : coordinates{ coordinates }, colorVal{colorVal} {
	/*EMPTY*/
	}
}
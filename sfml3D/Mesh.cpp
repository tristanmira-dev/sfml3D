#include "Mesh.h"
#include "Color.h"

namespace utils {
	

	/*READ INDEXES CONTAINED IN A VECTOR OF INDEXES(srcIdx) FROM SRC VERTICE*/
	Mesh::Mesh(Vertices const& srcVertice, std::vector<VerticeIdx> const& srcIdx, Color defaultCol) {
		for (const VerticeIdx& verticeIdx : srcIdx) {
			Vertices vertices;
			vertices.reserve(3);
			for (const int& idx : verticeIdx) {
				vertices.push_back(

					{
						Vector3D{ srcVertice[idx].coordinates.x, srcVertice[idx].coordinates.y, srcVertice[idx].coordinates.z },
						defaultCol
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
							}
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
	void Mesh::transformVertice(Matrix4x4& mtx, Vertices& vertices) {
		vertices[0].coordinates = mtx * vertices[0].coordinates;
		vertices[1].coordinates = mtx * vertices[1].coordinates;
		vertices[2].coordinates = mtx * vertices[2].coordinates;
	}
	VertexData::VertexData(Vector3D coordinates, Color colorVal) : coordinates{ coordinates }, colorVal{colorVal} { /*EMPTY*/ }
}
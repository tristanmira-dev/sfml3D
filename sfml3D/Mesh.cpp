#include "Mesh.h"
#include "Vertices.h"
#include "Color.h"

namespace utils {
	

	/*READ INDEXES CONTAINED IN A VECTOR OF INDEXES(srcIdx) FROM SRC VERTICE*/
	Mesh::Mesh(std::vector<VertexData> const& srcVertice, std::vector<VerticeIdx> const& srcIdx, Color defaultCol) {
		for (const VerticeIdx& verticeIdx : srcIdx) {
			Vertices vertices;
			int currentArrayIdx{};
			for (const int& idx : verticeIdx) {
				

				vertices.container[currentArrayIdx] = VertexData{
					Vector3D{ srcVertice[idx].coordinates.x, srcVertice[idx].coordinates.y, srcVertice[idx].coordinates.z },
					defaultCol
				};
				
				++currentArrayIdx;
				
			}
			this->triangleContainer.push_back( 
				Triangle { 
					vertices, 
					utils::VerticeMetaData{} 
				}
			);
		}

	}

	Mesh& Mesh::operator=(Mesh::Init_List src) {

		for (std::initializer_list<float> const &coords : src) {
			
			int idx{}; //Every 3 coordinates, reset to 0
			Vertices vertices;
			float tempCoordinates[3]{};

			for (float const &val : coords) {
				if (idx == 2) {
					vertices.container[idx] = VertexData {
							Vector3D{
								tempCoordinates[0],
								tempCoordinates[1],
								val
							},
							
							Color{}
					};


					idx = 0;
					continue;
				}

				tempCoordinates[idx] = val;

				idx++;
			}
			triangleContainer.push_back(
				Triangle { 
					vertices, 
					VerticeMetaData{} 
				});
		}
		
		return *this;
	}
	void Mesh::transformVertice(Matrix4x4& mtx, Vertices& vertices) {
		vertices.container[0].coordinates = mtx * vertices.container[0].coordinates;
		vertices.container[1].coordinates = mtx * vertices.container[1].coordinates;
		vertices.container[2].coordinates = mtx * vertices.container[2].coordinates;
	}

	void Mesh::transformVertice(Matrix4x4 const& mtx, Vertices& vertices) {
		vertices.container[0].coordinates = mtx * vertices.container[0].coordinates;
		vertices.container[1].coordinates = mtx * vertices.container[1].coordinates;
		vertices.container[2].coordinates = mtx * vertices.container[2].coordinates;
	}
}
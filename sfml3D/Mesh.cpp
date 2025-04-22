#include "Mesh.h"

namespace utils {
	Mesh& Mesh::operator=(Mesh::Init_List src) {

		for (std::initializer_list<float> const &coords : src) {
			
			int idx{}; //Every 3 coordinates, reset to 0
			Mesh::Vertices vertices;
			float sentinel[3]{};

			for (float const &val : coords) {
				if (idx == 2) {
					vertices.push_back(Vector3D{
						sentinel[0],
						sentinel[1],
						val
					});


					idx = 0;
					continue;
				}

				sentinel[idx] = val;

				idx++;
			}
			verticesContainer.push_back(vertices);
		}
		
		return *this;
	}
}
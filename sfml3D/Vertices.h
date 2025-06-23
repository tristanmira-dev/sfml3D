#ifndef VERTICES_H
#define VERTICES_H

#include <array>
#include <vector>
#include "Color.h"
#include "Vector3D.h"

namespace utils {
	struct VertexData {
		Vector3D coordinates;
		Color colorVal;
		VertexData(Vector3D coordinates = Vector3D{}, Color colorVal = Color{});
	};

	struct VerticeMetaData {
		Vector3D normal;
		VerticeMetaData(Vector3D normal = { 0.f, 0.f, 0.f }) : normal{ normal } {};
	};

	struct Vertices {
		std::array<VertexData, 3> container;
		inline VertexData& operator[](int idx) {
			return container[idx];
		}
	};

	//CONTAINER: CONTAINS 3 VERTEX TO MAKE UP A TRIANGLE FACE (STORED IN CONTAINER MEMBER), data(MORE METADATA ABOUT THE 3 VERTICES)
	struct Triangle {
		Vertices vertices; //STL VECTOR CONTAINER OF VERTEX STORED IN CLOCKWISE MANNER 
		VerticeMetaData data;

		Triangle() : vertices{}, data{} {};
		Triangle(Vertices const& vertices, VerticeMetaData data) : vertices{ vertices }, data{ data } {};

	};
	

	using VerticeIdx = std::vector<int>; //VERTICE INDEX BASED ON WAVEFONT MODEL FILE
	using TriangleContainer = std::vector<Triangle>;
}


#endif

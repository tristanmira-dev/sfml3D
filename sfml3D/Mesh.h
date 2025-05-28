#ifndef MESH_H
#define MESH_H

#include <vector>
#include <array>
#include <initializer_list>
#include "Vector3D.h"
#include "Matrix.h"
#include "Color.h"

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

	//CONTAINER: CONTAINS 3 VERTEX TO MAKE UP A TRIANGLE FACE (STORED IN CONTAINER MEMBER), data(MORE METADATA ABOUT THE 3 VERTICES)
	struct Triangle { 
		std::array<VertexData, 3> vertices; //STL VECTOR CONTAINER OF VERTEX STORED IN CLOCKWISE MANNER 
		VerticeMetaData data;

		Triangle() : vertices{}, data{} {};
		Triangle(std::array<VertexData, 3> const &vertices, VerticeMetaData data) : vertices{vertices}, data{data} {};
	};

	using Vertices = std::array<VertexData, 3>; //ARRAY OF TRIANGLE VERTICES (SIZE OF 3 VERTEX DATA)
	using VerticeIdx = std::vector<int>; //VERTICE INDEX BASED ON WAVEFONT MODEL FILE
	using TriangleContainer = std::vector<Triangle>; 

	struct Mesh {
		using Init_List = std::initializer_list<std::initializer_list<float>>; /*Collection of Vertices*/
		



		TriangleContainer triangleContainer;

		Mesh() = default;
		Mesh(std::vector<VertexData> const& srcVertice, std::vector<VerticeIdx> const& srcIdx, Color defaultCol);
		Mesh& operator=(Init_List src);
		static void transformVertice(Matrix4x4& mtx, Vertices& vertices);
		static void transformVertice(Matrix4x4 const& mtx, Vertices& vertices);
	};

}




#endif
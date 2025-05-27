#ifndef MESH_H
#define MESH_H

#include <vector>
#include <initializer_list>
#include "Vector3D.h"
#include "Matrix.h"
#include "Color.h"

/*TODO MODIFY VERTEXDATA TO ARRAY OF SIZE 3 (OPTIMIZE AS CURRENT ARCHITECTURE(AND MANY 3D RENDERERS) ONLY SUPPORTS MODELS MADE UP OF TRIANGLES ANYWAY)*/
/*MAKE INTERACTING WITH VERTICES MORE INTUITIVE, MOVE TYPE DEFENITIONS OUTSIDE OF MESH FOR CONSISTENCY*/


namespace utils {

	struct VertexData {
		Vector3D coordinates;
		Color colorVal;
		VertexData(Vector3D coordinates = Vector3D{}, Color colorVal = Color{});
	};

	struct VerticeData {
		Vector3D normal;
		VerticeData(Vector3D normal = { 0.f, 0.f, 0.f }) : normal{ normal } {};
	};

	//CONTAINER: CONTAINS 3 VERTICES TO MAKE UP A TRIANGLE FACE (STORED IN CONTAINER MEMBER), data(MORE METADATA ABOUT THE 3 VERTICES)
	struct VerticesContainerData { 
		std::vector<VertexData> container; //STL VECTOR CONTAINER OF VERTEX STORED IN CLOCKWISE MANNER 
		VerticeData data;

		VerticesContainerData() : container{}, data{} { container.reserve(3); };
		VerticesContainerData(std::vector<VertexData> const&container, VerticeData data) : container{container}, data{data} {};
	};

	struct Mesh {
		using Init_List = std::initializer_list<std::initializer_list<float>>;
		using Vertices = std::vector<VertexData>; //STL VECTOR CONTAINER OF COORDINATES OF VERTICES
		using VerticeIdx = std::vector<int>;
		using VerticesContainer = std::vector<VerticesContainerData>;



		VerticesContainer verticesContainer;

		Mesh() = default;
		Mesh(Vertices const& srcVertice, std::vector<VerticeIdx> const& srcIdx, Color defaultCol);
		Mesh& operator=(Init_List src);
		static void transformVertice(Matrix4x4& mtx, Vertices& vertices);
		static void transformVertice(Matrix4x4 const& mtx, Vertices& vertices);
	};

}




#endif
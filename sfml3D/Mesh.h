#ifndef MESH_H
#define MESH_H

#include <vector>
#include <initializer_list>
#include "Vector3D.h"



namespace utils {

	struct VertexData {
		Vector3D coordinates;
		float colorVal;

		VertexData(Vector3D coordinates, float colorVal = 0.f);
	};


	struct Mesh {
		using Init_List = std::initializer_list<std::initializer_list<float>>;
		using Vertices = std::vector<VertexData>; //STL VECTOR CONTAINER OF COORDINATES OF VERTICES
		using VerticesContainer = std::vector<Vertices>; //STL VECTOR CONTAINER OF VERTICES STORED IN CLOCKWISE MANNER 
		using VerticeIdx = std::vector<int>;
		VerticesContainer verticesContainer;

		Mesh() = default;
		Mesh(Vertices const &srcVertice, std::vector<VerticeIdx> const &srcIdx);
		Mesh& operator=(Init_List src);
	};

}




#endif
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <initializer_list>
#include "Vector3D.h"



namespace utils {
	struct Mesh {
		using Init_List = std::initializer_list<std::initializer_list<float>>;
		using VerticesContainer = std::vector<std::vector<Vector3D>>; //STL VECTOR CONTAINER OF VERTICES STORED IN CLOCKWISE MANNER 
		using Vertices = std::vector<Vector3D>; //STL VECTOR CONTAINER OF COORDINATES OF VERTICES

		VerticesContainer verticesContainer;

		Mesh& operator=(Init_List src);
	};

}




#endif
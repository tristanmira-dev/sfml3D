#ifndef PLANE_H
#define PLANE_H

#include "Vector3D.h"
#include "Mesh.h"

namespace utils {
	Vector3D calcVectIntersect(Vector3D planeN, Vector3D planeP, Vector3D lineStart, Vector3D lineEnd);

	/*Plane Equation, n.dot(P) - d, see if point lies on the inside half plane by the sign of the return value +ve the point lies on the inside half plane, -ve the point lies on the outside half plane*/
	float pointToPlaneDist(utils::Vector3D const& planeNormal, utils::Vector3D const& point, utils::Vector3D const& planePoint);

	//int triClipAgainstPlane(Vector3D planePoint, Vector3D planeNormal, VerticesContainerData& inputTri, VerticesContainerData& outputTri1, VerticesContainerData& outputTri2);
	int triClipAgainstPlane(Vector3D planePoint, Vector3D planeNormal, VerticesContainerData& inputTri, VerticesContainerData& outputTri1, VerticesContainerData& outputTri2);
}




#endif
#include "Plane.h"
#include "Vector3D.h"
#include "Mesh.h"
#include <iostream>


namespace utils {


	/*Plane Equation, n.dot(P) - d, see if point lies on the inside half plane by the sign of the return value +ve the point lies on the outside half plane(direction of normal), -ve the point lies on the inside half plane(opposite of normal)*/
	float pointToPlaneDist(utils::Vector3D const& planeNormal, utils::Vector3D const& point, utils::Vector3D const& planePoint) {
		return planeNormal.dot(point) - planeNormal.dot(planePoint);
	}

	/*Calculate the intersection between a line and a plane*/
	Vector3D calcVectIntersect(Vector3D planeN, Vector3D planeP, Vector3D lineStart, Vector3D lineEnd) {

		/*SOLVE FOR T AND FIND X, Y, Z BASED ON PARAMETRIC EQUATION OF A LINE*/
		//plane eqn = nx.x + ny.y + nz.z - d = 0 where d = nx.x0 + ny.y0 + nz.z0 
		// x = x0 + at, y = y0 + bt, z = z0 + ct where a, b, z corresponds to the vector coordinates

		float planeD = -planeN.dot(planeP);

		Vector3D lineVect = lineEnd - lineStart;

		float lineConstants = -(planeN.dot(lineStart) + planeD);

		float tConstants = planeN.dot(lineVect);

		float t = lineConstants / tConstants;

		return lineStart + (t*lineVect);
	}

	int triClipAgainstPlane(Vector3D planePoint, Vector3D planeNormal, VerticesContainerData& inputTri, VerticesContainerData& outputTri1, VerticesContainerData& outputTri2) {
		planeNormal.normalize();

		int insidePoints{}; 
		VertexData* insidePointsPtr[3]{};

		int outsidePoints{};
		VertexData* outsidePointsPtr[3]{};

		int trianglesFormed{};

		float d0{ pointToPlaneDist(planeNormal, inputTri.container[0].coordinates, planePoint) };
		float d1{ pointToPlaneDist(planeNormal, inputTri.container[1].coordinates, planePoint) };
		float d2{ pointToPlaneDist(planeNormal, inputTri.container[2].coordinates, planePoint) };

		if (d0 >= 0.f) {
			insidePointsPtr[insidePoints++] = &(inputTri.container[0]);
		} else {
			outsidePointsPtr[outsidePoints++] = &(inputTri.container[0]);
		}

		if (d1 >= 0.f) {
			insidePointsPtr[insidePoints++] = &(inputTri.container[1]);
		} else {
			outsidePointsPtr[outsidePoints++] = &(inputTri.container[1]);
		}

		if (d2 >= 0.f) {
			insidePointsPtr[insidePoints++] = &(inputTri.container[2]);
		} else {
			outsidePointsPtr[outsidePoints++] = &(inputTri.container[2]);
		}


		if (outsidePoints == 3) {
			return 0;
		}

		if (insidePoints == 3) {
			outputTri1 = inputTri;
			return 0;
		}

		if (insidePoints == 1) {
			/*REFACTOR LATER*/
			outputTri1.container[0].colorVal = insidePointsPtr[0]->colorVal;
			outputTri1.container[1].colorVal = outsidePointsPtr[0]->colorVal;
			outputTri1.container[2].colorVal = outsidePointsPtr[1]->colorVal;


			outputTri1.container[0].coordinates = insidePointsPtr[0]->coordinates;
			outputTri1.container[1].coordinates = calcVectIntersect(planeNormal, planePoint,  insidePointsPtr[0]->coordinates, outsidePointsPtr[0]->coordinates);
			outputTri1.container[2].coordinates = calcVectIntersect(planeNormal , planePoint, insidePointsPtr[0]->coordinates, outsidePointsPtr[1]->coordinates);

			return 1;
		}

		if (insidePoints == 2) {

			Vector3D pt1Intersect{
				calcVectIntersect(planeNormal, planePoint, insidePointsPtr[0]->coordinates, outsidePointsPtr[0]->coordinates)
			};

			Vector3D pt2Intersect{
				calcVectIntersect(planeNormal, planePoint, insidePointsPtr[1]->coordinates, outsidePointsPtr[0]->coordinates)
			};

			/*REFACTOR LATER*/
			outputTri1.container[0] = *(insidePointsPtr[0]);
			outputTri1.container[1] = *(insidePointsPtr[1]);
			outputTri1.container[2] = *(outsidePointsPtr[0]);

			/*REFACTOR LATER*/
			outputTri2.container[0] = *(insidePointsPtr[0]);
			outputTri2.container[1] = *(insidePointsPtr[1]);
			outputTri2.container[2] = *(outsidePointsPtr[0]);

			outputTri1.container[0].coordinates = insidePointsPtr[0]->coordinates;
			outputTri1.container[1].coordinates = insidePointsPtr[1]->coordinates;
			outputTri1.container[2].coordinates = pt1Intersect;

			outputTri2.container[0].coordinates = insidePointsPtr[1]->coordinates;
			outputTri2.container[1].coordinates = pt2Intersect;
			outputTri2.container[2].coordinates = pt1Intersect;

			return 2;
		}
		

		return 0;
	}

}
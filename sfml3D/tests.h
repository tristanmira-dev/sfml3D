#ifndef TESTS_HPP
#define TESTS_HPP

#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix.h"
#include "FileManager.h"
#include <cassert>


namespace tests {
	using namespace manager;
	using namespace utils;
	inline void testFileReader() {
		Mesh testMesh{};
		//assert (manager::FileManager::readVertex("./Assets/mesh1.obj", testMesh) == FileManager::READ_OK && "File Read OK");
	}
	inline void vec3DTests() {
		Vector3D a{ 3, 1, 0 }, b{ 1, 2, 5 };

		a += b;

		assert(a == (Vector3D{4, 3, 5}) && "Vec3D sum assignment is not correct");

	}
	inline void additionOverloadVec2D() {
		Vector2D a{ 3,1 }, b{ 1,2 };

		a += b;

		assert(a == (Vector2D{ 4, 3 }) && "Vec2D sum assignment is not correct!");

	}
	inline void matrixTest() {
		float testArr[16]{
			1,2,3,4,
			5,6,7,8,
			9,10,11,12,
			13,14,15,16
		};

		Matrix4x4 mtxObj{
			{1,2,3,4},
			{5,6,7,8 },
			{9,10,11,12},
			{13,14,15,16 }
		};

		assert(mtxObj == testArr && "Matrix Init failed");

	}

	inline void runTests() {
		vec3DTests();
		additionOverloadVec2D();
		matrixTest();
		testFileReader();
	}
}


#endif
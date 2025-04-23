#define _USE_MATH_DEFINES

#include "CommonUtils.h"
#include "Mesh.h"
#include "Vector3D.h"

#include <cmath>

namespace utils {
	float toRad(float degrees) {
		return degrees * (static_cast<float>(M_PI) / 180.0f);
	}
}

std::ostream& operator<<(std::ostream& os, utils::Vector3D const& vec)
{
	os << "x: " << vec.x << " | y: " << vec.y << " | z: " << vec.z;
	return os;
}
std::ostream& operator<<(std::ostream& os, utils::Matrix4x4 const& mtx) {


	for (int i{}; i < mtx.columnSize * mtx.rowSize; ++i) {

		os << (((i % mtx.rowSize) == 0 && i != 0) ? "\n" : "");
		os << mtx.m[i] << " ";
	}

	return os;
}
std::ostream& operator<<(std::ostream& os, std::vector<int> idx) {
	for (int i : idx) {
		os << i << " ";
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, std::vector<std::vector<int>> idx) {
	for (std::vector<int> i : idx) {
		for (int const& x : i) {
			os << x << " ";
		}
		os << '\n';
	}
	return os;
}

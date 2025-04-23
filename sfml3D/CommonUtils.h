#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include "Mesh.h"
#include "Vector3D.h"
#include "Matrix.h"

#include <ostream>

namespace utils {
	float toRad(float degrees);
}

std::ostream& operator<<(std::ostream& os, utils::Vector3D const& vec);
std::ostream& operator<<(std::ostream& os, utils::Matrix4x4 const& mtx);
std::ostream& operator<<(std::ostream& os, std::vector<int> idx);

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& vertices);
#include "CommonUtils_T.h" //PROVIDE DEFINITION FOR TEMPLATE FUNCTIONS

#endif
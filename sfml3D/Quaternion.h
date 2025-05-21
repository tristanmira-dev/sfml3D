#ifndef QUATERNION_H
#define QUATERNION_H
#include "Vector3D.h"

namespace utils {
	struct Quaternion {
		Quaternion(float w, Vector3D vec);

		Quaternion operator*(const Quaternion& quat);
		Quaternion operator*(const Vector3D& vec2);

		void normalise();
		Quaternion conjugate();

		float w;
		Vector3D vec;
	};

}





#endif
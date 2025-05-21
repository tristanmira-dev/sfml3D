#include "Quaternion.h"
#include "Vector3D.h"
#include <cmath>

namespace utils {

	Quaternion::Quaternion(float w, Vector3D vec) : w{ w }, vec{ vec } {
		/*EMPTY BY DESIGN*/
	}
	

	Quaternion Quaternion::operator*(const Vector3D &vec2) {
		return Quaternion{
			-this->vec.dot(vec2),
			this->w * vec2 + this->vec.cross(vec2)
		};

	}

	void Quaternion::normalise() {
		float len{std::sqrtf(this->w*this->w + this->vec.x*this->vec.x + this->vec.y*this->vec.y + this->vec.z*this->vec.z)};

		this->w /= len;
		this->vec.x /= len;
		this->vec.y /= len;
		this->vec.z /= len;


	}

	Quaternion Quaternion::conjugate() {
		return Quaternion(this->w, -this->vec);
	}

	Quaternion Quaternion::operator*(const Quaternion& quat) {
		return Quaternion{
			this->w * quat.w - this->vec.dot(quat.vec),
			this->w * quat.vec + quat.w * this->vec + this->vec.cross(quat.vec)
		};

	}

	

}
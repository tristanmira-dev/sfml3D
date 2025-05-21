#include "Vector3D.h"
#include "Quaternion.h"
#include "CommonUtils.h"


#define _USE_MATH_DEFINES
#include "math.h"

#include <cmath>


namespace utils {

	Vector3D::Vector3D(float x, float y, float z) : x{ x }, y{ y }, z{ z } { /*EMPTY*/ }

	Vector3D& utils::Vector3D::operator+=(Vector3D const& src) {
		this->x += src.x;
		this->y += src.y;
		this->z += src.z;

		return *this;
	}

	Vector3D& Vector3D::operator+=(const float& src) {
		this->x += src;
		this->y += src;
		this->z += src;
		return *this;
	}

	Vector3D Vector3D::operator+(const Vector3D& vec) const {
		return Vector3D(this->x + vec.x, this->y + vec.y, this->z + vec.z);
	}



	void Vector3D::normalize() {
		float len{ this->dist() };
		this->x /= len;
		this->y /= len;
		this->z /= len;
	
	}

	float Vector3D::dist() {
		return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	float Vector3D::dot(Vector3D const& vec) {
		return this->x * vec.x + this->y * vec.y + this->z * vec.z;
	}

	float Vector3D::dot(Vector3D const& vec) const {
		return this->x * vec.x + this->y * vec.y + this->z * vec.z;
	}

	

	Vector3D Vector3D::cross(Vector3D const &vec2) const {
		return Vector3D{
			this->y * vec2.z - this->z * vec2.y,
			this->z * vec2.x - this->x * vec2.z,
			this->x * vec2.y - this->y * vec2.x
		};
	}

	bool Vector3D::operator==(Vector3D const& compare2) {
		return this->x == compare2.x && this->y == compare2.y && this->z == compare2.z;
	}

	Vector3D Vector3D::operator-(Vector3D const& vec2) {

		return Vector3D {
			this->x - vec2.x,
			this->y - vec2.y,
			this->z - vec2.z
		};
	}
	
	void Vector3D::quaternionRotation(float angle, Vector3D vector) {
		Quaternion q{ std::cosf(toRad(angle * 0.5f)), std::sinf(toRad(angle * 0.5f)) * vector };

		q.normalise();

		Quaternion qConjugate = q.conjugate();

		Quaternion result = q * (*this) * qConjugate;

		this->x = result.vec.x; this->y = result.vec.y; this->z = result.vec.z;

	}

	Vector3D Vector3D::operator-() {
		return Vector3D(-this->x, -this->y, -this->z);
	}


	Vector3D operator*(const float& scalar, const utils::Vector3D& src) {
		return Vector3D{src.x * scalar, src.y * scalar, src.z * scalar};
	}

}



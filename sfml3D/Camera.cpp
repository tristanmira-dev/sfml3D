#include "Camera.h"

namespace utils {
	Camera::Camera(Vector3D position) : position { position }, U{ Vector3D{1.f, 0.f, 0.f} }, V{ Vector3D{0.f, 1.f, 0.f} }, N{ Vector3D{0.f, 0.f, 1.f} },
		transformation{
			{U.x, U.y, U.z, -position.x},
			{V.x, V.y, V.z, -position.y},
			{N.x, N.y, N.z, -position.z},
			{0.f, 0.f, 0.f, 1.f}
		}
	{
		/* EMPTY BY DESIGN */
	}
	Matrix4x4 const& Camera::getTransformation() {
		return this->transformation;
	}


	void Camera::translate(float x, float y, float z) {
		position.x = x;
		position.y = y;
		position.z = z;

		transformation(0, 3) = -x;
		transformation(1, 3) = -y;
		transformation(2, 3) = -z;
	}
	Vector3D const& Camera::getPosition() {
		return this->position;
	}
}
#include "Camera.h"
#include "Matrix.h"



namespace utils {
	Camera::Camera(Vector3D position) : position{ position }, N_pointAt{ Vector3D{0, 0.f, 1.f} }, V_upVect{ Vector3D{0.f, 1.f, 0.f} }, U{ V_upVect.cross(N_pointAt) }, cameraHAngle{0.f}, cameraVAngle{0.f}
	{
		V_upVect.normalize();

		///*EXAMPLE ROTATION CODE- TODO REMOVE LATER*/
		//U.quaternionRotation(80.f, V_upVect);
		//N_pointAt = U.cross(V_upVect);
		///*EXAMPLE ROTATION CODE- TODO REMOVE LATER*/


		Matrix4x4 translation;
		translation.setTranslationMatrix(-position);

		worldToCamTransformation = Matrix4x4{
			{U.x, U.y, U.z, 0.f},
			{V_upVect.x, V_upVect.y, V_upVect.z, 0.f},
			{N_pointAt.x, N_pointAt.y, N_pointAt.z, 0.f},
			{0.f, 0.f, 0.f, 1.f}
		};

		transformation =  worldToCamTransformation * translation;


	}
	Matrix4x4 const& Camera::getTransformation() {
		return this->transformation;
	}


	void Camera::translateRight(float x) {
		position += x * U;
		Matrix4x4 translation;
		translation.setTranslationMatrix(-position);

		transformation = worldToCamTransformation * translation;

	}

	void Camera::translateForward(float z) {
		position += z * N_pointAt;
		Matrix4x4 translation;
		translation.setTranslationMatrix(-position);

		transformation = worldToCamTransformation * translation;

	}

	Vector3D const& Camera::getPosition() {
		return this->position;
	}
	void Camera::incrementAngle()
	{

	}
}
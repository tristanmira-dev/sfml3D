#include "Camera.h"
#include "Matrix.h"
#include <iostream>


namespace utils {
	Camera::Camera(Vector3D position) : position{ position }, N_pointAt{ Vector3D{0, 0.f, 1.f} }, V_upVect{ Vector3D{0.f, 1.f, 0.f} }, U{ V_upVect.cross(N_pointAt) }, cameraHAngle{0.f}, cameraVAngle{0.f}
	{

		Matrix4x4 translation;
		translation.setTranslationMatrix(-position);

		worldToCamTransformation = Matrix4x4{
			{U.x, U.y, U.z, 0.f},
			{V_upVect.x, V_upVect.y, V_upVect.z, 0.f},
			{N_pointAt.x, N_pointAt.y, N_pointAt.z, 0.f},
			{0.f, 0.f, 0.f, 1.f}
		};

		transformation = worldToCamTransformation * translation;


	}
	Matrix4x4 const& Camera::getTransformation() {
		return this->transformation;
	}

	/*Operate on Camera's position in world coordinates*/
	void Camera::translateRight(float x) {
		position += x * U;
		Matrix4x4 translation;
		translation.setTranslationMatrix(-position);

		transformation = worldToCamTransformation * translation;

	}

	/*Operate on Camera's position in world coordinates*/
	void Camera::translateForward(float z) {

		/*MOVE PARALLEL TO Z AXIS*/
		Vector3D dirVec{ N_pointAt };
		dirVec.quaternionRotation(-cameraVAngle, U);

		position += z * dirVec;
		Matrix4x4 translation;
		translation.setTranslationMatrix(-position);

		transformation = worldToCamTransformation * translation;

	}

	void Camera::incDecYaw(float value) {
		this->cameraHAngle += value;
		this->updateUVN();
	}

	void Camera::incDecPitch(float value) {

		this->cameraVAngle += value;
		this->updateUVN();
	}

	Vector3D const& Camera::getPosition() {
		return this->position;
	}
	void Camera::updateUVN() {

		Vector3D YAxis = Vector3D{ 0.f, 1.f, 0.f };
		Vector3D View = Vector3D{ 0.f, 0.f, 1.f };

		View.quaternionRotation(cameraHAngle, YAxis);

		/*CROSS PRODUCT BETWEEN ORTHOGONAL VECTORS RESULT IN A UNIT VECTOR, SO NO NEED TO NORMALIZE*/
		U = YAxis.cross(View);
		View.quaternionRotation(cameraVAngle, U);

		V_upVect = View.cross(U);
		N_pointAt = View;


		Matrix4x4 translation;
		translation.setTranslationMatrix(-position);

		worldToCamTransformation = Matrix4x4{
			{U.x, U.y, U.z, 0.f},
			{V_upVect.x, V_upVect.y, V_upVect.z, 0.f},
			{N_pointAt.x, N_pointAt.y, N_pointAt.z, 0.f},
			{0.f, 0.f, 0.f, 1.f}
		};

		transformation = worldToCamTransformation * translation;

	}


}
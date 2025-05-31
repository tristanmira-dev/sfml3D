#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3D.h"
#include "Matrix.h"


namespace utils {
	/*FOLLOWING UVN, U LEFT/RIGHT AXIS, V UP AXIS, N FORWARD AXIS*/
	class Camera {
		public:
			Camera(Vector3D position);
			Matrix4x4 const& getTransformation();
			void translateRight(float x);
			void translateForward(float z);
			Vector3D const& getPosition();
			void updateUVN();
			void incDecYaw(float value);
			void incDecPitch(float value);

		private:
			Vector3D position;
			Vector3D N_pointAt;
			Vector3D V_upVect;
			Vector3D U;
			Matrix4x4 worldToCamTransformation;
			Matrix4x4 transformation;
			float cameraHAngle;
			float cameraVAngle;

	};
}

#endif


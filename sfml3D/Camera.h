#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3D.h"
#include "Matrix.h"


namespace utils {
	class Camera {
		public:
			Camera(Vector3D position);
			Matrix4x4 const& getTransformation();
			void translateRight(float x);
			void translateForward(float z);
			Vector3D const& getPosition();

			/*REMOVE LATER, JUST TESTING*/
			void incrementAngle();

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


#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3D.h"
#include "Matrix.h"


namespace utils {
	class Camera {
		public:
			Camera(Vector3D position);
			Matrix4x4 const& getTransformation();
			void translate(float x, float y, float z);
			Vector3D const& getPosition();

		private:
			Vector3D position;
			Vector3D U;
			Vector3D V;
			Vector3D N;
			Matrix4x4 transformation;


	};
}

#endif


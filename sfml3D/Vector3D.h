#ifndef VECTOR3D_H
#define VECTOR3D_H


namespace utils {

	union Vector3D {
		struct {
			float x;
			float y;
			float z;
		};
		float xy[3];

		Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f);
		Vector3D(Vector3D const& src) = default;
		Vector3D& operator=(Vector3D const& src) = default;
		Vector3D& operator+=(Vector3D const& src);
		Vector3D& operator+=(const float& src);
		void normalize();
		float dist();
		float dot(Vector3D const& vec);
		bool operator==(Vector3D const& compare2);
		Vector3D operator-(Vector3D const& vec2);

		Vector3D cross(const Vector3D& src) const;

	};
}

#endif
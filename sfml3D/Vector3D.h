#ifndef VECTOR3D_H
#define VECTOR3D_H


namespace utils {

	struct Vector3D {
		
		float x;
		float y;
		float z;

		Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f);
		Vector3D(Vector3D const& src) = default;
		Vector3D& operator=(Vector3D const& src) = default;
		Vector3D& operator+=(Vector3D const& src);
		Vector3D& operator+=(const float& src);
		Vector3D operator+(const Vector3D& vec) const;
		void normalize();
		float dist();
		float dot(Vector3D const& vec);
		float dot(Vector3D const& vec) const;
		bool operator==(Vector3D const& compare2);
		Vector3D operator-(Vector3D const& vec2);
		void quaternionRotation(float angle, Vector3D vector);
		Vector3D operator-();

		Vector3D cross(const Vector3D& src) const;

	};

	Vector3D operator*(const float& scalar, const utils::Vector3D& src);
}

#endif
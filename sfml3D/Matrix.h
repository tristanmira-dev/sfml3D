#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <cstddef>
#include <SFML/Graphics.hpp>
#include <ostream>
#include "Vector3D.h"


namespace utils {

	/* Matrix multiplication order following -> Matrix * column matrix */
	struct Matrix4x4 {
		float m[16];
		int rowSize{ 4 };
		int columnSize{ 4 };


		Matrix4x4();
		Matrix4x4(std::initializer_list<std::initializer_list<float>> init);
		

		void setRotationX(float angle);
		void setRotationY(float angle);

		/*Perspective Matrix multiplication*/
		Vector3D pMultiply(Vector3D const& vec);
		Vector3D pMultiply(Vector3D const& vec) const;

		//Setters for Special Matrices
		void setProjectionMatrix(sf::RenderWindow const& context, float fNear, float fFar, float fFov);

		//Array Indexing
		float& operator()(std::size_t row, std::size_t column);
		float const& operator()(std::size_t row, std::size_t column) const;
		Vector3D operator*(Vector3D const& vec);
		Vector3D operator*(Vector3D const& vec) const;
		Matrix4x4 operator*(Matrix4x4 const& mtx);
		bool operator==(Matrix4x4 const &);
		bool operator==(float const (&arr)[16]);

	};

}



#endif
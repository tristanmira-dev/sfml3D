#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <cstddef>
#include <SFML/Graphics.hpp>
#include <ostream>
#include "Vector3D.h"
	
namespace utils {

	struct Matrix4x4 {
		float m[16];
		int rowSize{ 4 };
		int columnSize{ 4 };


		Matrix4x4();
		Matrix4x4(std::initializer_list<std::initializer_list<float>> init);

		//Setters for Special Matrices
		void setProjectionMatrix(sf::RenderWindow const& context, float fNear, float fFar, float fFov);

		//Array Indexing
		float& operator()(std::size_t row, std::size_t column);
		float const& operator()(std::size_t row, std::size_t column) const;
		Vector3D operator*(Vector3D const& vec);

		void setRotationX(float angle);

		Vector3D pMultiply(Vector3D const& vec);


		bool operator==(Matrix4x4 const &);
		bool operator==(float const (&arr)[16]);

	};

	std::ostream& operator<<(std::ostream& os, Matrix4x4 const& mtx);


}



#endif
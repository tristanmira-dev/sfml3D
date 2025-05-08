#include "Matrix.h"
#include "CommonUtils.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace utils {
	Matrix4x4::Matrix4x4() : m{0}{}
	Matrix4x4::Matrix4x4(std::initializer_list<std::initializer_list<float>> init) : m{ 0.0f } {

		int rowIdx{};
		int columnIdx{};

		for (std::initializer_list<float> const& row : init) {
			for (float const& column : row) {
				m[rowIdx * rowSize + columnIdx] = column;
				++columnIdx;
			}
			columnIdx = 0;
			++rowIdx;
		}
	}

	void Matrix4x4::setProjectionMatrix(sf::RenderWindow const &context, float fNear, float fFar, float fFov){
		float aspectRatio{static_cast<float>(context.getSize().y) / static_cast<float>(context.getSize().x)};
		float fFovRad{ 1.0f / tanf(utils::toRad(fFov * 0.5f)) };


		float t = fFovRad * fNear;
		float r = t * aspectRatio;



		(*this)(0, 0) = r;
		(*this)(1, 1) = t;
		(*this)(2, 2) = (-fNear - fFar) / (fNear - fFar);
		(*this)(2, 3) = (2 * fNear * fFar) / (fNear - fFar);
		(*this)(3, 2) = 1;
		
	}


	float& Matrix4x4::operator()(std::size_t row, std::size_t column) {
		return this->m[row * this->rowSize + column];
	}

	float const& Matrix4x4::operator()(std::size_t row, std::size_t column) const {
		return this->m[row * this->rowSize + column];
	}
	
	bool Matrix4x4::operator==(Matrix4x4 const &cmp)
	{
		int size = rowSize * columnSize;
		for (int i{}; i < size; ++i) {
			if (this->m[i] != cmp.m[i]) {
				return false;
			}
		}
		return true;
	}
	
	bool Matrix4x4::operator==(float const(&cmp)[16])
	{
		int size = rowSize * columnSize;
		for (int i{}; i < size; ++i) {
			if (this->m[i] != cmp[i]) {
				return false;
			}
		}
		return true;
	}
	
	/*Perspective matrix multiplication with vector*/
	Vector3D Matrix4x4::pMultiply(Vector3D const& vec) {
		float w = ((*this)(3, 0) * vec.x + (*this)(3, 1) * vec.y + (*this)(3, 2) * vec.z + (*this)(3, 3) * 1);

		w = (w == 0.0f ? 1.0f : w);

		return Vector3D{
			((*this)(0,0) * vec.x + (*this)(0,1) * vec.y + (*this)(0,2) * vec.z) / w,
			((*this)(1,0) * vec.x + (*this)(1,1) * vec.y + (*this)(1,2) * vec.z) / w,
			((*this)(2,0) * vec.x + (*this)(2,1) * vec.y + (*this)(2,2) * vec.z + (*this)(2,3)) / w
		};
	}

	/*Perspective matrix multiplication with vector CONST*/
	Vector3D Matrix4x4::pMultiply(Vector3D const& vec) const {
		float w = ((*this)(3, 0) * vec.x + (*this)(3, 1) * vec.y + (*this)(3, 2) * vec.z + (*this)(3, 3) * 1);

		w = (w == 0.0f ? 1.0f : w);

		return Vector3D{
			((*this)(0,0) * vec.x + (*this)(0,1) * vec.y + (*this)(0,2) * vec.z) / w,
			((*this)(1,0) * vec.x + (*this)(1,1) * vec.y + (*this)(1,2) * vec.z) / w,
			((*this)(2,0) * vec.x + (*this)(2,1) * vec.y + (*this)(2,2) * vec.z + (*this)(2,3)) / w
		};
	}

	Vector3D Matrix4x4::operator*(Vector3D const& vec) {
		/*float w = ((*this)(3, 0) * vec.x + (*this)(3, 1) * vec.y + (*this)(3, 2) * vec.z + (*this)(3, 3) * 1);

		w = (w == 0.0f ? 1.0f : w);*/

		return Vector3D{
			((*this)(0,0) * vec.x + (*this)(0,1) * vec.y + (*this)(0,2) * vec.z + (*this)(0,3)),
			((*this)(1,0) * vec.x + (*this)(1,1) * vec.y + (*this)(1,2) * vec.z + (*this)(1,3)),
			((*this)(2,0) * vec.x + (*this)(2,1) * vec.y + (*this)(2,2) * vec.z + (*this)(2,3))
		};
	}

	Vector3D Matrix4x4::operator*(Vector3D const& vec) const {
		return Vector3D{
			((*this)(0,0) * vec.x + (*this)(0,1) * vec.y + (*this)(0,2) * vec.z + (*this)(0,3)),
			((*this)(1,0) * vec.x + (*this)(1,1) * vec.y + (*this)(1,2) * vec.z + (*this)(1,3)),
			((*this)(2,0) * vec.x + (*this)(2,1) * vec.y + (*this)(2,2) * vec.z + (*this)(2,3))
		};;
	}

	Matrix4x4 Matrix4x4::operator*(Matrix4x4 const& mtx)
	{
		Matrix4x4 newMtx;
		for (int row{}; row < this->rowSize; ++row) {
			for (int column{}; column < this->columnSize; ++column) {
				float sum = 0.0f;
				for (int col2{}; col2 < this->columnSize; ++col2) {
					sum += (*this)(row, col2) * mtx(col2, column);
				}
				newMtx(row, column) = sum;
			}
		}


		return newMtx;
	}

	void Matrix4x4::setRotationX(float angle) {
		float rad = toRad(angle);
		(*this)(0, 0) = 1.f;
		(*this)(1, 1) = cosf(rad);
		(*this)(1, 2) = -sinf(rad);
		(*this)(2, 1) = sinf(rad);
		(*this)(2, 2) = cosf(rad);
		(*this)(3, 3) = 1.f;
	}

	void Matrix4x4::setRotationY(float angle) {
		float rad = toRad(angle);
		(*this)(0, 0) = cosf(rad); 
		(*this)(0, 2) = sinf(rad);
		(*this)(1, 1) = 1.f;
		(*this)(2, 0) = -sinf(rad);
		(*this)(2, 2) = cosf(rad);
		(*this)(3, 3) = 1.f;
	}


}


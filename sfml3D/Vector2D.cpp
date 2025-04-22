#include "Vector2D.h"

namespace utils {
	Vector2D::Vector2D(float x, float y) : x{x}, y{y} { /*EMPTY*/ }
	Vector2D& Vector2D::operator+=(Vector2D const& src) {
		this->x += src.x;
		this->y += src.y;

		return *this;
	}

	bool Vector2D::operator==(Vector2D const& compare2) {
		return this->x == compare2.x && this->y == compare2.y;
	}

}
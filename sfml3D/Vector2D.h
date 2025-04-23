#ifndef VECTOR2D_H
#define VECTOR2D_H

namespace utils {
	struct Vector2D {

			float x;
			float y;
			
			Vector2D(float x = 0.0f, float y = 0.0f);
			Vector2D(Vector2D const& src) = default;
			Vector2D& operator=(Vector2D const& src) = default;
			Vector2D& operator+=(Vector2D const& src);
			bool operator==(Vector2D const& compare2);
	};
}




#endif
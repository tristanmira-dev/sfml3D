#ifndef COLOR_H
#define COLOR_H
#include <SFML/Graphics.hpp>

namespace utils {
	struct Color {
		float r;
		float g;
		float b;
		float a;

		Color(float r = 0.f, float g = 0.f, float b = 0.f, float a = 255.f);
		Color operator*(float scalar);
		operator sf::Color() const;
		
	};
}





#endif
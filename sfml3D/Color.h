#ifndef COLOR_H
#define COLOR_H
#include <cstdint>

namespace utils {
	struct Color {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255);
		Color operator*(float scalar);
		/*operator sf::Color() const;*/
		
	};
}





#endif
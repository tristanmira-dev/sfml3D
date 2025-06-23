#include "Color.h"
#include <cstdint>

namespace utils {
	Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r{ r }, g{ g }, b{ b }, a{ a } { /*EMPTY BY DESIGN*/ }

	Color Color::operator*(float scalar) {

		return Color(static_cast<uint8_t>(r*scalar), static_cast<uint8_t>(g * scalar), static_cast<uint8_t>(b * scalar), a);
	}
}

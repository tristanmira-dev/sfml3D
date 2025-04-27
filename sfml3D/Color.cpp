#include "Color.h"
#include <SFML/Graphics.hpp>

namespace utils {
	Color::Color(float r, float g, float b, float a) : r{ r }, g{ g }, b{ b }, a{ a } { /*EMPTY BY DESIGN*/ }

	Color Color::operator*(float scalar) {
		return Color(r*scalar, g * scalar, b * scalar, a);
	}

	Color::operator sf::Color() const
	{
		return sf::Color{ static_cast<sf::Uint8>(this->r), static_cast<sf::Uint8>(this->g), static_cast<sf::Uint8>(this->b), static_cast<sf::Uint8>(this->a) };
	}


}

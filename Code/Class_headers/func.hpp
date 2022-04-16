#pragma once

#include "../config.hpp"

namespace DeltaEngine
{
	json returnJson(jsonStr const jsonPath); // Returns a json array from a .json file.

	template <typename T>
	bool inVector(std::vector<T>&, T&);
	template <typename T>
	void eraseElem(std::vector<T>&, T&);

	template <typename T, typename U>
	sf::Vector2<T> operator*(sf::Vector2<T>& lhs, U rhs);
	template <typename T, typename U>
	sf::Vector2<T> operator*(U lhs, sf::Vector2<T>& rhs);
	template <typename T, typename U>
	sf::Vector2<T> operator/(sf::Vector2<T>& lhs, U rhs);
	template <typename T, typename U>
	sf::Vector2<T> operator/(U lhs, sf::Vector2<T>& rhs);
}

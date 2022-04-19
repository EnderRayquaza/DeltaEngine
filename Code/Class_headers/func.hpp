#pragma once

#include "../config.hpp"

namespace DeltaEngine
{
	json returnJson(jsonStr const jsonPath); // Returns a json array from a .json file.

	template <typename T>
	bool inVector(const std::vector<T>&, const T&);
	template <typename T>
	void eraseElem(const std::vector<T>&, const T&);

	template <typename T, typename U>
	sf::Vector2<T> operator*(const sf::Vector2<T>& lhs, const U rhs);
	template <typename T, typename U>
	sf::Vector2<T> operator*(const U lhs, const sf::Vector2<T>& rhs);
	template <typename T, typename U>
	sf::Vector2<T> operator/(const sf::Vector2<T>& lhs, const U rhs);
	template <typename T, typename U>
	sf::Vector2<T> operator/(const U lhs, const sf::Vector2<T>& rhs);
}

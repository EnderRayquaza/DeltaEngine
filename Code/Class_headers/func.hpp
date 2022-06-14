#pragma once

#include "../config.hpp"

namespace DeltaEngine
{
	json returnJson(jsonStr const jsonPath); // Returns a json array from a .json file.

	template <typename T>
	bool inVector(std::vector<T>& vec, T& item)
	{
		return std::find(vec.begin(), vec.end(), item) != vec.end();
	}

	template <typename T>
	void eraseElem(std::vector<T>& vec, T& item)
	{
		if (inVector(vec, item))
		{
			const auto& it{ std::find(vec.begin(), vec.end(), item) };
			vec.erase(it, it);

		}
	}


	template <typename T, typename U>
	sf::Vector2<T> operator*(const sf::Vector2<T>& lhs, const U rhs)
	{
		sf::Vector2<T> vec{};
		vec.x = lhs.x * rhs;
		vec.y = lhs.y * rhs;
		return vec;
	}

	template <typename T, typename U>
	sf::Vector2<T> operator*(const U lhs, const sf::Vector2<T>& rhs)
	{
		return rhs * lhs;
	}

	template <typename T, typename U>
	sf::Vector2<T> operator/(const sf::Vector2<T>& lhs, const U rhs)
	{
		return lhs * (double)(1 / rhs);
	}

	template <typename T, typename U>
	sf::Vector2<T> operator/(const U lhs, const sf::Vector2<T>& rhs)
	{
		return rhs / lhs;
	}
}

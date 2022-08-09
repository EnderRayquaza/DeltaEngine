#pragma once

#include "../config.hpp"

namespace DeltaEngine
{
	json returnJson(jsonStr const jsonPath); // Returns a json array from a .json file.

	double det(Vec2f const v, Vec2f const u);

	bool segmentCut(Vertex, Vertex, Vertex, Vertex);

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

}

	template <typename T, typename U>
	sf::Vector2<T> operator*(const sf::Vector2<T>& lhs, const sf::Vector2<U>& rhs)
{
	sf::Vector2<T> vec{};
	vec.x = lhs.x * rhs.x;
	vec.y = lhs.y * rhs.y;
	return vec;
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
	sf::Vector2<T> operator/(const sf::Vector2<T>& lhs, const sf::Vector2<U>& rhs)
	{
		sf::Vector2<T> vec{};
		vec.x = lhs.x / rhs.x;
		vec.y = lhs.y / rhs.y;
		return vec;
	}

	template <typename T, typename U>
	sf::Vector2<T> operator/(const sf::Vector2<T>& lhs, const U rhs)
	{
		if(rhs != 0)
			return lhs * (double)(1 / rhs);
		else
		{
			//std::cerr << "Error division by 0" << std::endl;
			return lhs;
		}
	}

	template <typename T, typename U>
	sf::Vector2<T> operator/(const U lhs, const sf::Vector2<T>& rhs)
	{
		if (lhs != 0)
		{
			return rhs / lhs;
		}
		else
		{
			//std::cerr << "Error division by 0" << std::endl;
			return rhs;
		}
	}

#pragma once

#include "config.hpp"
#include "Identifiable.hpp"

using json = nlohmann::json;

namespace DeltaEngine
{
	enum class moveType
	{
		Static,
		Kinematic,
		Dynamic
	};

	enum class collisionType
	{
		Nothing,
		Decor,
		Ground,
		ObjectA,
		ObjectB
	};

	typedef std::vector<collisionType> collisionTargets;

	enum ErrorType
	{
		FILE_NOT_FOUND,
		INDEX_OUT_OF_RANGE,
		SWITCH_DEFAULT,
		OTHER
	};

	void error(std::string errText, std::string fileName, uint line, ErrorType, bool stop=false);

	json returnJson(jsonStr const jsonPath); // Returns a json array from a .json file.

	template <typename T>
	bool inVector(std::vector<T>, T&);

	template <typename T>
	sf::Vector2<T> operator*(sf::Vector2<T>& lhs, int rhs);
	template <typename T>
	sf::Vector2<T> operator*(int lhs, sf::Vector2<T>& rhs);
	template <typename T>
	sf::Vector2<T> operator/(sf::Vector2<T>& lhs, int rhs);
	template <typename T>
	sf::Vector2<T> operator/(int lhs, sf::Vector2<T>& rhs);

}
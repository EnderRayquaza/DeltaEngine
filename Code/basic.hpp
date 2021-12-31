#pragma once

#include "config.hpp"

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

	struct Id
	{
		int intKey{0};
		std::string strKey{""};

		bool isEgal(Id& rhs);
	};

	struct Vertex
	{
		int x, y;
	};

	struct AABB
	{
		int x, y, w, h;
	};

	struct Shape
	{
		std::vector<Vertex> vertices;
	};

	bool operator==(Id lhs, Id rhs); //Compares 2 ID.

	bool operator!=(Id lhs, Id rhs); //Compares 2 ID.

	json returnJson(std::string jsonPath); // Returns a json array from a .json file.

	Id createId(std::vector<Id> staticList);

	template <typename T>
	sf::Vector2<T> operator*(sf::Vector2<T>& lhs, int rhs);
	template <typename T>
	sf::Vector2<T> operator*(int lhs, sf::Vector2<T>& rhs);
}

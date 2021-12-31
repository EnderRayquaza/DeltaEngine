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

		bool isEgal(Id const rhs) const noexcept;
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

	bool operator==(Id const lhs, Id const rhs); //Compares 2 ID.

	bool operator!=(Id const lhs, Id const rhs); //Compares 2 ID.

	json returnJson(std::string jsonPath); // Returns a json array from a .json file.

	Id createId(std::vector<Id> staticList);

	template <typename T>
	sf::Vector2<T> operator*(sf::Vector2<T>& lhs, int rhs);
	template <typename T>
	sf::Vector2<T> operator*(int lhs, sf::Vector2<T>& rhs);

	class Identifiable
	{
	public:
		Identifiable();
		Identifiable(Identifiable&&) = delete;
		Identifiable(const Identifiable&) = delete;
		~Identifiable() = default;

	protected:
		static std::vector<Id> listId;
		Id const m_id;
	};
}

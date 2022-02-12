﻿#pragma once

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

	typedef std::vector<collisionType> collisionTargets;

	struct Id
	{
		int intKey{0};
		std::string strKey{""};

		bool isEgal(Id const rhs) const noexcept;
	};

	/*struct Vertex
	{
		int x, y;
	};*/

	struct AABB
	{
		void move(Vec2i);

		int x, y, w, h;
	};

	class Shape
	{
	public:
		Shape(std::vector<Vertex>);
		void move(Vec2i);

		friend class Contact;
		friend class Impact;
		friend bool pointInShape(Vertex point, Shape);
	protected:
		std::vector<Vertex> m_vertices;
		AABB m_aabb;
	};

	class Identifiable : public sf::NonCopyable
	{
	public:
		Identifiable();
		~Identifiable() = default;

		Id get_id() const noexcept;

		friend bool operator==(Identifiable& const, Identifiable& const);

		friend bool operator!=(Identifiable& const, Identifiable& const );

	protected:
		static std::vector<Id> listId;
		Id const m_id;
	};

	bool operator==(Id const lhs, Id const rhs); //Compares 2 ID.

	bool operator!=(Id const lhs, Id const rhs); //Compares 2 ID.

	bool operator==(Identifiable& const lhs, Identifiable& const rhs);

	bool operator!=(Identifiable& const lhs, Identifiable& const rhs);

	json returnJson(std::string const jsonPath); // Returns a json array from a .json file.

	AABB findAABBfromShape(Shape& const shape);

	float findSurface(Shape& const shape);

	Id createId(std::vector<Id> staticList);

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
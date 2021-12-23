//basic_struct.hpp
#pragma once

#include "../DeltaEngine.hpp"

namespace DeltaEngine
{
	struct AABB;
	struct Vertex;
	struct Shape;
	class Vector;

	AABB findAABBfromShape(const Shape&);
	float aera(const Shape&);
	Vector operator+(const Vector&, const Vector&);
	Vector operator-(const Vector&, const Vector&);
	Vector operator*(const Vector&, const double);
	Vector operator/(const Vector&, const double);
	double operator*(const Vector&, const Vector&);
	std::ostream& operator<<(std::ostream&, const Vector&);

	struct AABB
	{
		int x, y, w, h;

		AABB(int = 0, int = 0, int = 0, int = 0);
		AABB(sf::Vector2i, sf::Vector2i);
		Vertex get_vertex(int index) const;
	};

	struct Vertex
	{
		int x, y;

		Vertex(int, int);
		Vertex(sf::Vector2i);
		Vertex(sf::Vertex);
	};

	struct Shape
	{
		std::vector<Vertex> vertices;

		Shape() = default;
		Shape(std::vector<Vertex>);
		Shape(sf::VertexArray);

		void move(const Vector&);
	};

	class Vector
	{
	public:
		Vector(double = 0, double = 0);
		Vector(sf::Vector2f);
		~Vector() = default;

		Vector& operator+=(const Vector&);
		Vector& operator-=(const Vector&);
		Vector& operator*=(const double);
		Vector& operator/=(const double);

		double get_standard() const;

		double calculStandard();
		double scalarProduct(const Vector&) const;
		double getAngle(const Vector&) const;
		Vector getUnit() const;
		sf::Vector2f to_sfV2f() const;

		double x, y;

	protected:
		double m_standard;

	};
}
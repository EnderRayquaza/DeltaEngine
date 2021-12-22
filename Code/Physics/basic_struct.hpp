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

		AABB(int, int, int, int);
		AABB(sf::Vector2i, sf::Vector2i);
		Vertex get_vertex(int index);
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

		Shape(std::vector<Vertex>);
		Shape(sf::VertexArray);
	};

	class Vector
	{
	public:
		Vector(double, double);
		Vector(sf::Vector2f);
		~Vector() = default;

		Vector& operator+=(const Vector&);
		Vector& operator-=(const Vector&);
		Vector& operator*=(const double);
		Vector& operator/=(const double);

		double get_standard() const noexcept;

		double calculStandard();
		double scalarProduct(const Vector&) const;
		double getAngle(const Vector&) const;
		Vector getUnit() const;

		double x, y;

	protected:
		double m_standard;

	};
}
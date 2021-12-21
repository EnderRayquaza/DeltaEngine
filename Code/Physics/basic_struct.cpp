#include "basic_struct.hpp"

namespace DeltaEngine
{
	//AABB
	AABB::AABB(int x, int y, int w, int h):x(x), y(y), w(w), h(h)
	{

	}

	AABB::AABB(sf::Vector2i pos, sf::Vector2i size) : x(pos.x), y(pos.y), w(size.x), h(size.y)
	{

	}

	Vertex AABB::get_vertex(int index)
	{
		switch (index)
		{
		case 0:
			return Vertex(x, y);
			break;
		case 1:
			return Vertex(x+w, y);
			break;
		case 2:
			return Vertex(x, y+h);
			break;
		case 3:
			return Vertex(x+w, y+h);
			break;
		default:
			return Vertex(0, 0);
			break;
		}
	}

	//Vertex
	Vertex::Vertex(int x, int y) :x(x), y(y)
	{

	}

	Vertex::Vertex(sf::Vector2i pos) : x(pos.x), y(pos.y)
	{

	}

	Vertex::Vertex(sf::Vertex vtx) : x(vtx.position.x), y(vtx.position.y)
	{

	}

	//Shape
	Shape::Shape(std::vector<Vertex> vVtx) :vertices(vVtx)
	{

	}

	Shape::Shape(sf::VertexArray vtxArr)
	{
		for (size_t i{ 0 }; i < vtxArr.getVertexCount(); i++)
		{
			vertices.push_back(Vertex(vtxArr[i]));
		}
	}

	//Vector
	Vector::Vector(double x, double y) :x(x), y(y)
	{
		calculStandard();
	}

	Vector::Vector(sf::Vector2f v2f) : Vector(v2f.x, v2f.y)
	{

	}

	Vector& Vector::operator+=(const Vector& vec)
	{
		x + vec.x; y + vec.y;
		return *this;
	}

	Vector& Vector::operator-=(const Vector& vec)
	{
		x - vec.x; y - vec.y;
		return *this;
	}

	Vector& Vector::operator*=(const double k)
	{
		x *= k; y *= k;
		return *this;
	}

	Vector& Vector::operator/=(const double k)
	{
		x /= k; y /= k;
		return *this;
	}

	double Vector::get_standard() const
	{
		return m_standard;
	}

	double Vector::calculStandard()
	{
		m_standard = sqrt(x * x + y * y);
		return m_standard;
	}

	double Vector::scalarProduct(const Vector& vec) const
	{
		return x * vec.x + y * vec.y;
	}

	//v.u = ||v||*||u||*cos angle <=> angle = cos-1(v.u/||v||*||u||)
	double Vector::getAngle(const Vector& vec) const
	{
		return acos(scalarProduct(vec) / (m_standard * vec.m_standard));
	}

	Vector Vector::getUnit() const
	{
		Vector vec{ *this };
		return vec / m_standard;
	}

	//Operator
	Vector operator+(const Vector& vec, const Vector& vec_)
	{
		Vector v{ vec };
		v += vec_;
		return v;
	}

	Vector operator-(const Vector& vec, const Vector& vec_)
	{
		Vector v{ vec };
		v -= vec_;
		return v;
	}

	Vector operator*(const Vector& vec, const double k)
	{
		Vector v{ vec };
		v *= k;
		return v;
	}

	Vector operator/(const Vector& vec, const double k)
	{
		Vector v{ vec };
		v /= k;
		return v;
	}

	double operator*(const Vector& vec, const Vector& vec_)
	{
		return vec.scalarProduct(vec_);
	}

	std::ostream& operator<<(std::ostream& flux, const Vector& vec)
	{
		flux << "v(" << vec.x << ", " << vec.y << ") ||v|| = " << vec.get_standard() << " ";
		return flux;
	}
}
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

	Vertex AABB::get_vertex(int index) const
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

	void Shape::move(const Vector& vec)
	{
		for (auto& vtx : vertices)
		{
			vtx.x += vec.x; vtx.y += vec.y;
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

	//Other functions
	AABB findAABBfromShape(const Shape& shape)
	{
		int xmin{INFINITY}, xmax{0}, ymin{INFINITY}, ymax{0};
		for (auto& vtx : shape.vertices)
		{
			if (vtx.x < xmin) xmin = vtx.x;
			if (vtx.x > xmax) xmax = vtx.x;
			if (vtx.y < ymin) ymin = vtx.y;
			if (vtx.y > ymax) ymax = vtx.y;
		}
		return AABB(xmin, ymin, xmax, ymax);
	}

	float aera(const Shape& shape)
	{
		const size_t n{ shape.vertices.size() };
		std::vector<float> DX{}, DY{};
		float A{ 0 };
		for (size_t i{ 0 }; i < n; i++)
		{
			DX.push_back((shape.vertices[(i + 1) % n].x - shape.vertices[(i + n - 1) % n].x) / 2);
			DY.push_back((shape.vertices[(i + 1) % n].y - shape.vertices[(i + n - 1) % n].y) / 2);
		}
		for (size_t i{ 0 }; i < n; i++)
		{
			A += shape.vertices[i].x * DY[i] - shape.vertices[i].y * DX[i];
		}
		return fabs(A / 2.f);
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

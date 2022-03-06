#include "Shape.hpp"

namespace DeltaEngine
{
	void moveAABB(AABB& aabb, Vec2i& vec)
	{
		aabb.left += vec.x;
		aabb.top  += vec.y;
	}
	
	void moveToAABB(AABB& aabb, Vec2i& vec)
	{
		aabb.left += vec.x;
		aabb.top  += vec.y;
	}

	AABB findAABBfromShape(std::vector<Vertex>& const vertices)
	{
		int xmin{ (int)INFINITY }, xmax{ 0 }, ymin{ (int)INFINITY }, ymax{ 0 };
		for (auto& vtx : vertices)
		{
			if (vtx.x < xmin) xmin = vtx.x;
			if (vtx.x > xmax) xmax = vtx.x;
			if (vtx.y < ymin) ymin = vtx.y;
			if (vtx.y > ymax) ymax = vtx.y;
		}
		return { xmin, ymin, xmax, ymax };
	}

	ulong findSurface(Shape& const shape)
	{
		size_t const n{ shape.m_vertices.size() };
		std::vector<long> DX{}, DY{};
		ulong S{ 0 };

		for (size_t i{ 0 }; i < n; i++)
		{
			DX.push_back((shape.m_vertices[(i + 1) % n].x - shape.m_vertices[(i + n - 1) % n].x) / 2);
			DY.push_back((shape.m_vertices[(i + 1) % n].y - shape.m_vertices[(i + n - 1) % n].y) / 2);
		}
		for (size_t i{ 0 }; i < n; i++)
		{
			S += shape.m_vertices[i].x * DY[i] - shape.m_vertices[i].y * DX[i];
		}
		return labs(S / 2.f);
	}

	Shape::Shape(std::vector<Vertex> vertices) :m_vertices{ vertices },
		m_aabb{ findAABBfromShape(vertices) }
	{}

	void Shape::setPosition(Vec2i pos) noexcept
	{
		Shape shape{ m_vertices };
		for (auto& vtx : shape.m_vertices)
		{
			vtx += pos;
		}
	}

	void Shape::setAngle(double angle) noexcept
	{
		Shape shape{ m_vertices };
		for (auto& vtx : shape.m_vertices)
		{
			vtx = { (int)(vtx.x * cos(angle) - vtx.y * sin(angle)),
					(int)(vtx.y * cos(angle) - vtx.x * sin(angle)) };
		}
	}
}
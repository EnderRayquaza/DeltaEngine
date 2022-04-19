#include "../Class_headers/Shape.hpp"

namespace DeltaEngine
{
	AABB findAABBfromVertices(const std::vector<Vertex>& vVtx, uint margin)
	{
		int xmin{ (int)INFINITY }, xmax{ 0 }, ymin{ (int)INFINITY }, ymax{ 0 };
		for (auto& vtx : vVtx)
		{
			if (vtx.x < xmin) xmin = vtx.x;
			if (vtx.x > xmax) xmax = vtx.x;
			if (vtx.y < ymin) ymin = vtx.y;
			if (vtx.y > ymax) ymax = vtx.y;
		}
		return AABB{ xmin - (int)margin, ymin - (int)margin, xmax + (int)margin, ymax + (int)margin };
	}

	Shape::Shape(jsonStr path):Loadable(path)
	{}

	Shape::Shape(std::vector<Vertex> vVtx, uint margin) :m_vVertex{ vVtx }, 
		m_aabb{ findAABBfromVertices(vVtx, margin) }
	{}

	bool Shape::load()
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TODO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		return false;
	}

	size_t Shape::nbVtx()
	{
		return m_vVertex.size();
	}

	std::vector<Vertex> Shape::getVertices(Vertex pos, double angle) const
	{
		std::vector<Vertex> vertices{ m_vVertex };
		//Rotation
		for (auto& vtx : vertices)
		{
			vtx = { (int)(vtx.x * cos(angle) - vtx.y * sin(angle)),
					(int)(vtx.y * cos(angle) - vtx.x * sin(angle)) };
		}
		//Moving
		for (auto& vtx : vertices)
		{
			vtx += pos;
		}
		return vertices;
	}

	bool Shape::pointIn(Vertex pt) const
	{
		for (size_t i{ 0 }; i < m_vVertex.size(); i++)
		{ //For all points of the shapeA
			Vertex vtx, vtx1;
			if (i + 1 < m_vVertex.size())//After looking over all points, it goes to the first one.
			{
				vtx = m_vVertex[i], vtx1 = m_vVertex[i + 1]; //The current vertex and the next one. 
			}
			else
			{
				vtx = m_vVertex[i], vtx1 = m_vVertex[0]; //The current vertex (the last) and the first one. 
			}
			Vec2f aa{ float(vtx1.x - vtx.x), float(vtx1.y - vtx.y) },
				ab{ float(pt.x - vtx.x), float(pt.y - vtx.y) }; //Calculs the vector vtx;vtx+1 and vtx;pt.
			float det{ (aa.x - ab.y) * (aa.y - ab.x) }; //Calculs their determinant.
			if (det >= 0) //Verifies the sign of the determinant
			{
				return true;
			}
		}
		return false;
	}

	ulong Shape::getSurface() const
	{
		size_t const n{ m_vVertex.size() };
		std::vector<long> DX{}, DY{};
		ulong S{ 0 };

		for (size_t i{ 0 }; i < n; i++)
		{
			DX.push_back((m_vVertex[(i + 1) % n].x - m_vVertex[(i + n - 1) % n].x) / 2);
			DY.push_back((m_vVertex[(i + 1) % n].y - m_vVertex[(i + n - 1) % n].y) / 2);
		}
		for (size_t i{ 0 }; i < n; i++)
		{
			S += m_vVertex[i].x * DY[i] - m_vVertex[i].y * DX[i];
		}
		return (ulong)labs(S / 2.f);
	}
}
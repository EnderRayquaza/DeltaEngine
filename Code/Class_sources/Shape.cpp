#include "../Class_headers/Shape.hpp"

namespace DeltaEngine
{
	AABB findAABBfromVertices(const std::vector<Vertex>& vVtx, uint margin)
	{
		int xmin{ (int)vVtx[0].x }, xmax{ 0 }, ymin{ (int)vVtx[0].y }, ymax{ 0 };
		for (auto& vtx : vVtx)
		{
			//std::cout << "\"vtx\" : " << vtx.x << "/" << vtx.y << std::endl;
			if (vtx.x < xmin) xmin = vtx.x;
			if (vtx.x > xmax) xmax = vtx.x;
			if (vtx.y < ymin) ymin = vtx.y;
			if (vtx.y > ymax) ymax = vtx.y;
		}
		//std::cout << std::endl;
		return AABB{ xmin - (int)margin, ymin - (int)margin,
			(xmax - xmin) + (int)margin, (ymax - ymin) + (int)margin };
	}

	Vec2f whichSideCutted(const Shape shape, Vertex pos, double angle, Vertex centerA, Vertex centerB)
	{
		std::vector<Vertex> vVertex{ shape.getVertices(pos, centerA-pos, angle) };
		for (size_t i{ 0 }; i < vVertex.size(); i++)
		{
			Vertex vtx, vtx1;
			if (i + 1 < vVertex.size())
				vtx = vVertex[i], vtx1 = vVertex[i + 1];
			else
				vtx = vVertex[i], vtx1 = vVertex[0];

			if (segmentCut(vtx, vtx1, centerA, centerB)) //Verifies the sign of the determinant
			{
				return { vtx1 - vtx };
			}
		}
		std::cout << "no segment was cutted..." << std::endl;
		return { 0, 0 };
	}

	Shape::Shape(jsonStr path) :Loadable(path)
	{}

	Shape::Shape(std::vector<Vertex> vVtx, uint margin): m_vVertex{ vVtx }, m_aabbMargin{ margin }
	{}

	bool Shape::load()
	{
		json j{ returnJson(_path) };
		for (auto& vtx : j["vertex"])
		{
			//std::cout << "vtx : " << vtx[0] << "/" << vtx[1] << std::endl;
			m_vVertex.push_back(Vertex{ vtx[0], vtx[1] });
		}
		m_aabbMargin = j["margin"];
		std::cout << std::endl;
		return true;
	}

	size_t Shape::nbVtx() const
	{
		return m_vVertex.size();
	}

	std::vector<Vertex> Shape::getVertices(Vertex pos, Vertex center, double angle) const
	{
		std::vector<Vertex> vertices{ m_vVertex };
		//Rotation
		for (auto& vtx : vertices)
		{
			vtx = { (float)((vtx.x - center.x) * cos(angle) - (vtx.y - center.y) * sin(angle) + center.x),
					(float)((vtx.y - center.y) * cos(angle) + (vtx.x - center.x) * sin(angle) + center.y) };
		}
		//Moving
		for (auto& vtx : vertices)
		{
			vtx += pos;
		}
		return vertices;
	}

	AABB Shape::getAABB(Vertex pos, Vertex center, double angle) const
	{
		return findAABBfromVertices(getVertices(pos, center, angle), m_aabbMargin);
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


	bool pointInShape(Vertex const pt, std::vector<Vertex> const vVtx)
	{
		for (size_t i{ 0 }; i < vVtx.size(); i++)
		{ //For all points of the shapeA
			Vertex vtx, vtx1;
			if (i + 1 < vVtx.size())
				vtx = vVtx[i], vtx1 = vVtx[i + 1];
			else
				vtx = vVtx[i], vtx1 = vVtx[0];
			/*if (500 < pt.x and pt.x < 550 and 50 < pt.y and pt.y < 250)
			{
			std::cout << "point pt : " << pt.x << "/" << pt.y << std::endl;
			std::cout << "point vtx : " << vtx.x << "/" << vtx.y << std::endl;
			std::cout << "point vtx1 : " << vtx1.x << "/" << vtx1.y << std::endl;
			}*/

			Vec2f side{ vtx1 - vtx }, vPt{ pt - vtx }; //Calculs the vector vtx;vtx+1 and vtx;pt.
			double det{ (side.x * -vPt.y) - (-side.y * vPt.x) }; //Calculs their determinant.
			if (det > 0) //Verifies the sign of the determinant
			{
				//std::cout << "det > 0" << std::endl;
				return false;
			}
			//std::cout << "next point " << std::endl << std::endl;
		}
		return true;
	}
}
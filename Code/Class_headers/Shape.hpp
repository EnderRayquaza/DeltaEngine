#pragma once

#include "../config.hpp"

namespace DeltaEngine
{
	AABB findAABBfromVertices(const std::vector<Vertex>&, uint margin=0);

	class Shape
	{
	public:
		Shape() = delete;
		Shape(std::vector<Vertex>, uint margin = 0);
		~Shape() = default;

		std::vector<Vertex> getVertices(Vertex pos = { 0,0 }, double angle = 0) const; //Return the Shape modified by a position and a rotation.
		bool pointIn(Vertex) const;
		ulong getSurface() const;

	protected:
		std::vector<Vertex> const m_vVertex;
		AABB const m_aabb;
	};
}
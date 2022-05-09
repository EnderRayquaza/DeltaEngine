#pragma once

#include "../config.hpp"
#include "Loadable.hpp"

namespace DeltaEngine
{
	AABB findAABBfromVertices(const std::vector<Vertex>&, uint margin=0);

	class Shape : public Loadable
	{
	public:
		Shape() = delete;
		Shape(jsonStr);
		Shape(std::vector<Vertex>, uint margin = 0);
		~Shape() = default;

		bool load();

		size_t nbVtx();
		std::vector<Vertex> getVertices(Vertex pos = { 0,0 }, double angle = 0) const; //Return the Shape modified by a position and a rotation.
		AABB getAABB(Vertex pos = { 0,0 }, double angle = 0) const; //Return the AABB of the Shape modified by a position and a rotation.
		bool pointIn(Vertex) const; //Verifies if the point is in the Shape.
		ulong getSurface() const; //Returns the surface of the shape.

	protected:
		std::vector<Vertex> const m_vVertex;
		AABB const m_aabb;
	};

	bool pointInShape(Vertex const point, std::vector<Vertex> const);
}
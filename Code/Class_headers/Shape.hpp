#pragma once

#include "../config.hpp"
#include "func.hpp"
#include "Loadable.hpp"

namespace DeltaEngine
{
	class Shape;

	AABB findAABBfromVertices(const std::vector<Vertex>&, uint margin=0);

	Vec2f whichSideCutted(const Shape shape, Vertex position, double angle, Vertex centerA, Vertex centerB);

	class Shape : public Loadable
	{
	public:
		Shape() = delete;
		Shape(jsonStr);
		Shape(std::vector<Vertex>, uint margin = 0);
		~Shape() = default;

		bool load();

		size_t nbVtx() const;
		std::vector<Vertex> getVertices(Vertex pos = { 0,0 }, Vertex center = { 0, 0 }, double angle = 0) const; //Return the Shape modified by a position and a rotation.
		AABB getAABB(Vertex pos = { 0,0 }, Vertex center = { 0, 0 }, double angle = 0) const; //Return the AABB of the Shape modified by a position and a rotation.
		bool pointIn(Vertex) const; //Verifies if the point is in the Shape.
		ulong getSurface() const; //Returns the surface of the shape.

	protected:
		std::vector<Vertex> m_vVertex{};
		uint m_aabbMargin{0};
	};

	bool pointInShape(Vertex const point, std::vector<Vertex> const);
}
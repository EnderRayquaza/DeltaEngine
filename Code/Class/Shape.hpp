#pragma once

#include "../config.hpp"

namespace DeltaEngine
{
	class Shape;
	void moveAABB(AABB&, Vec2i&);
	void moveToAABB(AABB&, Vec2i&);
	AABB findAABBfromShape(std::vector<Vertex>& const);
	ulong findSurface(Shape& const);

	class Shape
	{
	public:
		Shape() = delete;
		Shape(std::vector<Vertex>);
		~Shape() = default;

		Shape moveTo(Vec2i) const noexcept;

		friend class Contact;
		friend class Impact;
		friend bool pointInShape(Vertex point, Shape);
		friend AABB findAABBfromShape(std::vector<Vertex>& const);
		friend ulong findSurface(Shape& const);

	protected:
		std::vector<Vertex> m_vertices;
		AABB m_aabb;
	};
}
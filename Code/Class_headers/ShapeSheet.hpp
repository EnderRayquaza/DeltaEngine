#pragma once

#include "../config.hpp"
#include "Loadable.hpp"
#include "Manager.hpp"
#include "Shape.hpp"

namespace DeltaEngine
{
	class ShapeSheet : public Identifiable, public Loadable
	{
	public:
		ShapeSheet() = delete;
		ShapeSheet(jsonStr);
		ShapeSheet(Manager<Shape>, Vec2i size);
		~ShapeSheet() = default;

		Shape& operator[](Vec2i index);

		bool load();

	protected:
		Manager<Shape> m_mngShape;
		Vec2i m_size;
	};
}
#include "../Class_headers/ShapeSheet.hpp"

namespace DeltaEngine
{
	ShapeSheet::ShapeSheet(jsonStr path) :Identifiable(), Loadable(path)
	{}

	ShapeSheet::ShapeSheet(Manager<Shape> mng, Vec2i size) : Identifiable(), Loadable(),
		m_mngShape{ std::move(mng) }, m_size{ size }
	{}

	Shape& ShapeSheet::operator[](Vec2i index)
	{
		if (index.x < m_size.x || index.y < m_size.y)
		{
			return m_mngShape[(uint)index.x + (uint)m_size.y * index.y];
		}
	}

	bool ShapeSheet::load()
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TODO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		for (size_t i{0}; i < m_mngShape.size(); i++)
		{
			m_mngShape[i].load();
		}
	}
}
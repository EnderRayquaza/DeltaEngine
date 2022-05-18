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
		else
		{
			return m_mngShape[-1];
		}
	}

	bool ShapeSheet::load()
	{
		json j{ returnJson(_path) };
		for (size_t i{0}; i < (size_t)j["size"]; i++)
		{
			m_mngShape.addItem(Shape{ (jsonStr)j["shapes"][i] });
		}
		m_mngShape.loadItem();
		return true;
	}
}
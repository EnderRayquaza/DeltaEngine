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
			std::cerr << "Error no shape found" << std::endl;
			return m_mngShape[-1];
		}
	}

	bool ShapeSheet::load()
	{
		json j{ returnJson(_path) };
		m_size = Vec2i{ j["size"][0], j["size"][1] };
		for (auto& shape : j["shapes"])
		{
			Shape s{ (jsonStr)shape };
			m_mngShape.addItem(s);
		}
		m_mngShape.loadItem();
		return true;
	}
}
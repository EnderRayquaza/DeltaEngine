#include "Animation.hpp"

namespace DeltaEngine
{
	ShapeSheet::ShapeSheet(jsonStr jsonPath, uint sizeX, uint sizeY) :m_jsonPath{ jsonPath }, m_size{ sizeX, sizeY }
	{}

	Shape& ShapeSheet::operator()(uint const indexX, uint const indexY) noexcept
	{
		if (indexX >= m_size.x || indexY >= m_size.y)
		{
			error("Index out of range", "Animation.cpp", 12, ErrorType::INDEX_OUT_OF_RANGE);
			return;
		}
		return m_items[indexX + m_size.y * indexY];
	}

	Shape& ShapeSheet::operator[](Vec2i const index) noexcept
	{
		if (index.x >= m_size.x || index.y >= m_size.y)
		{
			error("Index out of range", "Animation.cpp", 12, ErrorType::INDEX_OUT_OF_RANGE);
			return;
		}
		return m_items[index.x + m_size.y * index.y];
	}

	void ShapeSheet::load()
	{
		json j{ returnJson(m_jsonPath) };
		for (auto& shape : j["shape"])
		{
			std::vector<Vertex> vertices{};
			for (auto& vtx : shape)
			{
				vertices.push_back(Vertex(vtx[0], vtx[1]));
			}
			m_items.push_back((Shape)vertices);
		}
	}
}
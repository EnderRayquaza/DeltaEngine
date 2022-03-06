#include "Animation.hpp"

namespace DeltaEngine
{
	ShapeSheet::ShapeSheet(jsonStr jsonPath, uint sizeX, uint sizeY) :m_jsonPath{ jsonPath }, m_size{ sizeX, sizeY }
	{}

	Shape& ShapeSheet::operator()(uint const indexX, uint const indexY)
	{
		if (indexX >= m_size.x || indexY >= m_size.y)
		{
			error("Index(arg) out of range(m_size)", "Animation.cpp", 12,
				ErrorType::INDEX_OUT_OF_RANGE, true);
		}
		return m_items[indexX + (uint)m_size.y * indexY];
	}

	Shape& ShapeSheet::operator[](Vec2i const index)
	{
		if (index.x >= m_size.x || index.y >= m_size.y)
		{
			error("Index out of range", "Animation.cpp", 12, ErrorType::INDEX_OUT_OF_RANGE, true);
		}
		return m_items[index.x + (uint)m_size.y * index.y];
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

	Animation::Animation(jsonStr jsonPath)
	{
		json j{ returnJson(jsonPath) };
		time = (ulong)j["time"];
		for (auto& pos : j["vPos"])
		{
			vPos.push_back(Vec2i(pos[0], pos[1]));
		}
	}
}
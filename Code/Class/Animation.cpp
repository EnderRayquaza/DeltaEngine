#include "Animation.hpp"

namespace DeltaEngine
{
	ShapeSheet::ShapeSheet(std::string jsonPath, uint sizeX, uint sizeY) :m_jsonPath{ jsonPath }, m_size{ sizeX, sizeY }
	{}

	Shape& ShapeSheet::operator()(uint const indexX, uint const indexY) noexcept
	{
		if (indexX >= m_size.x || indexY >= m_size.y)
		{
			return;
		}
		return m_items[indexX];
	}

	void ShapeSheet::load()
	{
		json j{ returnJson(m_jsonPath) };
		for (auto& shape : j["shape"])
		{
			std::vector<Vertex> vVtx{};
			for (auto& vtx : shape)
			{
				vVtx.push_back(Vertex(vtx[0], vtx[1]));
			}
			m_items.push_back((Shape)vVtx);
		}
	}
}
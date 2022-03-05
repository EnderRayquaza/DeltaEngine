#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Shape.hpp"

namespace DeltaEngine
{
	class ShapeSheet
	{
	public:
		ShapeSheet() = delete;
		ShapeSheet(jsonStr jsonPath, uint sizeX, uint sizeY);
		~ShapeSheet() = default;

		Shape& operator()(uint const indexX, uint const indexY);

		Shape& operator[](Vec2i const index);

		void load();

	protected:
		jsonStr m_jsonPath;
		Vec2i m_size;
		std::vector<Shape> m_items{};
	};

	struct Animation
	{
		Animation(jsonStr jsonPath);
		std::vector<Vec2i> vPos;
		ulong time, currTime{0};
	};
}

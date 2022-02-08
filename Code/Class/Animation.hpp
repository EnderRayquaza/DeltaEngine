#pragma once

#include "../config.hpp"
#include "../basic.hpp"

namespace DeltaEngine
{
	class ShapeSheet
	{
	public:
		ShapeSheet() = delete;
		ShapeSheet(std::string jsonPath, uint sizeX, uint sizeY);
		~ShapeSheet() = default;

		Shape& operator()(uint const indexX, uint const indexY);

		void load();

	protected:
		std::string m_jsonPath;
		Vec2i m_size;
		std::vector<Shape> m_items;
	};

	struct Animation
	{
		std::vector<Vec2i> var2findAName;
		ulong time, timeStamp;
	};
}
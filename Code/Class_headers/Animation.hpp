#pragma once
#include "../config.hpp"
#include "func.hpp"
#include "Loadable.hpp"

namespace DeltaEngine
{
	struct Animation : public Loadable
	{
		Animation() = default;
		Animation(jsonStr);

		bool load();
		size_t size();

		std::vector<Vec2i> _vCoord{};
	};
}
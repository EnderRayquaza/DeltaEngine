#pragma once
#include "../config.hpp"
#include "Loadable.hpp"

namespace DeltaEngine
{
	class Animation : public Loadable
	{
	public:
		Animation() = default;
		Animation(jsonStr);

		bool load();
		size_t size();

		std::vector<Vec2i> _vCoord{};
	protected:
	};
}
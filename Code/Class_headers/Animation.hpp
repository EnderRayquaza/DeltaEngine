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
		Animation(json);

		bool load();
		bool loadByJson();
		size_t size();

		json _j{};
		sf::Time _time{};
		std::vector<Vec2i> _vCoord{};
	};
}
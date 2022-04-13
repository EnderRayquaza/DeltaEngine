#pragma once

#include "../config.hpp"

namespace DeltaEngine
{
	class Loadable
	{
	public:
		Loadable() = default;
		Loadable(jsonStr path) :_path{ path }
		{}
		~Loadable() = default;

		virtual bool load() = 0;

		jsonStr _path{};
	};
}
#pragma once
#include "../config.hpp"

namespace DeltaEngine
{
	enum class moveType
	{
		Static,
		Kinematic,
		Dynamic
	};

	enum class collisionType
	{
		Nothing,
		Decor,
		Ground,
		ObjectA,
		ObjectB
	};

	typedef std::vector<collisionType> collisionTargets;
}

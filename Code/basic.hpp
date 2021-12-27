#pragma once

#include "DeltaEngine.hpp"

using json = nlohmann::json;

namespace DeltaEngine
{
	/*enum class moveType
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
	};*/

	json returnJson(std::string jsonPath); // Returns a json array from a .json file.

	struct Id
	{
		int intKey;
		std::string strKey;
	};

	bool operator==(Id& lhs, Id& rhs); //Compares 2 ID.
}

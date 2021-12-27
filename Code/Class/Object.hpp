#pragma once

#include "../DeltaEngine.hpp"
#include "../basic.hpp"

namespace DeltaEngine
{
	class Object;

	class Object
	{
	public:
		Object();
		//Object(std::string jsonPath);
		//~Object() = default;

	protected:
		//static std::vector<Id> listId;
		Id m_id; //Don't work!!!
	};
}

#pragma once

#include "../config.hpp"
#include "../basic.hpp"

namespace DeltaEngine
{
	class Object
	{
	public:
		Object();
		Object(std::string jsonPath);
		~Object() = default;

	protected:
		static std::vector<Id> listId;
		Id m_id;
	};
}

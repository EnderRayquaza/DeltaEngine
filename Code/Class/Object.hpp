#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Body.hpp"

namespace DeltaEngine
{
	class Object
	{
	public:
		Object();
		Object(std::string jsonPath);
		~Object() = default;

		bool load(std::string jsonPath);
	protected:
		static std::vector<Id> listId;
		Id const m_id;



	};
}

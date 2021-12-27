#pragma once

#include "../DeltaEngine.hpp"

namespace DeltaEngine
{
	class Object
	{
	public:
		Object();
		Object(std::string jsonPath);
		~Object();

	protected:
		static std::vector<ID> listId;
		const ID m_id;
	};
}

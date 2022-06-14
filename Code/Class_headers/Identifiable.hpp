#pragma once

#include "../config.hpp"
#include "func.hpp"

namespace DeltaEngine
{
	class Identifiable;

	struct Id
	{
		int intKey1{ 0 };
		int intKey2{ 0 };
	};

	Id createId(std::vector<Id>& staticList);

	bool operator==(Id const lhs, Id const rhs);

	bool operator!=(Id const lhs, Id const rhs);

	bool operator==(Identifiable& lhs, Identifiable& rhs);

	bool operator!=(Identifiable& lhs, Identifiable& rhs);

	class Identifiable
	{
	public:
		Identifiable();
		~Identifiable() = default;

		Id const _id;
	protected:
		inline static std::vector<Id> s_idList{};
	};
}
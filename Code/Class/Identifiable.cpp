#include "Identifiable.hpp"

namespace DeltaEngine
{
	//Identifiable
	Identifiable::Identifiable() :m_id(createId(listId))
	{}

	Id Identifiable::get_id() const noexcept
	{
		return m_id;
	}

	//Funcs
	Id createId(std::vector<Id> list)
	{
		Id id{};
		do
		{
			id = Id{ rand(), std::to_string(rand()) };
		} while (inVector(list, id));
		return id;
	}

	bool operator==(Id const lhs, Id const rhs)
	{
		return lhs.intKey == rhs.intKey && lhs.strKey == rhs.strKey;
	}

	bool operator!=(Id const lhs, Id const rhs)
	{
		return !(lhs == rhs);
	}

	bool operator==(Identifiable& const lhs, Identifiable& const rhs)
	{
		return lhs.m_id == rhs.m_id;
	}

	bool operator!=(Identifiable& const lhs, Identifiable& const rhs)
	{
		return !(lhs == rhs);
	}

}
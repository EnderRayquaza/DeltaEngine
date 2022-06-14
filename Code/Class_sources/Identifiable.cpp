#include "../Class_headers/Identifiable.hpp"

namespace DeltaEngine
{
	Id createId(std::vector<Id>& list)
	{
		Id id{};
		do
		{
			id = Id{ rand(), rand() };
		} while (inVector<Id>(list, id));
		return id;
	}

	bool operator==(Id const lhs, Id const rhs)
	{
		return lhs.intKey1 == rhs.intKey1 && lhs.intKey2 == rhs.intKey2;
	}

	bool operator!=(Id const lhs, Id const rhs)
	{
		return !(lhs == rhs);
	}

	bool operator==(Identifiable& lhs, Identifiable& rhs)
	{
		return lhs._id == rhs._id;
	}

	bool operator!=(Identifiable& lhs, Identifiable& rhs)
	{
		return !(lhs == rhs);
	}

	Identifiable::Identifiable() : _id{ createId(s_idList) }
	{}
}
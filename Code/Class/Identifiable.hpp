#pragma once

#include "../config.hpp"
#include "../basic.hpp"

namespace DeltaEngine
{
	struct Id;
	class Identifiable;
	Id createId(std::vector<Id> staticList);
	bool operator==(Id const lhs, Id const rhs);
	bool operator!=(Id const lhs, Id const rhs);
	bool operator==(Identifiable& const lhs, Identifiable& const rhs);
	bool operator!=(Identifiable& const lhs, Identifiable& const rhs);

	struct Id
	{
		int intKey{ 0 };
		std::string strKey{ "" };
	};

	class Identifiable : public sf::NonCopyable
	{
	public:
		Identifiable();
		~Identifiable() = default;

		Id get_id() const noexcept;

		friend bool operator==(Identifiable& const, Identifiable& const);
		friend bool operator!=(Identifiable& const, Identifiable& const);

	protected:
		static std::vector<Id> listId;
		Id const m_id;
	};
}
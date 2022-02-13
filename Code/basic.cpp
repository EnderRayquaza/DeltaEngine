#include "basic.hpp"

namespace DeltaEngine
{
	bool Id::isEgal(Id const rhs) const noexcept
	{
		return intKey == rhs.intKey && strKey == rhs.strKey;
	}

	bool operator==(Id const lhs, Id const rhs)
	{
		return lhs.isEgal(rhs);
	}

	bool operator!=(Id const lhs, Id const rhs)
	{
		return !(lhs == rhs);
	}



	json returnJson(std::string const jsonPath)
	{
		std::ifstream file(jsonPath); //Opens the file.
		if (!file) //Returns an error if it can't.
			std::cout << "Erreur : File not open (" << jsonPath << ")" << std::endl;
		json j{}; //Creates a json variable.
		file >> j; //Puts the data from the file in the json var.
		return j; //Returns it.
	}



	Id createId(std::vector<Id> list)
	{
		Id id{};
		do
		{
			id = Id{ rand(), std::to_string(rand()) };
		} while (inVector(list, id));
		return id;
	}

	template <typename T>
	bool inVector(std::vector<T> vec, T& item)
	{
		return std::find(vec.begin(), vec.end(), item) != std::end;
	}

	template <typename T>
	sf::Vector2<T> operator*(sf::Vector2<T>& lhs, int rhs)
	{
		sf::Vector2<T> vec{};
		vec.x = lhs.x * rhs;
		vec.y = lhs.y * rhs;
		return vec;
	}
	template <typename T>
	sf::Vector2<T> operator*(int lhs, sf::Vector2<T>& rhs)
	{
		return rhs * lhs;
	}

	Identifiable::Identifiable():m_id(createId(listId))
	{}

	Id Identifiable::get_id() const noexcept
	{
		return m_id;
	}
}
#include "basic.hpp"

namespace DeltaEngine
{




	json returnJson(std::string const jsonPath)
	{
		std::ifstream file(jsonPath); //Opens the file.
		if (!file) //Returns an error if it can't.
			std::cout << "Erreur : File not open (" << jsonPath << ")" << std::endl;
		json j{}; //Creates a json variable.
		file >> j; //Puts the data from the file in the json var.
		return j; //Returns it.
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


}
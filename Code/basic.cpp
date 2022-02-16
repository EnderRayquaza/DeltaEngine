#include "basic.hpp"

namespace DeltaEngine
{
	void error(std::string errText, std::string fileName, uint line, ErrorType type, bool stop)
	{
		std::string err{ "Error (" + std::to_string(type) + ") : " + errText + " at " + fileName +
			" (" + std::to_string(line) + ") !"};
		std::cerr << std::endl << err << std::endl;
		if (stop)
		{
			assert(false && err.c_str());
		}
	}

	json returnJson(jsonStr const jsonPath)
	{
		std::ifstream file{ jsonPath }; //Opens the file.
		if (!file) //Returns an error if it can't.
			std::cout << "Error : File not open (" << jsonPath << ")" << std::endl;
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
	template <typename T>
	sf::Vector2<T> operator/(sf::Vector2<T>& lhs, int rhs)
	{
		sf::Vector2<T> vec{};
		vec.x = lhs.x / rhs;
		vec.y = lhs.y / rhs;
		return vec;
	}
	template <typename T>
	sf::Vector2<T> operator/(int lhs, sf::Vector2<T>& rhs)
	{
		return rhs / lhs;
	}

}
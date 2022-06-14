#include "../Class_headers/func.hpp"

namespace DeltaEngine
{
	json returnJson(jsonStr const jsonPath)
	{
		std::ifstream file{ jsonPath }; //Opens the file.
		if (!file) //Returns an error if it can't.
			std::cout << "Error : File not open (" << jsonPath << ")" << std::endl;
		json j{}; //Creates a json variable.
		file >> j; //Puts the data from the file in the json var.
		return j; //Returns it.
	}

	/*template <typename T>
	bool inVector(std::vector<T>& vec, T& item)
	{
		return std::find(vec.begin(), vec.end(), item) != vec.end();
	}*/

	template <typename T>
	void eraseElem(std::vector<T>& vec, T& item)
	{
		if (inVector(vec, item))
		{
			const auto& it{ std::find(vec.begin(), vec.end(), item) };
			vec.erase(it, it);
			
		}
	}

	template <typename T, typename U>
	sf::Vector2<T> operator*(const sf::Vector2<T>& lhs, const U rhs)
	{
		sf::Vector2<T> vec{};
		vec.x = lhs.x * rhs;
		vec.y = lhs.y * rhs;
		return vec;
	}

	template <typename T, typename U>
	sf::Vector2<T> operator*(const U lhs, const sf::Vector2<T>& rhs)
	{
		return rhs * lhs;
	}

	template <typename T, typename U>
	sf::Vector2<T> operator/(const sf::Vector2<T>& lhs, const U rhs)
	{
		return lhs * (double)(1 / rhs);
	}

	template <typename T, typename U>
	sf::Vector2<T> operator/(const U lhs, const sf::Vector2<T>& rhs)
	{
		return rhs / lhs;
	}
}
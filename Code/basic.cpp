#include "basic.hpp"

namespace DeltaEngine
{
	json returnJson(std::string jsonPath)
	{
		std::ifstream file(jsonPath); //Opens the file.
		if (!file) //Returns an error if it can't.
			std::cout << "Erreur : File not open (" << jsonPath << ")" << std::endl;
		json j{}; //Creates a json variable.
		file >> j; //Puts the data from the file in the json var.
		return j; //Returns it.
	}

	bool operator==(Id& lhs, Id& rhs)
	{
		return lhs.intKey == rhs.intKey && lhs.strKey == rhs.strKey;
	}
}
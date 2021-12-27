#include "DeltaEngine.hpp"

namespace DeltaEngine
{
	enum class moveType
	{
		Static,
		Kinematic,
		Dynamic
	};

	enum class collisionType
	{
		Nothing,
		Decor,
		Ground,
		ObjectA,
		ObjectB
	};

	json returnJson(std::string jsonPath)
	{
		std::ifstream file(jsonPath); //Opens the file.
		if (!file) //Returns an error if it can't.
			std::cout << "Erreur : File not open (" << jsonPath << ")" << std::endl;
		json j{}; //Creates a json variable.
		file >> j; //Puts the data from the file in the json var.
		return j; //Returns it.
	}

	bool operator==(ID& lhs, ID& rhs)
	{
		return lhs.intKey == rhs.intKey && lhs.strKey == rhs.strKey;
	}

	struct ID
	{
		int intKey;
		std::string strKey;
	};
}
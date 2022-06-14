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
}
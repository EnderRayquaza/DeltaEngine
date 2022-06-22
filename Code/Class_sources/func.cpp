#include "../Class_headers/func.hpp"

namespace DeltaEngine
{
	json returnJson(jsonStr const jsonPath)
	{
		std::ifstream file((std::string)jsonPath); //Opens the file.
		if (!file) //Returns an error if it can't.
			std::cout << "DE - Error : File not open (path:" << jsonPath << ")" << std::endl;
		json j{}; //Creates a json variable.
		file >> j; //Puts the data from the file in the json var.
		file.close();
		return j; //Returns it.
	}
}
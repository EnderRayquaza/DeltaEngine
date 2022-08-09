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

	double det(Vec2f const v, Vec2f const u)
	{
		return (v.x * (-u.y)) - ((-v.y) * u.x);
	}

	bool segmentCut(Vertex A, Vertex B, Vertex C, Vertex D)
	{
		Vec2f AB{ B - A }, CD{ D - C };
		Vec2f AC{ C - A }, AD{ D - A }, CA{ A - C }, CB{ B - C };
		
		/*std::cout << "A : " << A.x << "/" << A.y << std::endl;
		std::cout << "B : " << B.x << "/" << B.y << std::endl;
		std::cout << "C : " << C.x << "/" << C.y << std::endl;
		std::cout << "D : " << D.x << "/" << D.y << std::endl;
		std::cout << "AB : " << AB.x << "/" << AB.y << std::endl;
		std::cout << "AC : " << AC.x << "/" << AC.y << std::endl;
		std::cout << "AD : " << AD.x << "/" << AD.y << std::endl;
		std::cout << "det(AB, AC) : " << det(AB, AC) << std::endl;
		std::cout << "det(AB, AD) : " << det(AB, AD) << std::endl;
		std::cout << std::boolalpha;
		std::cout << "segmentCut : " << (det(AB, AC) * det(AB, AD) < 0) << std::endl << std::endl;
		std::cout << std::noboolalpha;*/
		return (det(AB, AC) * det(AB, AD) < 0);// and det(CD, CA) * det(CD, CB) < 0);
		
	}
}
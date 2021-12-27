#pragma once

//STL
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

//SFML
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//Json
#include <nlohmann/json.hpp>

//DeltaEngine
#include "Class/Object.hpp"

//For conversion radians <-> degrees.
#define RAD2DEG 57.29577951
#define DEG2RAD 0.01745329252

using json = nlohmann::json;

namespace DeltaEngine
{
	enum class moveType;

	enum class collisionType;

	json returnJson(std::string jsonPath); // Returns a json array from a .json file.
	bool operator==(ID& lhs, ID& rhs); //Compares 2 ID.

	struct ID;
	class Object;
}
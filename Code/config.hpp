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

//For conversion radians <-> degrees.
#define RAD2DEG 57.29577951
#define DEG2RAD 0.01745329252

using json = nlohmann::json;
using namespace std::literals;
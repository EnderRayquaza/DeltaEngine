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


#define PI 3.141592654 //π
#define RAD2DEG 180./PI //For conversion radians -> degrees.
#define DEG2RAD PI/180. //For conversion degrees -> radians.

using json = nlohmann::json;
using namespace std::literals;

typedef unsigned int uint;
typedef unsigned long ulong;
typedef std::vector<uint> vec_uint;
typedef std::vector<ulong> vec_ulong;
typedef std::string jsonStr;
typedef sf::Vector2i Vertex;
typedef sf::Vector2i Vec2i;
typedef sf::Vector2f Vec2f;

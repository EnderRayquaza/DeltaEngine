#pragma once
/*
* Some abbreviation I use :
* v/vec -> vector
* vtx -> vertex
* func -> function
* str -> string
* pos -> position
* obj -> object
* mng -> manager
* tex -> texture
* nb -> number (of)
*/

//STL
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

//SFML
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//Json
#include <nlohmann/json.hpp>


constexpr auto PI = 3.141592654; //π
constexpr auto RAD2DEG = 180./PI; //For conversion radians -> degrees.
constexpr auto DEG2RAD = PI/180.; //For conversion degrees -> radians.
constexpr auto DS_ALL = -1; //On all displayScreens

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
typedef sf::IntRect AABB;
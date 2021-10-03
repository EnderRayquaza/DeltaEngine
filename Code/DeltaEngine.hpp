//DeltaEngine.hpp
#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <TGUI/TGUI.hpp>

#include <box2d/box2d.h>

#include <nlohmann/json.hpp>

#define RAD2DEG 57.29577951
#define DEG2RAD 0.01745329252

#define STATICBODY 0
#define KINEMATICBODY 1
#define DYNAMICBODY 2

#define TEXTURE_ON true

using json = nlohmann::json;

namespace DeltaEngine
{
    class Project;
	class Game;
	class Object;
	class Entity;


	void print(std::string str, std::string end="none");
	json returnJson(std::string jsonPath);

	class Project
	{
	public:
		Project(std::string name, int version_Major, int version_minor, bool debug, std::string icon);
		std::string get_title();
		bool get_debug();
	protected:
		std::string m_name;
		int m_ver_M;
		int m_ver_m;
		bool m_debug;
		std::string m_ico;
	};

	class Game
	{
	public:
		Game(Project& prj, b2Vec2& gravity, float timeStep = 1.f/60.f, int32 velIt = 6, int32 posIt = 3);
		sf::RenderWindow& get_win();
		b2World& get_world();
		float get_timeStep();
		int32 get_velIt();
		int32 get_posIt();

		void draw();
		void addObj(Object& obj);
		void addEnt(Entity& ent);

	protected:
		Project m_prj;
		sf::RenderWindow m_win;
		std::vector<Object> m_vObj;
		std::vector<Entity> m_vEnt;
		b2Vec2 m_gravity;
		b2World m_world;
		float m_timeStep;
		int32 m_velIt;
		int32 m_posIt;
	};

	class Part
	{
	public:
		Part(std::string jsonPath, b2World& world, sf::Vector2f pos = sf::Vector2f(0, 0));
		double get_coef();
		int get_priority();
		int get_nb_vtx();
		sf::ConvexShape& get_shape();
		sf::Texture& get_texture();
		bool get_textureOn();
		b2Body* get_body();
		sf::Vector2f get_pos(bool inPx=true);
		double get_angle(bool inDeg = true);
	protected:
		double m_coef;
		int m_priority;
		int m_type;
		int m_nb_vtx;
		sf::ConvexShape m_shape;
		sf::Texture m_tex;
		bool m_tex_load;
		b2Body* m_body;
	};

	class Object
	{
	public:
		Object(std::string jsonPath, b2World& world, sf::Vector2f pos = sf::Vector2f(0, 0));
		int get_nb_part();
		std::vector<Part> get_Vpart();
	protected:
		int m_id;
		std::string m_name;
		int m_nb_part;
		std::vector<Part> m_Vpart;
	};

	class Entity : public Object
	{
	public:
		Entity(std::string jsonPath, b2World& world, sf::Vector2f pos = sf::Vector2f(0, 0));
		bool verifyIfAlive();
		void damage(double val);
		void heal(double val);
		void move(int dir, double val, double drag = 0.98, double acc = 0.1);
		void jump(double val);
		void tp(b2Vec2 pos);
	protected:
		double m_hpMax;
		double m_hp;
		bool m_isAlive;
	};
}

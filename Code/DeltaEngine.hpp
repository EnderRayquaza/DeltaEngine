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

enum _partCategory
{
	NOTHING = 0x0000,
	DECOR = 0x0001,
	GROUND = 0x0002,
	PLAYER = 0x0004,
	PNJ = 0x0006,
	ENEMY = 0x0008,
	BULLET = 0x0010,
};

using json = nlohmann::json;

namespace DeltaEngine
{
    class Project;
	class Game;
	class Object;
	class Entity;
	class Light;


	void print(std::string str, std::string end="none");
	json returnJson(std::string jsonPath); //Return a json from a .json file.

	class Project
	{
	public:
		Project(std::string name, int version_Major, int version_minor, bool debug, std::string icon);
		std::string get_title();
		bool get_debug();
	protected:
		std::string m_name;
		int m_ver_M; //Version major.
		int m_ver_m; //Version minor.
		bool m_debug; //If the project is in debug mode.
		std::string m_ico;
	};

	class Game
	{
	public:
		Game(Project& prj, b2Vec2& gravity, sf::Color& bgColor, float timeStep = 1.f/60.f, int32 velIt = 6, int32 posIt = 3);
		sf::RenderWindow& get_win();
		b2World& get_world();
		float get_timeStep();
		int32 get_velIt();
		int32 get_posIt();

		void draw(); //Draws all Objects and Entities in the game.
		void addObj(Object& obj); //Adds an Object to the game.
		void addEnt(Entity& ent); //Idem for Entities.
		void addLgh(Light& lgh); //Idem for Lights.

	protected:
		Project m_prj;
		sf::RenderWindow m_win;
		sf::Color m_bgColor;
		std::vector<Object> m_vObj; //A vector with all Objects of the game.
		std::vector<Entity> m_vEnt; //Idem for Entities.
		std::vector<Light> m_vLgh; //Idem for Light.
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
		bool get_shapeTex();
		bool get_textureOn();
		b2Body* get_body();
		sf::Vector2f get_pos(bool inPx=true);
		double get_angle(bool inDeg = true);
	protected:
		double m_coef; //To convert px (for SFML) & meters (for Box2D).
		int m_priority; //To draw the part in a special order.
		uint16 m_type; //The type of the Part (see enum _partCategory above).
		int m_bodyType; //The type of the body (Static, Kinematic or Dynamic).
		int m_nb_vtx; //The number of vertices.
		sf::ConvexShape m_shape; //The shape (SFML).
		sf::Texture m_tex; //The texture (SFML).
		bool m_shapeTex; //If true, the texture will be shaped by the shape.
		bool m_tex_load; //Contains the value returned by loadFromFile().
		b2Body* m_body; //The body (Box2D).
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
		int m_nb_part; //The number of Parts.
		std::vector<Part> m_Vpart; //A vector with the Parts of the Object.
	};

	class Entity : public Object
	{
	public:
		Entity(std::string jsonPath, b2World& world, sf::Vector2f pos = sf::Vector2f(0, 0));
		bool verifyIfAlive();
		void damage(double val);
		void heal(double val);
		void move(int dir, double val, double drag = 0.98, double acc = 0.1); //Moves the Entity on x axis.
		void jump(double val);
		void tp(b2Vec2 pos); //Teleports the Entity
	protected:
		double m_hpMax;
		double m_hp;
		bool m_isAlive;
	};

	class Light
	{
	public:
		Light(Game& game, sf::Vector2f pos, double rad, int vtx = 21, sf::Vector3f color = sf::Vector3f(255, 255, 255));
		sf::VertexArray& get_vtxArr();
	protected:
		sf::VertexArray m_vtxArr;
	};
}

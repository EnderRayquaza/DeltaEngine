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
	class ShaderManager;


	void print(std::string str, std::string end = "none"); //Like the fonction std::cout.
	json returnJson(std::string jsonPath); //Returns a json from a .json file.

	class Project
	{
	public:
		Project(std::string name, int version_Major, int version_minor, bool debug, std::string icon); //Constructor.

		std::string get_title(); //Returns the name + the version.
		bool get_debug();

		void set_debug(bool val); //Switchs between debug and realese.
	protected:
		std::string m_name; //The name of the Project.
		int m_ver_M; //Version major.
		int m_ver_m; //Version minor.
		bool m_debug; //If the project is in debug mode.
		std::string m_ico; //The path of the icon.
	};

	class Game
	{
	public:
		Game(Project& prj, ShaderManager* shdMgn, b2Vec2& gravity, sf::Color& bgColor, float timeStep = 1.f / 60.f,
			int32 velIt = 6, int32 posIt = 3); //Constructor.
		Project& get_project();
		sf::RenderWindow& get_win();
		std::vector<Object>& get_vObj();
		std::vector<Entity>& get_vEnt();
		std::vector<Light>& get_vLgh();
		b2World& get_world();
		float get_timeStep();
		int32 get_velIt();
		int32 get_posIt();

		void draw(); //Draws all Objects and Entities in the game.
		void addObj(Object& obj); //Adds an Object to the game.
		void addEnt(Entity& ent); //Idem for Entities.
		void addLgh(Light& lgh); //Idem for Lights.

	protected:
		Project m_prj; //The Project linked with the Game.
		ShaderManager* m_shdMgn;

		sf::RenderWindow m_win; //A RenderWindow to draw and show the Game.
		sf::Color m_bgColor; //The color of the background.
		std::vector<Object> m_vObj; //A vector with all Objects of the game.
		std::vector<Entity> m_vEnt; //Idem for Entities.
		std::vector<Light> m_vLgh; //Idem for Light.
		std::vector<Light> m_vPartLgh; //A vector with all Lights of all the Parts.

		b2Vec2 m_gravity; //A vector defining the gravity.
		b2World m_world; //The World where the Bodies move.
		float m_timeStep; //The time step for b2box.
		int32 m_velIt; //Param for b2box.
		int32 m_posIt; //Idem.
	};

	class Part
	{
	public:
		Part(std::string jsonPath, b2World& world, sf::Vector2f pos = sf::Vector2f(0, 0)); //Constructor.
		double get_coef();
		int get_priority();
		int get_nb_vtx();
		sf::ConvexShape& get_shape();
		sf::Texture& get_texture();
		bool get_shapeTex();
		bool get_textureOn();
		bool get_animated();
		sf::Vector2i get_sizeSpr();
		sf::Vector2i get_currentSprPos();
		sf::IntRect get_currSprRect();
		int get_shdIdx();
		b2Body* get_body();
		sf::Vector2f get_pos(bool inPx = true);
		double get_angle(bool inDeg = true);
		std::vector<Light>& get_vLgh();

		void set_currentSprPos(sf::Vector2i pos);
		void set_currentSprPos(unsigned int posx, unsigned int posy);
	protected:
		double m_coef; //To convert px (for SFML) & meters (for Box2D).
		int m_priority; //To draw the part in a special order.
		uint16 m_type; //The type of the Part (see enum _partCategory above).
		int m_bodyType; //The type of the body (Static, Kinematic or Dynamic).
		int m_nb_vtx; //The number of vertices.
		sf::ConvexShape m_shape; //The shape (SFML).
		sf::Texture m_tex; //The texture (SFML).
		sf::Texture m_currTex; //The current texture (SFML).
		bool m_shapeTex; //If true, the texture will be shaped by the shape.
		bool m_tex_load; //Contains the value returned by loadFromFile().
		bool m_animated; //If true, it has an animated texture.
		sf::Vector2i m_sizeSpr; //The size of one sprite in the sheet.
		sf::Vector2i m_currentSprPos; //The position of the current sprite in the sheet.
		int m_shdIdx;
		b2Body* m_body; //The body (Box2D).
		std::vector<Light> m_vLgh; //A vector with light which follow the part.
	};

	class Object
	{
	public:
		Object(std::string jsonPath, b2World& world, sf::Vector2f pos = sf::Vector2f(0, 0)); //Constructor.
		int get_nb_part();
		std::vector<Part>& get_vPart();
		void updateLight(); //Updates the position of Lights.
	protected:
		int m_id; //The id of the Object.
		std::string m_name; //The name of the Object.
		int m_nb_part; //The number of Parts.
		std::vector<Part> m_vPart; //A vector with the Parts of the Object.
	};

	class Entity : public Object
	{
	public:
		Entity(std::string jsonPath, b2World& world, sf::Vector2f pos = sf::Vector2f(0, 0)); //Constructor.
		bool verifyIfAlive(); //Verifies if the Entity is sill alive.
		void damage(double val); //Reduces his HP.
		void heal(double val); //Increases his HP.
		void move(float dir, float val, float acc = 0.1); //Moves the Entity.
		void tp(b2Vec2 pos); //Teleports the Entity.
	protected:
		double m_hpMax; //Its health points maximum.
		double m_hp; //Its actual health points.
		bool m_isAlive; //True if m_hp>0, else False.
	};

	class Light
	{
	public:
		Light(sf::Vector2f pos, double rad, int vtx = 21, sf::Vector3f color = sf::Vector3f(255, 255, 255)); //Constructor.

		sf::VertexArray& get_vtxArr();

		void set_pos(sf::Vector2f pos);
	protected:
		double m_rad; //Its radius in px.
		sf::VertexArray m_vtxArr; //An Array with all the vertices of the Light.
		sf::Vector2f m_pos; //Its positon in px.
	};

	class ShaderManager
	{
	public:
		ShaderManager(std::string listPath);

		sf::Shader* get_shd(int index);

	protected:
		std::vector<sf::Shader*> m_vShd;
	};
}
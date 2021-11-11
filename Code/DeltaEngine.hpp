//DeltaEngine.hpp
#pragma once

//STL
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//SFML
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//Box2d
#include <box2d/box2d.h>
//Json
#include <nlohmann/json.hpp>

//For conversion radians <-> degrees.
#define RAD2DEG 57.29577951
#define DEG2RAD 0.01745329252
//For Game::draw
#define PRIORITIES 5
//For bodyType (box2d)
#define STATICBODY 0
#define KINEMATICBODY 1
#define DYNAMICBODY 2

//For collision (box2d)
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
	class Game;
	class Object;
	class Entity;
	class Light;
	class ShaderManager;

	json returnJson(std::string jsonPath); //Returns a json from a .json file.

	class Game
	{
	public:
		Game() = delete; //Constructor deleted
		Game(std::string name, int version_Major, int version_minor, bool debug, bool textureOn,
			std::string icon, ShaderManager* shaderManager, sf::Color& bgColor, b2Vec2& gravity,
			float timeStep = 1.f / 60.f, int32 velocityIt = 6, int32 positionIt = 3); //Constructor
		~Game(); //Destructor

		//Getters
		std::string get_title(bool showVersion = false); //Returns the name + the version.
		bool get_debug();
		bool get_textureOn();
		std::vector<Object>& get_vObject();
		std::vector<Entity>& get_vEntity();
		std::vector<Light>& get_vLight();

		sf::RenderWindow& get_window();

		b2World& get_world();
		float get_timeStep();
		int32 get_velocityIt();
		int32 get_positionIt();

		//Setters
		void set_debug(bool value); //Switchs between debug and release.
		void set_textureOn(bool value);
		void addObject(Object& object); //Adds an Object to the game.
		void addEntity(Entity& entity); //Idem for Entities.
		void addLight(Light& light); //Idem for Lights.
		void removeObject(int index); //Removes an Object of the game.
		void removeEntity(int index); //Idem for Enities.
		void removeLight(int index); //Idem for Lights.

		//Others
		void draw(); //Draws all Objects and Entities in the game.

	protected:
		//Game members
		std::string m_name; //The name of the program.
		unsigned int m_version_M; //Version major.
		unsigned int m_version_m; //Version minor.
		bool m_debug; //If the program is in debug mode.
		bool m_textureOn; //If you show the textures or not.
		std::string m_icon; //The path of the icon.
		std::vector<Object> m_vObject; //A vector with all Objects of the game.
		std::vector<Entity> m_vEntity; //Idem for Entities.
		std::vector<Light> m_vLight; //Idem for Light.
		std::vector<Light> m_vPartLight; //A vector with all Lights of all the Parts.

		//Game members (SFML)
		ShaderManager* m_shaderManager;
		sf::RenderWindow m_window; //A RenderWindow to draw and show the Game.
		sf::Color m_bgColor; //The color of the background.

		//Game members (Box2d)
		b2Vec2 m_gravity; //A vector defining the gravity.
		b2World m_world; //The World where the Bodies move.
		float m_timeStep; //The time step for b2box.
		int32 m_velocityIt; //Param for b2box, increase it and perfomance will drops but quality 
							//will grows.
		int32 m_positionIt; //Idem.
	};

	class Part
	{
	public:
		Part() = delete; //Constructor deleted.
		Part(std::string jsonPath, b2World& world, sf::Vector2f position = sf::Vector2f(0, 0)); 
		//Constructor.
		~Part();

		friend Game;
		friend Object;
		friend Entity;

		//Getters
		sf::IntRect get_currentSpriteRect();
		sf::Vector2f get_position(bool inPx = true);
		double get_angle(bool inDeg = true);

		//Setters
		void set_currentSpritePosition(sf::Vector2i position);
		void set_currentSpritePosition(unsigned int positionX, unsigned int positionY);

	protected:
		//Part members
		int m_priority; //To draw the part in a special order.
		std::vector<int> m_shaderIndexes; //The index of the shader applied
		std::vector<Light> m_vLight; //A vector with light which follow the part.

		double m_coef; //To convert px (for SFML) & meters (for Box2D).
		int m_nb_vertices; //The number of vertices.

		//Part members (SFML)
		sf::ConvexShape m_shape; //The shape.
		sf::Texture m_texture; //The texture.
		sf::Texture m_currTexture; //The current texture.
		bool m_shapeTexture; //If true, the texture will be shaped by the shape.
		bool m_animated; //If true, it has an animated texture.
		sf::Vector2i m_sizeSprite; //The size of one sprite in the sheet.
		sf::Vector2i m_currentSpritePosition; //The position of the current sprite in the sheet.

		//Part members (Box2d)
		uint16 m_type; //The type of the Part (see enum _partCategory above).
		int m_bodyType; //The type of the body (Static, Kinematic or Dynamic).
		b2Body* m_body; //The body.
	};

	class Object
	{
	public:
		Object() = delete; //Constructor deleted.
		Object(std::string jsonPath, b2World& world, sf::Vector2f position = sf::Vector2f(0, 0));
		//Constructor.
		~Object(); //Destructor.

		friend void Game::draw();

		//Others
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
		Entity() = delete; //Deleted Constructor.
		Entity(std::string jsonPath, b2World& world, sf::Vector2f position = sf::Vector2f(0, 0));
		//Constructor.
		~Entity(); //Destructor.

		void move(float direction, float value, float acceleration = 0.1); //Moves the Entity.

	protected:

	};

	class Light
	{
	public :
		Light() = delete; //Deleted Constructor.
		Light(double radius, int vertices, sf::Vector2f position,
			sf::Color color = sf::Color(255, 255, 255), double intensity = 255);//Constructor
		//for classic Lights.
		Light(double radius, int vertices, sf::Vector2f position, double abscissa_angle,
			double opening_angle, sf::Color color = sf::Color(255, 255, 255),
			double intensity = 255); //Constructor for directed Lights.
		~Light(); //Destructor.

		//Getters
		sf::VertexArray& get_vertexArray();

		//Setters
		void set_position(sf::Vector2f position);

		//Others
		void generate();

	protected:
		//Light members
		double m_radius; //Its radius in px.
		sf::VertexArray m_vertexArray; //An Array with all the vertices of the Light.
		sf::Vector2f m_position; //Its positon in px.
		sf::Color m_color;
		double m_intensity;

		bool m_directed; //If the light is a directed light.

		//Directed Light members
		double m_abscissa_angle; //The angle between the axe of abscissa and the light.
		double m_opening_angle; //Tha angle between the first and last ray.
	};

	class ShaderManager
	{
	public:
		ShaderManager() = delete; //Deleted constructor.
		ShaderManager(std::string listPath); //Constructor.
		~ShaderManager(); //Destructor.

		//Getters
		sf::Shader* get_shader(int index);

	protected:
		std::vector<sf::Shader*> m_vShader;
	};
}
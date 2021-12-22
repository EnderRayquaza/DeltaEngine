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
//#include <box2d/box2d.h>
//Json
#include <nlohmann/json.hpp>

//DeltaEngine
#include "Physics/basic_struct.hpp"
#include "Physics/Body.hpp"
#include "Physics/collision.hpp"
#include "Physics/World.hpp"

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
enum class _PartCategory
{
	NOTHING = 0x0000,
	DECOR = 0x0001,
	GROUND = 0x0002,
	FRIEND = 0x0004,
	ENEMY = 0x0008,
	BULLET = 0x0010
};

enum class _Light
{
	CLASSIC,
	DIRECTIONAL,
	LINEAR
};

using json = nlohmann::json;

namespace DeltaEngine
{
	/**
	* @namespace DeltaEngine
	* @brief A 2d engine made with [SFML](sfml-dev.org "SFML") (window,render,sound) and [Box2D](box2d.ord "Box2D") (physics).
	* 
	* DeltaEngine
	* -----------
	* 
	* It uses multiples classes, firstly Game, that contains infos about your project 
	* (name, version, debug/release mode, etc...) and your [Objects](@ref Object),
	* [Entities](@ref Entity), [Lights](@ref Light) and [Shaders](@ref ShaderManager).
	* This class draws everything on the [window](@ref Game::m_window) too.
	* 
	* [Objects](@ref Object) and [Entities](@ref Entity) are pretty the same,
	* but [Entities](@ref Entity) can move and [Objects](@ref Object) are statics. 
	* They're containers of [Parts](@ref Part).
	* 
	* [Parts](@ref Part) are a combination of a texture ([SFML](sfml-dev.org "SFML")) and
	* an hitbox ([Box2D](box2d.ord "Box2D")). They can be animated 
	* and [Shaders](@ref ShaderManager) can be applied on.
	* 
	* [Lights](@ref Light) enlight the scene. They can be 
	* [circular or directional](@ref Light::m_directional) and
	* you can change their [color](@ref Light::m_color) and [brightness](@ref Light::m_intensity).
	* 
	* [ShaderManagers](@ref ShaderManager) manage and stock all your [Shaders](@ref ShaderManager).
	* They're accessible by their index.
	* 
	* 
	* Made by [EnderRayquaza](https://github.com/EnderRayquaza, "My Github") / Under MIT Licence.\n
	* Copyright DeltaEngine belong to EnderRayquaza.\n
	* You must quote me if your use my work. Thx.
	*/
	/**
	* @fn json returnJson(std::string jsonPath)
	* @brief Returns a json array from a .json file.
	* @param jsonPath (std::string) The path of the json file.
	* @return (json) A json array with all the datas of the file.
	*/
	/**
	* @class Game
	* @brief A class that contains yours Object, Entity, Light and ShaderManager.
	*
	* Game contains infos about your project 
	(name, version, debug/release mode, etc...) and your Object, Entity, Light and Shader (in a ShaderManager).
	* This class draws everything on the window too.
	*/
	/**
	* @class Part
	* @brief The DeltaEngine item base. It contains a sprite (with SFML) and an hitbox (with Box2D).
	* 
	* Friend with Game, Object and Entity
	* Part are a combination of a texture (SFML) and an hitbox (Box2D). They can be animated and Shader can be applied on.
	* @see Object
	* @see Entity
	*/
	/**
	* @class Object
	* @brief A class that contains statics Part.
	* 
	* Friend with Game.
	* Object and Entity are pretty the same, but Entity can move and Object are statics. They're container of Part.
	* @see Entity
	*/
	/**
	* @class Entity
	* @brief [Inherits from Object] It contains kinematics and dynamics Part.
	* 
	* Friend with Game.
	* Object and Entity are pretty the same, but Entity can move and Object are statics. They're container of Part.
	* @see Object
	*/
	/**
	* @class Light
	* @brief A class that enlights the Game. There're circles Light and directional Light.
	* 
	* Light enlight the scene. They can be circular or directional and you can change their color and brightness.
	*/
	/**
	* @class TextureManager
	* @brief A class that contains and manage sf::Texture
	* @see sf::Texture
	*
	* TextureManager manage and stock all your Texture. They're accessible by their index.
	* You can select a part of the texture with its coordinates.
	*/
	/**
	* @class ShaderManager
	* @brief A class that contains and manage sf::Shader
	* @see sf::Shader
	* 
	* ShaderManager manage and stock all your Shader. They're accessible by their index.
	*/

	class Game;
	class Part;
	class Object;
	class Entity;
	class Light;
	class LinearLight;
	class TextureManager;
	class ShaderManager;
	class DEContactListener;

	json returnJson(std::string jsonPath); ///< Returns a json array from a .json file.

	class Game
	{
	public:
		/**
		* @fn Game() = delete
		* This constructor is deleted.
		* @see Game(std::string name, int version_Major, int version_minor, bool debug, bool textureOn, std::string icon, ShaderManager* shaderManager, sf::Color& bgColor, b2Vec2& gravity, float timeStep = 1.f / 60.f, int32 velocityIt = 6, int32 positionIt = 3)
		*/
		/**
		* @fn Game(std::string name, int version_Major, int version_minor, bool debug, bool textureOn, std::string icon, ShaderManager* shaderManager, sf::Color& bgColor, b2Vec2& gravity, float timeStep = 1.f / 60.f, int32 velocityIt = 6, int32 positionIt = 3)
		* The main and default Constructor.
		* @param name (std::string) The name of the Game.
		* @param version_Major (int) The version major of the Game (v.Major.minor).
		* @param version_minor (int) The version minor of the Game (v.Major.minor).
		* @param debug (bool) Define if the Game is in debug mode.
		* @param textureOn (bool) Define if the texture will be drawed.
		* @param icon (std::string) The path to the icon.
		* @param shaderManager (ShaderManager* ) The ShaderManager of the Game.
		* @see ShaderManager
		* @param bgColor (sf::Color&) The color of the background.
		* @param gravity (b2Vec2&) The force of gravity which is applied in th Game.
		* @param timeStep (float) The time step between to frame.
		* @param velocityIt (int32) A param for Box2D. Increase it and the quality will be increase but the performance will drops.
		* @see b2World::Step
		* @param positionIt (int32) A param for Box2D. Increase it and the quality will be increase but the performance will drops.
		* @see b2World::Step
		*/
		/**
		* @fn ~Game()
		* Default destructor.
		* Not defined.
		*/
		/**
		* @fn std::string get_title(bool showVersion = false)
		* Returns the title ie. the name + the version (if you want it).
		* @param showVersion (bool) If you want the version in the title.
		* @return (std::string) The title.
		*/
		/**
		* @fn bool get_debug()
		* @return m_debug() (bool)
		*/
		/**
		* @fn bool get_textureOn()
		* @return m_textureOn() (bool)
		*/
		/**
		* @fn std::vector<Object>& get_vObject()
		* @return m_vObject() (std::vector<Object>&)
		*/
		/**
		* @fn std::vector<Entity>& get_vEntity()
		* @return m_vEntity() (std::vector<Entity>&)
		*/
		/**
		* @fn std::vector<Light>& get_vLight()
		* @return m_vLight() (std::vector<Light>&)
		*/
		/**
		* @fn sf::RenderWindow& get_window()
		* @return m_window() (sf::RenderWindow&)
		*/
		/**
		* @fn b2World& get_world()
		* @return m_world() (b2World&)
		*/
		/**
		* @fn float get_timeStep()
		* @return m_timeStep() (float)
		*/
		/**
		* @fn int32 get_velocityIt()
		* @return m_velocityIt() (int32)
		*/
		/**
		* @fn int32 get_positionIt()
		* @return m_positionIt() (int32)
		*/
		//Todo : Doc of Setters
		/**
		* @fn void draw()
		* Draws Objects, Entity, Light and Shader on m_window().
		*/

		Game() = delete; ///< Constructor deleted
		Game(std::string name, int version_Major, int version_minor, bool debug, bool textureOn, std::string icon,
			TextureManager* textureManager, ShaderManager* shaderManager, DEContactListener* contactListener,
			sf::Color& bgColor, b2Vec2& gravity, float timeStep = 1.f / 60.f, int32 velocityIt = 6,
			int32 positionIt = 3); ///< Default Constructor
		Game(const Game&); ///< Copy Constructor
		Game operator=(const Game&);
		~Game(); ///< Destructor

		friend DEContactListener;

		//Getters
		std::string get_title(bool showVersion = false); ///< Returns the name + the version.
		bool get_debug();
		bool get_textureOn();
		std::vector<Object>& get_vObject();
		std::vector<Entity>& get_vEntity();
		std::vector<Light>& get_vLight();

		sf::RenderWindow* get_window();

		b2World& get_world();
		float get_timeStep();
		int32 get_velocityIt();
		int32 get_positionIt();

		//Setters
		void set_debug(bool value); ///< Switchs between debug and release.
		void set_textureOn(bool value); ///< Enable/Disable the textures.
		void addObject(Object& object); ///< Adds an Object to the game.
		void addEntity(Entity& entity); ///< Adds an Entity to the game.
		void addLight(Light& light); ///< Adds an Light to the game.
		void addLinearLight(LinearLight& light); ///< Adds an Light to the game.
		void removeObject(int index); ///< Removes an Object of the game.
		void removeEntity(int index); ///< Removes an Entity of the game.
		void removeLight(int index); ///< Removes an Light of the game.
		void removeLinearLight(int index); ///< Removes an Light of the game.

		//Others
		void init();
		void draw(); ///< Draws Object, Entity, Light and sf::Shader.
		Part& findPart(b2Body* body);

	protected:
		//Game members
		std::string m_name; ///< The name of the program.
		unsigned int m_version_M; ///< Version major.
		unsigned int m_version_m; ///< Version minor.
		bool m_debug; ///< If the program is in debug mode.
		bool m_textureOn; ///< If you show the textures or not.
		std::string m_icon; ///< The path of the icon.
		std::vector<Object> m_vObject; ///< A vector with all Objects of the game.
		std::vector<Entity> m_vEntity; ///< A vector with all Entity of the game.
		std::vector<Light> m_vLight; ///< A vector with all Light of the game.
		std::vector<LinearLight> m_vLinLight; ///< A vector with all Light of the game.
		std::vector<Light> m_vPartLight; ///< A vector with all Light of all the Part.
		std::vector<LinearLight> m_vPartLinLight; ///< A vector with all Light of all the Part.

		//Game members (SFML)
		TextureManager* m_textureManager;
		ShaderManager* m_shaderManager; ///< The ShaderManager of the Game.
		sf::RenderWindow* m_window; ///< A RenderWindow to draw and show the Game.
		sf::Color m_bgColor; ///< The color of the background.

		//Game members (Box2d) 
		DEContactListener* m_contactListener;
		b2Vec2 m_gravity; ///< A vector defining the gravity.
		b2World m_world; ///< The World where the Bodies move.
		float m_timeStep; ///< The time step for b2box.
		int32 m_velocityIt; ///< Param for b2box, increase it and perfomance will drops but quality will grows.
		int32 m_positionIt; ///< Idem.
	};

	class Part
	{
	public:
		/**
		* @fn Part() = delete
		* Deleted constructor. Don't use it.
		*/
		/**
		* @fn Part(std::string jsonPath, b2World& world, sf::Vector2f position = sf::Vector2f(0, 0))
		* @param jsonPath (std::string) The path of the .json file where's the data.
		* @param world (b2World&) The world where the Part will be created.
		* @param position (sf::Vector2f) The postion of the Part in meters.
		* 
		* The default constructor. Use .json to create your Part.
		*/
		/**
		* @fn ~Part()
		* Destructor.
		*/
		/**
		* @fn sf::IntRect get_currentSpriteRect()
		* @return (sf::IntRect) The rectangle of the current texture.
		*/
		/**
		* @fn sf::Vector2f get_position(bool inPx = true)
		* @param inPx (bool) Set true if you want the position in px, false for meters.
		* @return (sf::Vector2f) The position of the Part.
		*/
		/**
		* @fn double get_angle(bool inDeg = true)
		* @param Set true if you want the angle in degrees, false for radians.
		* @return (double) The angle of the Part.
		*/
		/**
		* @fn void set_currentSpritePosition(sf::Vector2i position)
		* @param position (sf::Vector2i) The new position of the current sprite position.
		*/
		/**
		* @fn void set_currentSpritePosition(unsigned int positionX, unsigned int positionY)
		* @param positionX (unsigned int) The new position of the current sprite position on the X axis.
		* @param positionY (unsigned int) The new position of the current sprite position on the Y axis.
		*/

		Part() = delete; ///< Constructor deleted.
		Part(std::string jsonPath, b2World& world, sf::Vector2f position = sf::Vector2f(0, 0)); ///< Default Constructor.
		~Part() = default; ///< Destructor.

		friend Game;
		friend Object;
		friend Entity;

		//Getters
		sf::IntRect get_currentSubTextureRect();
		sf::Vector2f get_position(bool inPx = true); ///< Set true if you want the position in px, false for meters.
		double get_angle(bool inDeg = true); ///< Set true if you want the angle in degrees, false for radians.

		//Setters
		void set_currentSubTexturePosition(sf::Vector2i position);
		void set_currentSubTexturePosition(unsigned int positionX, unsigned int positionY);

	protected:
		//Part members
		int m_priority; ///< To draw the Part in a special order.
		std::vector<Light> m_vLight; ///< A vector with Light which follow the Part.
		std::vector<LinearLight> m_vLinLight; ///< A vector with LinearLight which follow the Part.

		double m_coef; ///< To convert px (for SFML) & meters (for Box2D).
		int m_nb_vertices; ///< The number of vertices.

		//Part members (SFML)
		sf::ConvexShape m_shape; ///< The shape.
		int m_textureIndex; ///< The texture index in the TextureManager.
		int m_shaderIndex; ///< The index of the Shader applied. Set -1 if you don't want a Shader.
		bool m_shapeTexture; ///< If true, the texture will be shaped by the shape.
		bool m_subTexture; ///< If true, it has a sub-texture.
		//bool m_repeated; ///< Defines if the Texture is repeated in the Sprite.
		bool m_smoothed; ///< Defines if the Texture is smoothed.
		//sf::Vector2i m_sizeSprite; ///< The size of one sprite in the sheet.
		sf::Vector2i m_sizeSubTexture; ///< The size of one sub-texture in the sheet.
		sf::Vector2i m_currentSubTexturePosition; ///< The position of the current sub-texture in the sheet.

		//Part members (Box2d)
		_PartCategory m_type; ///< The type of the Part (see enum _PartCategory above).
		int m_bodyType; ///< The type of the body (Static, Kinematic or Dynamic).
		b2Body* m_body; ///< The body.
	};

	class Object
	{
	public:
		/**
		* @fn Object() = delete
		* Deleted constructor. Don't use it.
		*/
		/**
		* @fn Object(std::string jsonPath, b2World& world, sf::Vector2f position = sf::Vector2f(0, 0))
		* @param jsonPath (std::string) The path of the .json file where's the data.
		* @param world (b2World&) The world where the differents Part will be created.
		* @param position (sf::Vector2f) The postion of the Object in meters.
		*
		* The default constructor. Use .json to create your Object.
		* @see Part::Part(std::string jsonPath, b2World& world, sf::Vector2f position = sf::Vector2f(0, 0))
		*/
		/**
		* @fn ~Object()
		* Destructor.
		*/
		/**
		* @fn void updateLight()
		*/

		Object() = delete; ///< Constructor deleted.
		Object(std::string jsonPath, b2World& world, sf::Vector2f position = sf::Vector2f(0, 0));
		///< Constructor.
		//~Object(); ///< Destructor.

		friend Game;

		//Others
		void updateLight(); ///< Updates the position of Lights.

	protected:
		int m_id; ///< The id of the Object.
		std::string m_name; ///< The name of the Object.
		int m_nb_part; ///< The number of Part.
		std::vector<Part> m_vPart; ///< A vector with the Part of the Object.
	};

	class Entity : public Object
	{
	public:
		/**
		* @fn Entity() = delete
		* Deleted constructor. Don't use it.
		*/
		/**
		* @fn Entity(std::string jsonPath, b2World& world, sf::Vector2f position = sf::Vector2f(0, 0))
		* @param jsonPath (std::string) The path of the .json file where's the data.
		* @param world (b2World&) The world where the differents Part will be created.
		* @param position (sf::Vector2f) The postion of the Entity in meters.
		*
		* The default constructor. Use .json to create your Entity.
		* @see Part::Part(std::string jsonPath, b2World& world, sf::Vector2f position = sf::Vector2f(0, 0))
		*/
		/**
		* @fn ~Entity()
		* Destructor.
		*/
		/**
		* @fn void move(float direction, float value, float acceleration = 0.1)
		* @param direction (float) The angle (in degrees) of the direction.
		* @param value (float) The velocity of the movement.
		* @param acceleation (float) Th acceleration to go at the velocity.
		* 
		* I dislike this function, so it will be modified soon and maybe modified a lot of time.
		*/
		Entity() = delete; ///< Deleted Constructor.
		Entity(std::string jsonPath, b2World& world, sf::Vector2f position = sf::Vector2f(0, 0));
		///< Constructor.
		//~Entity(); ///< Destructor.

		void move(float direction, float value, float acceleration = 0.1); ///< Moves the Entity.

	protected:
	};

	class Light
	{
	public :
		/**
		* @fn Light() = delete
		* Deleted constructor. Don't use it.
		*/
		/**
		* @fn Light(double radius, int vertices, sf::Vector2f position, sf::Color color = sf::Color(255, 255, 255), double intensity = 255)
		* @param radius (double) The radius of the Light.
		* @param vertices (int) The number of vertices in the cirle. More improves quality, but dicrease perfs.
		* @param position (sf::Vector2f) The position of the Light (center of the circle).
		* @param color (sf::Color) The color of the Light.
		* @param intensity (double) The intensity/brightness of the Light
		* 
		* Use this constructor for circles Light.
		*/
		/**
		* @fn Light(double radius, int vertices, sf::Vector2f position, double abscissa_angle, double opening_angle, sf::Color color = sf::Color(255, 255, 255), double intensity = 255);
		* @param radius (double) The radius of the Light.
		* @param vertices (int) The number of vertices in the cirle. More improves quality, but dicrease perfs.
		* @param position (sf::Vector2f) The position of the Light (center of the circle).
		* @param abscissa_angle (double) The angle between the abscissa axis and the Light.
		* @param opening_angle (double) Tha angle between the first and last ray.
		* @param color (sf::Color) The color of the Light.
		* @param intensity (double) The intensity/brightness of the Light
		*
		* Use this constructor for directionals Light.
		*/
		/**
		* @fn ~Light()
		* Destructor.
		*/
		/**
		* @fn sf::VertexArray& get_vertexArray()
		* @return m_vertexArray() (sf::VertexArray)
		*/
		/**
		* @fn void set_position(sf::Vector2f position)
		* @param position (sf::Vector2f) The new position of the Light.
		*/
		/**
		* @fn void generate()
		*/

		Light() = delete; ///< Deleted Constructor.
		Light(std::string jsonPath, _Light typeLight);
		//~Light(); ///< Destructor.

		friend Game;
		friend Part;

		//Getters
		sf::VertexArray& get_vertexArray();

		//Setters
		void set_position(sf::Vector2f position);

		//Others
		void generate(); ///< Calculate the render of the Light.

	protected:
		_Light m_type; ///< The type of the Light.

		//Light members
		double m_coef;
		double m_radius; ///< Its radius in px.
		sf::VertexArray m_vertexArray; ///< An Array with all the vertices of the Light.
		sf::Vector2f m_position_origin; ///< Its original positon in px.
		sf::Vector2f m_position; ///< Its positon in px.
		sf::Color m_color; ///< The color of the Light.
		double m_brightness; ///< The brightness at the source of the Light.
		double m_intensity; ///< The intensity of the Light.

		//Directed Light members
		double m_abscissa_angle; ///< The angle between the axe of abscissa and the light.
		double m_opening_angle; ///< The angle between the first and last ray.
	};

	class LinearLight : public Light
	{
	public:
		LinearLight() = delete;
		LinearLight(std::string jsonPath);
		~LinearLight() = default;

		friend Game;
		friend Part;

		//Other
		void generate();

	protected:
		//Linear Light members
		std::vector<sf::VertexArray> m_vVertexArray;
		std::vector<sf::Vector2f> m_verticesPosition; ///< The position of each vertex.
	};

	class TextureManager
	{
		/**
		* @fn TextureManager() = delete;
		* Deleted constructor. Don't use it.
		*/
		/**
		* @fn TextureManager(std::string jsonPath);
		* @param jsonPath (std::string) The path to the .json file defining TextureManager.
		*/
		/**
		* @fn ~TextureManager()
		* Destructor.
		*/
		/**
		* @fn sf::Texture* get_texture(unsigned int index)
		* @param index (unsigned int) The index of the Texture.
		* @return (sf::Texture*) A pointer the choosen Texture in m_vTexture(). 
		*/
		/**
		* @fn sf::Texture* get_texture(unsigned int index, sf::Vector2i spriteSize, sf::Vector2i position)
		* @param index (unsigned int) The index of the Texture.
		* @param spriteSize (sf::Vector2i) The size of the sprite.
		* @param position (sf::Vector2i) The position of the choosen Texture.
		* @return (sf::Texture*) A pointer the choosen Texture in m_vTexture().
		*/
		/**
		* @fn sf::Texture* get_texture(unsigned int index, sf::IntRect rect)
		* @param index (unsigned int) The index of the Texture.
		* @param rect (sf::IntRect) The rectangle where is the choosen Texture.
		* @return (sf::Texture*) A pointer the choosen Texture in m_vTexture().
		*/
	public:
		TextureManager() = delete;
		TextureManager(std::string jsonPath);
		~TextureManager();

		sf::Texture* get_texture(unsigned int index);

		void init();

	protected:
		std::string m_jsonPath;
		std::vector<sf::Texture*> m_vTexture;
	};

	class ShaderManager
	{
	public:
		/**
		* @fn ShaderManager() = delete;
		* Deleted constructor. Don't use it.
		*/
		/**
		* @fn ShaderManager(std::string jsonPath);
		* @param jsonPath (std::string) The path to the .json file defining ShaderManager.
		*/
		/**
		* @fn ~ShaderManager()
		* Destructor.
		*/
		/**
		* @fn sf::Shader* get_shader(int index)
		* @param index (int) The index of the Shader.
		* @return (sf::Shader*) A pointer the choosen Shader in m_vShader(). 
		*/
		ShaderManager() = delete; ///< Deleted constructor.
		ShaderManager(std::string jsonPath); ///< Constructor.
		~ShaderManager(); ///< Destructor.

		//Getters
		sf::Shader* get_shader(int index); ///< Gets the Shader by the index.

		void init();

	protected:
		std::string m_jsonPath;
		std::vector<sf::Shader*> m_vShader; ///< The vector with all the Shader.
	};
}
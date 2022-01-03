#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Light.hpp"
#include "Manager.hpp"
#include "Object.hpp"
#include "World.hpp"

typedef std::vector<DeltaEngine::Object> vecObj;
typedef std::vector<DeltaEngine::Light> vecLight;

namespace DeltaEngine
{
	class Game
	{
	public:
		Game() = delete;
		Game(std::string name, Vec2i version, std::string ico, BodyManager&, TextureManager&, 
			ShaderManager&,	Vec2i windowSize, uint windowFlag, sf::Color, double timeStep);
		~Game() = default;
		
		void init();
		void draw();

		void addObject(Object&); ///< Adds an Object to the game.
		void addLight(Light&); ///< Adds an Light to the game.
		void removeObject(Id); ///< Removes an Object of the game.
		void removeLight(Id); ///< Removes an Light of the game.

		bool _debug, _textureOn;
	protected:
		std::string m_name;
		Vec2i m_version;
		std::string m_ico;
		vecObj m_vObj;
		vecLight m_vLight;

		BodyManager& m_bodyMng;
		TextureManager& m_textureMng;
		ShaderManager& m_shaderMng;
		sf::RenderWindow m_window;
		sf::Color m_bgColor;
		World m_world;
		double m_timeStep;

	};
}

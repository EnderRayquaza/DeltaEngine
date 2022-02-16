#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Light.hpp"
#include "Manager.hpp"
#include "Object.hpp"
#include "World.hpp"

namespace DeltaEngine
{
	class Game
	{
	public:
		Game() = delete;
		Game(std::string name, Vec2i version, std::string ico, uint nbDisplayScreen,
			TextureManager&, ShaderManager&, ShapeManager&, Vec2i windowSize, uint windowFlag,
			sf::Color, double timeStep);
		~Game() = default;
		
		void init();
		void drawBody(Body&, sf::Sprite&, sf::RenderTexture&);
		void drawDebugShape(Body&, sf::RenderTexture&);
		void drawLight(Light&, sf::RenderTexture&);
		void draw();

		void addObject(Object&); ///< Adds an Object to the game.
		void addLight(Light&); ///< Adds an Light to the game.
		void removeObject(Id); ///< Removes an Object of the game.
		void removeLight(Id); ///< Removes an Light of the game.

		bool _debug{false}, _textureOn{true};
		uint _debugDisplayScreen{0};

	protected:
		//Basic members
		std::string m_name;
		Vec2i m_version;
		std::string m_ico;
		std::vector<Object> m_vObj{};
		std::vector<Light> m_vLight{};
		uint m_nbDisplayScreen;

		//Render members
		TextureManager& m_textureMng;
		ShaderManager& m_shaderMng;
		ShapeManager& m_shapeMng;
		Vec2i m_sizeScreen;
		sf::RenderWindow m_window;
		sf::Color m_bgColor;

		//Physic members
		World m_world;
		double m_timeStep;
		

	};
}

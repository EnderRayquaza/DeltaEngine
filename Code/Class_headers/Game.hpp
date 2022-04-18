#pragma once

#include "../config.hpp"
#include "Area.hpp"
#include "Body.hpp"
#include "Manager.hpp"
#include "ShapeSheet.hpp"
#include "Texture.hpp"

namespace DeltaEngine
{
	class Game
	{
	public:
		Game() = default;
		~Game() = default;

		void init(); //Inits all things in the Game.
		void step(double time); //The main function.
		void draw(); //Draw the element of the game on the window.
		void drawBody(Body&, sf::Sprite&, sf::RenderTexture&); //Draw a body.
		void drawDebugShape(Body&, sf::RenderTexture&); //Draw the edge of a shape.

		bool _debug{ false }, _textureOn{ true };
		uint _debugDisplayScreen{ 0 };

	protected:
		std::string m_name, m_icoPath;
		uint m_nbDisplayScreen;

		Vec2i m_sizeScreen;
		sf::RenderWindow m_window;
		sf::Color bgColor;

		//Managers
		Manager<Area>& m_mngArea;
		Manager<Body>& m_mngBody;
		Manager<ShapeSheet>& m_mngSS;
		Manager<Texture>& m_mngTex;
	};
}
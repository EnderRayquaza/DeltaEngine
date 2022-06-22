#include "../Class_headers/Game.hpp"

namespace DeltaEngine
{
	Game::Game(jsonStr path, Manager<Area>& ma, Manager<Body>& mb, Manager<ShapeSheet>& mss,
		Manager<Texture>& mt) : Loadable(path), m_mngArea{ ma }, m_mngBody{ mb }, m_mngSS{ mss },
		m_mngTex{ mt }
	{}

	bool Game::load()
	{
		json j{ returnJson(_path) };
		m_name = std::string(j["name"]);
		m_icoPath = std::string(j["icopath"]);
		m_nbDisplayScreen = uint(j["nbDS"]);

		m_sizeScreen = Vec2i{ j["size"][0], j["size"][1] };
		_window.create(sf::VideoMode(m_sizeScreen.x, m_sizeScreen.y), m_name);
		m_bgColor = sf::Color{ sf::Uint8(j["bgColor"][0]), sf::Uint8(j["bgColor"][1]),
			sf::Uint8(j["bgColor"][2]) };
		return true;
	}

	void Game::init()
	{
		_window.setTitle(m_name);
		sf::Image ico{};
		if (!ico.loadFromFile(m_icoPath))
		{
			std::cout << "Ico not loaded" << std::endl;
		}
		_window.setIcon(ico.getSize().x, ico.getSize().y, ico.getPixelsPtr());

		m_mngBody.loadItem();
		m_mngSS.loadItem();
		//m_mngTex.loadItem();
	}

	void Game::step(double time)
	{
		//Render
		draw();

		//Physic
		for (size_t i{0}; i < m_mngArea.size(); i++)
		{
			m_mngArea[i].step(0);
			m_mngArea[i].step(time);
		}
		for (size_t i{ 0 }; i < m_mngBody.size(); i++)
		{
			m_mngBody[i].move(time);
		}
	}

	void Game::draw()
	{
		sf::RenderTexture rtTex{}, rtDShape{}, rtTamp{};
		sf::Sprite spr{};
		rtTex.create(m_sizeScreen.x, m_sizeScreen.y);
		rtDShape.create(m_sizeScreen.x, m_sizeScreen.y);
		rtTamp.create(m_sizeScreen.x, m_sizeScreen.y);

		_window.clear(m_bgColor);

		for (size_t i{ 0 }; i < m_nbDisplayScreen; i++)
		{
			rtTex.clear(sf::Color::Transparent);
			rtDShape.clear(sf::Color::Transparent);
			rtTamp.clear(sf::Color::Transparent);

			//std::cout << "current ds :" << i << std::endl;
			for (size_t j{ 0 }; j < m_mngBody.size(); j++)
			{
				Body& body{ m_mngBody[j] };
				if (body.m_displayScreen == i)
				{
					//std::cout << "current body :" << body._id.intKey1 << "-" << body._id.intKey2 << std::endl;
					if (_textureOn)
					{
						drawBody(body, spr, rtTex);
					}
					if (_debug)
					{
						drawDebugShape(body, rtDShape);
					}

					body.nextFrameTex();
					body.nextFrameSS();
				}

			}

			rtTex.display(); //Updates the RenderTexture.
			spr.setTexture(rtTex.getTexture(), true); //Puts it on the sprite.
			rtTamp.draw(spr); //And draws it on the tampon texture.

			rtDShape.display(); //Updates it.
			spr.setTexture(rtDShape.getTexture(), true); //Puts it on the sprite.
			rtTamp.draw(spr); //And draws it on the tampon texture.

			rtTamp.display(); //Updates it.
			spr.setTexture(rtTamp.getTexture(), true); //Puts it on the sprite.
			_window.draw(spr); //And draws it on the window.
		}

		_window.display(); //Updates the window.
	}

	void Game::drawBody(Body& body, sf::Sprite& spr, sf::RenderTexture& rtTex)
	{
		spr.setTexture(m_mngTex[body.m_indexTexMng], true); //Sets the Texture to the Sprite.
		sf::IntRect iR{ body.getCoordTex(),	m_mngTex[body.m_indexTexMng].get_frameSize() }; //Defines the TextureRect.
		spr.setTextureRect(iR); //Applies it.
		spr.setPosition((Vec2f)body.m_pos); //Sets the pos of the body.
		spr.setRotation(body.m_angle); //Same for angle.
		rtTex.draw(spr); //Draws the sprite on the RenderTexture.
	}

	void Game::drawDebugShape(Body& body, sf::RenderTexture& rtDShape)
	{
		Shape& shape{ m_mngSS[body.m_indexSSMng][body.getCoordShape()] }; //Gets the shape.
		sf::ConvexShape convShape{ shape.nbVtx() }; //Defines the shape for SFML.
		for (size_t i{ 0 }; i < shape.nbVtx(); i++) //Sets the points at their pos.
		{
			convShape.setPoint(i, (Vec2f)shape.getVertices(body.m_pos, body.m_angle)[i]);
		}
		convShape.setFillColor(sf::Color::Transparent); //Colors the shape.
		convShape.setOutlineThickness(2.f); //Idem
		switch (body.m_moveType)
		{
		case DeltaEngine::moveType::Static:
			convShape.setOutlineColor(sf::Color::Blue);
			break;
		case DeltaEngine::moveType::Kinematic:
			convShape.setOutlineColor(sf::Color::Red);
			break;
		case DeltaEngine::moveType::Dynamic:
			convShape.setOutlineColor(sf::Color::Green);
			break;
		default:
			convShape.setOutlineColor(sf::Color::White);
			break;
		}

		rtDShape.draw(convShape); //Draws the shape on the RenderTexture.
	}
}
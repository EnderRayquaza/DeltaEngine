#include "Game.hpp"

namespace DeltaEngine
{
	Game::Game(std::string name, Vec2i version, std::string ico, uint nbDS,
		TextureManager& tm, ShaderManager& sdm, ShapeManager& spm, Vec2i wSize, uint wFlag,
		sf::Color color, double timeStep) : m_name{ name }, m_version{ version }, m_ico{ ico },
		m_nbDisplayScreen{ nbDS }, m_textureMng{ tm }, m_shaderMng{ sdm }, m_shapeMng{ spm },
		m_window{ {(uint)wSize.x, (uint)wSize.y}, "Wating Initialisation...", wFlag },
		m_bgColor{ color },	m_timeStep{ timeStep }
	{}

	void Game::init()
	{
		if (_debug)
		{
			m_window.setTitle(m_name + " v"s + std::to_string(m_version.x) + "."s +
				std::to_string(m_version.y) + " (_debug mode)");
		}
		else
		{
			m_window.setTitle(m_name);
		}
		sf::Image ico{};
		if (!ico.loadFromFile(m_ico))
		{
			error("File not found : " + m_ico, "Game.cpp", 19, ErrorType::FILE_NOT_FOUND);
		}
		m_window.setIcon(ico.getSize().x, ico.getSize().y, ico.getPixelsPtr());
		m_textureMng.load();
		m_shaderMng.load();
		m_shapeMng.load();
	}

	void Game::drawBody(Body& body, sf::Sprite& sprite, sf::RenderTexture& objTex)
	{
		sprite.setTextureRect(body.get_textureRect());
		sprite.setTexture(m_textureMng[body.m_tmIndex]);
		sprite.setPosition((Vec2f)body.m_position);
		sprite.setRotation(body.m_angle);
		objTex.draw(sprite, &m_shaderMng[0]);
	}

	void Game::drawDebugShape(Body& body, sf::RenderTexture& debugTex)
	{
		sf::ConvexShape cvx{ body.get_shape(m_shapeMng).m_vertices.size() };
		for (size_t i{0}; i < cvx.getPointCount(); i++)
		{
			cvx.getPoint(i) = (Vec2f)body.get_shape(m_shapeMng).m_vertices[i];
		}
		cvx.setRotation(body.m_angle);
		cvx.setFillColor(sf::Color::Transparent);
		cvx.setOutlineThickness(10);
		switch (body.m_moveType)
		{
		case moveType::Static:
			cvx.setOutlineColor(sf::Color::Blue);
			break;
		case moveType::Kinematic:
			cvx.setOutlineColor(sf::Color::Red);
			break;
		case moveType::Dynamic:
			cvx.setOutlineColor(sf::Color::Green);
			break;
		default:
			error("Unknown moveType", "Game.cpp", 66, ErrorType::SWITCH_DEFAULT);
			break;
		}
		debugTex.draw(cvx);
	}

	void Game::drawLight(Light& light, sf::RenderTexture& lightTex)
	{
		switch (light.type)
		{
		case DeltaEngine::LightType::Undefined:
			error("Undefined light was called", "Game.cpp", 77, ErrorType::OTHER);
			break;
		case DeltaEngine::LightType::Classic:
			lightTex.draw(light.get_vtxArray());
			break;
		case DeltaEngine::LightType::Directional:
			lightTex.draw(light.get_vtxArray());
			break;
		case DeltaEngine::LightType::Linear:
			for (auto& vtxArray : light.get_vecVtxArray())
			{
				lightTex.draw(vtxArray);
			}
			break;
		default:
			error("Unknown LightType", "Game.cpp", 92, ErrorType::SWITCH_DEFAULT);
			break;
		}
	}

	void Game::draw()
	{
		sf::Sprite sprite{};
		sf::RenderTexture objTex{}, lightTex{}, debugTex{}, tampTex{};
		std::vector<Body> vBody{};

		objTex.create(m_sizeScreen.x, m_sizeScreen.y);
		lightTex.create(m_sizeScreen.x, m_sizeScreen.y);
		debugTex.create(m_sizeScreen.x, m_sizeScreen.y);
		tampTex.create(m_sizeScreen.x, m_sizeScreen.y);

		m_window.clear();
		objTex.clear(sf::Color::Transparent);
		lightTex.clear(m_bgColor);
		debugTex.clear(sf::Color::Transparent);
		tampTex.clear(sf::Color::Transparent);

		//Collects all the bodies.
		for (auto& obj : m_vObj)
		{
			for (auto& body : obj.m_vBody)
			{
				vBody.push_back(body);
			}
		}

		//Draws debug items.
		if (_debug)
		{
			for (auto& body : vBody)
			{
				if (body.m_displayScreen == _debugDisplayScreen) //If the body is on the debug DS.
				{
					drawBody(body, sprite, objTex);
				}
				else if (body.m_displayScreen == -1) //If the object needs to be drawn.
				{
					drawBody(body, sprite, objTex);
				}
			}
		}

		//Draw items.
		for (size_t screen{0}; screen < m_nbDisplayScreen; screen++) //For every screen.
		{
			if (_textureOn)
			{
				for (auto& body : vBody)
				{
					if (body.m_displayScreen == screen) //If we are at the current screen.
					{
						drawBody(body, sprite, objTex);
					}
					else if (body.m_displayScreen == -1) //If the object needs to be drawn.
					{
						drawBody(body, sprite, objTex);
					}
				}
			}

			for (auto& light : m_vLight)
			{
				if (light.m_displayScreen == screen) //Idem.
					drawLight(light, lightTex);
				else if (light.m_displayScreen == -1) //Idem too.
					drawLight(light, lightTex);
			}

			//Adding objects textures to the tamp.
			objTex.display();
			sprite.setTexture(objTex.getTexture());
			tampTex.draw(sprite, sf::BlendAdd);

			//Adding lights to the tamp.
			lightTex.display();
			sprite.setTexture(lightTex.getTexture());
			tampTex.draw(sprite, sf::BlendMultiply);

			//Copy the tamp on the window and clear it.
			tampTex.display();
			sprite.setTexture(tampTex.getTexture());
			m_window.draw(sprite, sf::BlendAdd);
			tampTex.clear();
		}
		m_window.display();
	}

	void Game::addObject(Object& obj)
	{
		m_vObj.push_back(obj);
	}

	void Game::addLight(Light& light)
	{
		m_vLight.push_back(light);
	}

	void Game::removeObject(Id id)
	{
		for (size_t i{ 0 }; i < m_vObj.size(); i++)
		{
			if (m_vObj[i].get_id() == id)
			{
				m_vObj.erase(m_vObj.begin() + i);
			}
		}
	}

	void Game::removeLight(Id id)
	{
		for (size_t i{ 0 }; i < m_vLight.size(); i++)
		{
			if (m_vLight[i].get_id() == id)
			{
				m_vLight.erase(m_vLight.begin() + i);
			}
		}
	}

}
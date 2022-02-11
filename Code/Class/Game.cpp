#include "Game.hpp"

namespace DeltaEngine
{
	void Game::init()
	{
		if (_debug)
			m_window.setTitle(m_name + " v"s + std::to_string(m_version.x) + "."s +
				std::to_string(m_version.y) + " (_debug mode)");
		else
			m_window.setTitle(m_name);
		sf::Image ico{};
		if (!ico.loadFromFile(m_ico))
			std::cerr << m_ico << " : File not find" << std::endl;
		m_window.setIcon(ico.getSize().x, ico.getSize().y, ico.getPixelsPtr());
		m_textureMng.load();
		m_shaderMng.load();
	}

	void Game::drawBody(Body& body, sf::Sprite& sprite, sf::RenderTexture& objTex)
	{
		sprite.setTextureRect(body.get_textureRect());
		sprite.setTexture(m_textureMng[body.m_tmIndex]);
		objTex.draw(sprite, &m_shaderMng[0]);
	}

	void Game::drawLight(Light& light, sf::RenderTexture& lightTex)
	{
		switch (light.type)
		{
		case DeltaEngine::LightType::Undefined:
			std::cout << "Undefined light was called in Game::draw" << std::endl;
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

		for (size_t screen{0}; screen < m_nbDisplayScreen; screen++) //For every screen.
		{
			for (auto& body : vBody)
			{
				if (body.m_displayScreen == screen) //If we are at the current screen.
					drawBody(body, sprite, objTex);
				else if (body.m_displayScreen == -1) //If the object needs to be drawn.
					drawBody(body, sprite, objTex);
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
#include "Game.hpp"

namespace DeltaEngine
{
	Game::Game(std::string name, Vec2i version, std::string ico, BodyManager& bodyManager,
		TextureManager& textureManager, ShaderManager& shaderManager,
		Vec2i windowSize, uint windowFlag, sf::Color bgColor, double timeStep) : m_name{ name },
		m_version{ version }, m_bodyMng{ bodyManager }, m_textureMng{ textureManager },
		m_shaderMng{ shaderManager }, m_window{ {windowSize.x, windowSize.y}, m_name, windowFlag },
		m_bgColor{ bgColor }, m_timeStep{ timeStep }, m_ico{ ico }
	{}

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
		m_bodyMng.load();
		m_textureMng.load();
		m_shaderMng.load();
	}

	void Game::draw(){}

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
#include "Manager.hpp"

namespace DeltaEngine
{
	ShapeManager::ShapeManager(jsonStr jsonPath):m_jsonPath(jsonPath)
	{}

	ShapeSheet& ShapeManager::operator[](uint const index) noexcept
	{
		if (index >= m_items.size())
		{
			return;
		}
		return m_items[index];
	}

	void ShapeManager::load()
	{
		json j{ returnJson(m_jsonPath) };
		for (auto& e : j["ShapeSheet"])
		{
			ShapeSheet item{(std::string)e["file"], (uint)e["size"][0], (uint)e["size"][1]};
			m_items.push_back(item);
		}
	}


	TextureManager::TextureManager(jsonStr jsonPath):m_jsonPath(jsonPath)
	{}

	sf::Texture& TextureManager::operator[](size_t index)
	{
		if (index >= m_items.size())
		{
			return;
		}
		return m_items[index];
	}

	void TextureManager::load()
	{
		json j{ returnJson(m_jsonPath) };
		for (auto e : j["textures"])
		{
			sf::Texture item;
			if (!item.loadFromFile((std::string)e))
			{
				error("Cannot load this : " + (std::string)e, "Manager.cpp", 48,
					ErrorType::FILE_NOT_FOUND);
			}
			m_items.push_back(item);
		}
	}


	ShaderManager::ShaderManager(jsonStr jsonPath) :m_jsonPath(jsonPath)
	{}

	sf::Shader& ShaderManager::operator[](size_t index)
	{
		if (index >= m_items.size())
		{
			return;
		}
		return m_items[index];
	}

	void ShaderManager::load()
	{
		json j{ returnJson(m_jsonPath) };
		for (auto e : j["shaders"]["vert"])
		{
			sf::Shader item;
			if (!item.loadFromFile((std::string)e, sf::Shader::Vertex))
			{
				error("Cannot load this : " + (std::string)e, "Manager.cpp", 76,
					ErrorType::FILE_NOT_FOUND);
			}
			m_items.push_back(item);
		}
		for (auto e : j["shaders"]["frag"])
		{
			sf::Shader item;
			if (!item.loadFromFile((std::string)e, sf::Shader::Fragment))
			{
				error("Cannot load this : " + (std::string)e, "Manager.cpp", 86,
					ErrorType::FILE_NOT_FOUND);
			}
			m_items.push_back(item);
		}
		for (auto e : j["shaders"]["vert&frag"])
		{
			sf::Shader item;
			if (!item.loadFromFile((std::string)e[0], (std::string)e[1]))
			{
				error("Cannot load this : " + (std::string)e, "Manager.cpp", 96,
					ErrorType::FILE_NOT_FOUND);
			}
			m_items.push_back(item);
		}
	}
}
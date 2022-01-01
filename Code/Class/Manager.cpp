#include "Manager.hpp"

namespace DeltaEngine
{
	BodyManager::BodyManager(std::string jsonPath) :m_jsonPath(jsonPath)
	{}

	BodyManager::~BodyManager()
	{
		for (auto item : m_items)
		{
			item->~Body();
			delete item;
		}
	}

	Body* BodyManager::operator()(size_t i, size_t j, size_t k)
	{
		size_t index{ i + m_size[0] * j + (m_size[0] * m_size[1]) * k };
		if (index >= m_size[3])
		{
			return nullptr;
		}
		return m_items[index];
	}

	void BodyManager::set_jsonPath(std::string jsonPath) noexcept
	{
		m_jsonPath = jsonPath;
	}

	void BodyManager::load()
	{
		json j{ returnJson(m_jsonPath) };
		m_size = { (size_t)j["size"][0], (size_t)j["size"][1], (size_t)j["size"][2],
			(size_t)j["size"][0] * (size_t)j["size"][1] * (size_t)j["size"][2] };
		for (auto& e : j["body"])
		{
			Body* item = new Body{(std::string)e};
			m_items.push_back(item);
		}
	}


	TextureManager::TextureManager(std::string jsonPath):m_jsonPath(jsonPath)
	{}

	TextureManager::~TextureManager()
	{
		for (auto item : m_items)
		{
			item->~Texture();
			delete item;
		}
	}

	sf::Texture* TextureManager::operator[](size_t index)
	{
		if (index >= m_items.size())
		{
			return nullptr;
		}
		return m_items[index];
	}

	void TextureManager::set_jsonPath(std::string jsonPath) noexcept
	{
		m_jsonPath = jsonPath;
	}

	void TextureManager::load()
	{
		json j{ returnJson(m_jsonPath) };
		for (auto e : j["textures"])
		{
			sf::Texture* item = new sf::Texture();
			if (!item->loadFromFile((std::string)e))
			{
				std::cerr << "Cannot load this : " << (std::string)e << std::endl;
			}
			m_items.push_back(item);
		}
	}


	ShaderManager::ShaderManager(std::string jsonPath) :m_jsonPath(jsonPath)
	{}

	ShaderManager::~ShaderManager()
	{
		for (auto item : m_items)
		{
			item->~Shader();
			delete item;
		}
	}

	sf::Shader* ShaderManager::operator[](size_t index)
	{
		if (index >= m_items.size())
		{
			return nullptr;
		}
		return m_items[index];
	}

	void ShaderManager::set_jsonPath(std::string jsonPath) noexcept
	{
		m_jsonPath = jsonPath;
	}

	void ShaderManager::load()
	{
		json j{ returnJson(m_jsonPath) };
		for (auto e : j["shaders"]["vert"])
		{
			sf::Shader* item = new sf::Shader();
			if (!item->loadFromFile((std::string)e, sf::Shader::Vertex))
			{
				std::cerr << "Cannot load this : " << (std::string)e << std::endl;
			}
			m_items.push_back(item);
		}
		for (auto e : j["shaders"]["frag"])
		{
			sf::Shader* item = new sf::Shader();
			if (!item->loadFromFile((std::string)e, sf::Shader::Fragment))
			{
				std::cerr << "Cannot load this : " << (std::string)e << std::endl;
			}
			m_items.push_back(item);
		}
		for (auto e : j["shaders"]["vert&frag"])
		{
			sf::Shader* item = new sf::Shader();
			if (!item->loadFromFile((std::string)e[0], (std::string)e[1]))
			{
				std::cerr << "Cannot load this : " << (std::string)e << std::endl;
			}
			m_items.push_back(item);
		}
	}
}
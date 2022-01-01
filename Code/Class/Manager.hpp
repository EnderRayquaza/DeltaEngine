#pragma once

#include "../config.hpp"
#include "Body.hpp"

namespace DeltaEngine
{
	class BodyManager : public sf::NonCopyable
	{
	public:
		BodyManager() = default;
		BodyManager(std::string jsonPath);
		~BodyManager();

		Body* operator()(size_t i, size_t j, size_t k);

		void set_jsonPath(std::string jsonPath) noexcept;

		void load();
	private:
		std::string m_jsonPath;
		std::array<size_t, 4> m_size;
		std::vector<Body*> m_items;
	};

	class TextureManager : public sf::NonCopyable
	{
	public:
		TextureManager() = default;
		TextureManager(std::string jsonPath);
		~TextureManager();

		sf::Texture* operator[](size_t index);

		void set_jsonPath(std::string jsonPath) noexcept;

		void load();

	protected:
		std::string m_jsonPath;
		std::vector<sf::Texture*> m_items;
	};

	class ShaderManager : public sf::NonCopyable
	{
	public:
		ShaderManager() = default;
		ShaderManager(std::string jsonPath);
		~ShaderManager();

		sf::Shader* operator[](size_t index);

		void set_jsonPath(std::string jsonPath) noexcept;

		void load();

	protected:
		std::string m_jsonPath;
		std::vector<sf::Shader*> m_items;
	};
}

#pragma once

#include "../config.hpp"
#include "Body.hpp"

namespace DeltaEngine
{
	class ShapeManager
	{
	public:
		ShapeManager() = delete;
		ShapeManager(jsonStr jsonPath);
		~ShapeManager() = default;

		ShapeSheet& operator[](uint const index);

		void load();

	protected:
		jsonStr m_jsonPath;
		std::vector<ShapeSheet> m_items;
	};

	class TextureManager : public sf::NonCopyable
	{
	public:
		TextureManager() = delete;
		TextureManager(jsonStr jsonPath);
		~TextureManager() = default;

		sf::Texture& operator[](size_t index);

		void load();

	protected:
		jsonStr m_jsonPath;
		std::vector<sf::Texture> m_items;
	};

	class ShaderManager : public sf::NonCopyable
	{
	public:
		ShaderManager() = delete;
		ShaderManager(jsonStr jsonPath);
		~ShaderManager() = default;

		sf::Shader& operator[](size_t index);

		void load();

	protected:
		jsonStr m_jsonPath;
		std::vector<sf::Shader> m_items;
	};
}

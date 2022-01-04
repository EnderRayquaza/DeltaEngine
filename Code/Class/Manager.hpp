#pragma once

#include "../config.hpp"
#include "Body.hpp"

namespace DeltaEngine
{
	class ShapeSheet : public std::vector<Shape>
	{
	public:
		ShapeSheet() = delete;
		ShapeSheet(std::string jsonPath);
		~ShapeSheet() = default;

		Shape& operator()(uint const indexX, uint const indexY);

	protected:
		std::vector<Shape> m_items;
	};

	class ShapeManager
	{
	public:
		ShapeManager() = delete;
		ShapeManager(std::string jsonPath);
		~ShapeManager() = default;

		ShapeSheet& operator[](uint const index) noexcept;

	protected:
		std::vector<ShapeSheet> m_items;
	};

	class TextureManager : public sf::NonCopyable
	{
	public:
		TextureManager() = delete;
		TextureManager(std::string jsonPath);
		~TextureManager();

		sf::Texture* operator[](size_t index);

		void load();

	protected:
		std::string m_jsonPath;
		std::vector<sf::Texture*> m_items;
	};

	class ShaderManager : public sf::NonCopyable
	{
	public:
		ShaderManager() = delete;
		ShaderManager(std::string jsonPath);
		~ShaderManager();

		sf::Shader* operator[](size_t index);

		void load();

	protected:
		std::string m_jsonPath;
		std::vector<sf::Shader*> m_items;
	};
}

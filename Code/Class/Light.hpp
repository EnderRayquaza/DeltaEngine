#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Game.hpp"

namespace DeltaEngine
{

	enum class LightType;
	class Light;
	class ClassicLight;
	class DirectionalLight;
	class LinearLight;

	enum class LightType
	{
		Undefined,
		Classic,
		Directional,
		Linear
	};

	class Light : public Identifiable
	{
	public:
		Light() = delete;
		Light(std::string jsonPath);
		virtual ~Light() = default;

		virtual sf::VertexArray get_vtxArray() = 0;
		virtual std::vector<sf::VertexArray> get_vecVtxArray() = 0;
		void set_position(Vec2i position) noexcept;

		virtual void generate() = 0;

		friend class Game;
	protected:
		LightType const type{ LightType::Undefined };
		double m_radius;
		Vec2i m_position;
		sf::Color m_color;
		double m_brightness, m_intensity;
		int m_displayScreen;
	};

	class ClassicLight : public Light
	{
	public:
		ClassicLight(std::string jsonPath);
		virtual ~ClassicLight() = default;

		virtual sf::VertexArray get_vtxArray();

		virtual void generate();

		friend class Game;
	protected:
		LightType const type{ LightType::Classic };
		sf::VertexArray m_vtxArray;
	};

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(std::string jsonPath);
		virtual ~DirectionalLight() = default;

		virtual sf::VertexArray get_vtxArray();

		void generate();

		friend class Game;
	protected:
		LightType const type{ LightType::Directional };
		sf::VertexArray m_vtxArray;
		double m_xAxisAngle, m_openingAngle;
	};

	class LinearLight : public Light
	{
	public:
		LinearLight(std::string jsonPath);
		virtual ~LinearLight() = default;

		virtual std::vector<sf::VertexArray> get_vecVtxArray();

		void generate();

		friend class Game;
	protected:
		LightType const type{ LightType::Linear };
		std::vector<sf::VertexArray> m_vtxArrays;
		std::vector<Vertex> m_vertices;
	};
}
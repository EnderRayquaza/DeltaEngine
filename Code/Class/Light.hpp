#pragma once

#include "../config.hpp"
#include "../basic.hpp"

namespace DeltaEngine
{
	class Light;
	class ClassicLight;
	class DirectionalLight;
	class LinearLight;

	class Light : public Identifiable
	{
	public:
		Light() = delete;
		Light(std::string jsonPath);
		~Light() = default;


		void set_position(Vec2i position) noexcept;

		virtual void generate() = 0;

	protected:
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

		void generate();

	protected:
		sf::VertexArray m_vtxArray;
	};

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(std::string jsonPath);

		void generate();

	protected:
		sf::VertexArray m_vtxArray;
		double m_xAxisAngle, m_openingAngle;
	};

	class LinearLight : public Light
	{
	public:
		LinearLight(std::string jsonPath);

		void generate();

	protected:
		std::vector<sf::VertexArray> m_vtxArrays;
		std::vector<Vertex> m_vertices;
	};
}
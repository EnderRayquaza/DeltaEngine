#include "Light.hpp"

namespace DeltaEngine
{
	Light::Light(jsonStr jsonPath)
	{
		json j{ returnJson(jsonPath) };
		m_radius = (double)j["radius"];
		m_position = { (double)j["position"][0], (double)j["position"][1] };
		m_color = { (double)j["color"][0], (double)j["color"][1],  (double)j["color"][2] };
		m_brightness = (double)j["brightness"];
		m_intensity = (double)j["intensity"];
		m_displayScreen = (int)j["displayScreen"];
	}

	void Light::set_position(Vec2i position) noexcept
	{
		m_position = position;
	}

	ClassicLight::ClassicLight(jsonStr jsonPath):Light(jsonPath)
	{}

	sf::VertexArray ClassicLight::get_vtxArray()
	{
		return m_vtxArray;
	}

	void ClassicLight::generate()
	{
		m_vtxArray[0].position = (Vec2f)m_position;
		m_vtxArray[0].color = sf::Color(m_color.r, m_color.b, m_color.g, m_brightness);

		for (size_t i{ 0 }; i < m_vtxArray.getVertexCount() - 1; i++) //The first vertex is already placed.
		{
			double angle = 2 * PI * i / (m_vtxArray.getVertexCount() - 2); //Calculate the angle (0-Center-Vextex)
			//The last vertex will be at the same place than the first.

			m_vtxArray[i + 1].position = sf::Vector2f((m_position.x + cos(angle) * m_radius),
				(m_position.y - sin(angle) * m_radius)); //Sets the vertex at its pos with trigo.

			m_vtxArray[i + 1].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);
		}
	}

	DirectionalLight::DirectionalLight(jsonStr jsonPath) :Light(jsonPath)
	{
		json j{ returnJson(jsonPath) };
		m_xAxisAngle = j["xAxisAngle"];
		m_openingAngle = j["openingAngle"];
	}

	sf::VertexArray DirectionalLight::get_vtxArray()
	{
		return m_vtxArray;
	}

	void DirectionalLight::generate()
	{
		m_vtxArray[0].position = (Vec2f)m_position;
		m_vtxArray[0].color = sf::Color(m_color.r, m_color.b, m_color.g, m_brightness);

		for (size_t i{ 0 }; i < m_vtxArray.getVertexCount() - 1; i++) //The first vertex is already placed.
		{
			double angle = DEG2RAD * m_openingAngle * i / (m_vtxArray.getVertexCount() - 2) +
				DEG2RAD * m_xAxisAngle; //Calculate the angle (0-Center-Vextex)

			m_vtxArray[i + 1].position = sf::Vector2f((m_position.x + cos(angle) * m_radius),
				(m_position.y - sin(angle) * m_radius)); //Sets the vertex at its pos with trigo.

			m_vtxArray[i + 1].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);
		}
	}

	LinearLight::LinearLight(jsonStr jsonPath) :Light(jsonPath)
	{
		json j{ returnJson(jsonPath) };
		for (auto& vtx : j["vertices"])
		{
			m_vertices.push_back({vtx[0], vtx[1]});
		}
		for (size_t i{ 0 }; i < 2 * m_vertices.size() + 2; i++)
		{
			m_vtxArrays.push_back(sf::VertexArray(sf::Quads, 4));
		}
	}

	std::vector<sf::VertexArray> LinearLight::get_vecVtxArray()
	{
		return m_vtxArrays;
	}

	void LinearLight::generate()
	{
		for (size_t i{ 0 }; i < m_vtxArrays.size() - 4; i++) //The 4 final quads are generated apart.
		{
			if (i < m_vertices.size() - 1)
			{
				m_vtxArrays[i][0].position = sf::Vector2f(m_vertices[i].x,
					m_vertices[i].y);
				m_vtxArrays[i][0].color = sf::Color(m_color.r, m_color.b, m_color.g, m_brightness);
				m_vtxArrays[i][1].position = sf::Vector2f(m_vertices[i + 1].x,
					m_vertices[i + 1].y);
				m_vtxArrays[i][1].color = sf::Color(m_color.r, m_color.b, m_color.g, m_brightness);

				m_vtxArrays[i][2].position = sf::Vector2f(m_vertices[i + 1].x,
					(m_vertices[i + 1].y + m_radius));
				m_vtxArrays[i][2].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);
				m_vtxArrays[i][3].position = sf::Vector2f(m_vertices[i].x,
					(m_vertices[i].y + m_radius));
				m_vtxArrays[i][3].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);
			}
			else if (i < 2 * m_vertices.size() - 2)
			{
				size_t i_{ i - m_vertices.size() + 1 };
				m_vtxArrays[i][0].position = sf::Vector2f(m_vertices[i_].x,
					m_vertices[i_].y);
				m_vtxArrays[i][0].color = sf::Color(m_color.r, m_color.b, m_color.g, m_brightness);
				m_vtxArrays[i][1].position = sf::Vector2f(m_vertices[i_ + 1].x,
					m_vertices[i_ + 1].y);
				m_vtxArrays[i][1].color = sf::Color(m_color.r, m_color.b, m_color.g, m_brightness);

				m_vtxArrays[i][2].position = sf::Vector2f(m_vertices[i_ + 1].x,
					(m_vertices[i_ + 1].y - m_radius));
				m_vtxArrays[i][2].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);
				m_vtxArrays[i][3].position = sf::Vector2f(m_vertices[i_].x,
					(m_vertices[i_].y - m_radius));
				m_vtxArrays[i][3].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);
			}
			else
				std::cout << "(Err) i : " << i << std::endl;
		}
		for (size_t i{ 0 }; i < 4; i++)
		{
			std::array<int, 4> arr_i{ 0, 0, m_vertices.size() - 1, m_vertices.size() - 1 };
			std::array<int, 4> arr_x{ -1, -1, 1, 1 };
			std::array<int, 4> arr_y{ -1, 1, -1, 1 };
			size_t i_{ m_vtxArrays.size() - (i + 1) };
			m_vtxArrays[i_][0].position = sf::Vector2f(m_vertices[arr_i[i]].x,
				m_vertices[arr_i[i]].y);
			m_vtxArrays[i_][0].color = sf::Color(m_color.r, m_color.b, m_color.g, m_brightness);

			m_vtxArrays[i_][1].position = sf::Vector2f((m_vertices[arr_i[i]].x + m_radius * arr_x[i]),
				m_vertices[arr_i[i]].y);
			m_vtxArrays[i_][1].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);

			m_vtxArrays[i_][2].position = sf::Vector2f((m_vertices[arr_i[i]].x + m_radius * arr_x[i]),
				(m_vertices[arr_i[i]].y + m_radius * arr_y[i]));
			m_vtxArrays[i_][2].color = sf::Color(m_color.r, m_color.b, m_color.g, 0);

			m_vtxArrays[i_][3].position = sf::Vector2f(m_vertices[arr_i[i]].x,
				(m_vertices[arr_i[i]].y + m_radius * arr_y[i]));
			m_vtxArrays[i_][3].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);
		}
	}
}
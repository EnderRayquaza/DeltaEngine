#pragma once

#include "../config.hpp"
#include "../basic.hpp"

namespace DeltaEngine
{
	class Body : public Identifiable
	{
	public:
		Body();
		Body(Shape shape, AABB aabb, double density = 1, double friction = 0, double restituion = 0,
			Vertex position = {0, 0}, double angle = 0);
		~Body();

	protected:
		Vertex m_position;
		double m_angle;
		Shape m_shape;
		AABB m_aabb;
		double m_mass, m_density, m_friction, m_restitution;
		double m_force, m_impulse, m_velocity;
	};
}
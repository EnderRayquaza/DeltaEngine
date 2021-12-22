#pragma once

#include "../DeltaEngine.hpp"

namespace DeltaEngine
{
	class Body
	{
	public:
		Body(Vertex, Shape&, double, double, double);
		~Body() = default;

		Vertex get_position() const noexcept;

		void set_position(Vertex pos);

		void step();
		void applyForce(Vector force);
		void resetForces();
		void applyImpulse(Vector impulse);
		void resetImpulses();

	protected:
		Vertex m_position;
		Vector m_currentForce;
		Vector m_currentImpulse;
		AABB m_aabb;
		Shape m_shape;
		double m_mass;
		double m_density;
		double m_friction;
		double m_restitution;
	};
}

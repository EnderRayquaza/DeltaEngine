#pragma once

#include "../DeltaEngine.hpp"

namespace DeltaEngine
{
	class Body
	{
	public:
		Body(Vector, Shape&, double, double, double);
		~Body() = default;

		friend Contact;
		friend Collision;

		Vector get_position() const noexcept;

		void set_position(Vector pos);

		void move(double time);
		void applyForce(Vector force);
		void resetForces();
		void applyImpulse(Vector impulse);
		void resetImpulses();

	protected:
		static std::vector<int> listId;
		int m_id;
		Vector m_position;
		Vector m_currentForce;
		Vector m_currentImpulse;
		Vector m_currentVelocity;
		AABB m_aabb;
		Shape m_shape;
		double m_mass;
		double m_density;
		double m_friction;
		double m_restitution;
	};
}

﻿#include "Body.hpp"

namespace DeltaEngine
{
	Body::Body(Vector position, Shape& shape, double density, double friction, double restitution):m_position(position),
		m_shape(shape), m_density(density), m_friction(friction), m_restitution(restitution), m_currentForce(0, 0),
		m_currentImpulse(0, 0), m_currentVelocity(0, 0), m_aabb(findAABBfromShape(m_shape)), m_mass(m_density * aera(m_shape))
	{
		do
		{
			m_id = std::rand();
		} while (*std::find(listId.begin(), listId.end(), m_id) == m_id);
		listId.push_back(m_id);
	}

	Vector Body::get_position() const
	{
		return m_position;
	}

	void Body::set_position(Vector pos)
	{
		m_position = pos;
	}

	void Body::move(double time)
	{
		Vector totForce{ m_currentForce + m_currentImpulse };
		resetImpulses();
		//ΣF = ma <=> a = ΣF.m-1
		Vector a{ totForce / m_mass };
		//v = da.dt-1 = a.t + v0
		m_currentVelocity += a * time;
		m_position += m_currentVelocity;
		m_shape.move(m_currentVelocity);
		m_aabb = findAABBfromShape(m_shape);
	}

	void Body::applyForce(Vector force)
	{
		m_currentForce += force;
	}

	void Body::resetForces()
	{
		m_currentForce = Vector(0, 0);
	}

	void Body::applyImpulse(Vector impulse)
	{
		m_currentImpulse += impulse;
	}

	void Body::resetImpulses()
	{
		m_currentImpulse = Vector(0, 0);
	}
}
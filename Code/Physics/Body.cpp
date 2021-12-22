#include "Body.hpp"

namespace DeltaEngine
{
	Body::Body(Vertex position, Shape& shape, double density, double friction, double restitution):m_position(position),
		m_shape(shape), m_density(density), m_friction(friction), m_restitution(restitution), m_currentForce(0, 0),
		m_currentImpulse(0, 0), m_aabb(findAABBfromShape(m_shape)), m_mass(m_density * aera(m_shape))
	{}

	Vertex Body::get_position() const
	{
		return m_position;
	}

	void Body::set_position(Vertex pos)
	{
		m_position = pos;
	}

	void Body::step()
	{
		Vector totForce{ m_currentForce + m_currentImpulse };
		resetImpulses();
		//Execute totForce on the body
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
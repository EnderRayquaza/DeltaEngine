#include "Fluid.hpp"

namespace DeltaEngine
{
	Fluid::Fluid(Vertex pos, Shape shape, ulong viscosity, ulong density, Vec2f force) :
		m_pos{ pos }, m_shape{ shape }, m_viscosity{ viscosity }, m_density{ density },
		m_force{ force }
	{}

	void Fluid::set_absForce(bool absForce)
	{
		m_absoluteForce = absForce;
	}

	bool Fluid::BodyAlreadyIn(Body& body_)
	{
		for (auto& body : m_vBodies)
		{
			if (body_.get_id() == body.get_id())
			{
				return true;
			}
		}
		return false;
	}

	bool Fluid::BodyMustBeIn(Body& body)
	{
		return pointInShape(body.m_center, m_shape) && !BodyAlreadyIn(body);
	}

	bool Fluid::BodyMustBeOut(Body& body)
	{
		return !pointInShape(body.m_center, m_shape) && BodyAlreadyIn(body);
	}

	void Fluid::add_body(Body& body)
	{
		if (!BodyAlreadyIn(body))
		{
			body.applyForce(m_force);
			m_vBodies.push_back(body);
		}
	}

	void Fluid::remove_body(Body& body)
	{
		for (size_t i{0}; i < m_vBodies.size(); i++)
		{
			if (body.get_id() == m_vBodies[i].get_id())
			{
				body.applyForce(-m_force);
				m_vBodies.erase(m_vBodies.begin() + i);
			}
		}
	}
}
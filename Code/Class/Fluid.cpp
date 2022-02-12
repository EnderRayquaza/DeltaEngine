#include "Fluid.hpp"

namespace DeltaEngine
{
	Fluid::Fluid(Vertex pos, Shape shape, ulong viscosity, ulong density, Vec2f force):m_pos(pos), m_shape(shape),
		m_viscosity(viscosity), m_density(density), m_force(force)
	{}

	void Fluid::set_absForce(bool param)
	{
		m_absoluteForce = param;
	}

	bool Fluid::BodyAlreadyIn(Body& param)
	{
		for (auto& body : m_vBodies)
		{
			if (param.get_id() == body.get_id())
			{
				return true;
			}
		}
		return false;
	}

	bool Fluid::BodyMustBeIn(Body& param)
	{
		return pointInShape(param.m_center, m_shape) && !BodyAlreadyIn(param);
	}

	bool Fluid::BodyMustBeOut(Body& param)
	{
		return !pointInShape(param.m_center, m_shape) && BodyAlreadyIn(param);
	}

	void Fluid::add_body(Body& param)
	{
		if (!BodyAlreadyIn(param))
		{
			param.applyForce(m_force);
			m_vBodies.push_back(param);
		}
	}

	void Fluid::remove_body(Body& param)
	{
		for (size_t i{0}; i < m_vBodies.size(); i++)
		{
			if (param.get_id() == m_vBodies[i].get_id())
			{
				param.applyForce(-m_force);
				m_vBodies.erase(m_vBodies.begin() + i);
			}
		}
	}
}
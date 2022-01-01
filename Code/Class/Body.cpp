#include "Body.hpp"

namespace DeltaEngine
{
	Body::Body(std::string jsonPath)
	{
		json j{ returnJson(jsonPath) };
		m_position = { (int)j["position"][0], (int)j["position"][1] };
		m_angle = (double)j["angle"];
		for (auto& vtx : j["vertices"])
		{
			m_shape.vertices.push_back({ (int)vtx[0], (int)vtx[1] });
		}
		m_aabb = findAABBfromShape(m_shape);
		m_density = j["density"];
		m_mass = m_density * findSurface(m_shape);
		m_friction = j["friction"];
		m_restitution = j["restitution"];
	}

	Body::Body(Shape shape, AABB aabb, double density, double friction, double restituion,
		Vertex position, double angle) : m_shape{ shape }, m_aabb{ aabb }, m_density{ density },
		m_friction{ friction }, m_restitution{ restituion }, m_position{ position },
		m_angle{ angle }
	{}

	void Body::set_position(Vertex position) noexcept
	{
		m_position = position;
	}

	void Body::set_angle(double angle) noexcept
	{
		m_angle = angle;
	}


	void Body::move(double time)
	{
		Vec2f vecTotal{ m_force + m_impulse }, acc{};
		resetImpulse();
		//ΣF = ma <=> a = ΣF.m-1
		acc = vecTotal / m_mass;
		//v = da.dt-1 = a.t + v0
		m_velocity = acc * time;
		m_position += (Vec2i)m_velocity;
		m_shape.move((Vec2i)m_velocity);
		m_aabb.move((Vec2i)m_velocity);

	}

	void Body::rotate(double angle) noexcept
	{
		m_angle += angle;
	}

	void Body::applyForce(Vec2f force) noexcept
	{
		m_force += force;
	}

	void Body::applyImpulse(Vec2f impulse) noexcept
	{
		m_impulse += impulse;
	}

	void Body::resetForce() noexcept
	{
		m_force = Vec2f{ 0, 0 };
	}

	void Body::resetImpulse() noexcept
	{
		m_impulse = Vec2f{ 0, 0 };
	}

}
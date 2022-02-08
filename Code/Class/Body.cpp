#include "Body.hpp"

namespace DeltaEngine
{
	Body::Body(std::string jsonPath)
	{
		json j{ returnJson(jsonPath) };
		m_position = { (int)j["position"][0], (int)j["position"][1] };
		m_angle = (double)j["angle"];
		m_density = j["density"];
		m_mass = m_density * findSurface(get_shape());
		m_friction = j["friction"];
		m_restitution = j["restitution"];
	}

	Body::Body(Vec2i state, moveType mvT, collisionType collT, collisionTargets collTg, int displayScreen,
		double density, double friction,
		double restituion, Vertex position, double angle) : m_state{ state }
		, m_density{ density }, m_friction{ friction },
		m_restitution{ restituion }, m_position{ position }, m_angle{ angle },
		m_center{ NULL, NULL }, m_moveType{ mvT }, m_collisionType{ collT },
		m_displayScreen{ displayScreen },
		m_collisionTargets{ collTg }
	{}

	void Body::set_position(Vertex position) noexcept
	{
		m_position = position;
	}

	void Body::set_angle(double angle) noexcept
	{
		m_angle = angle;
	}


	void Body::move(double timeStep)
	{
		Vec2f vecTotal{ m_force + m_impulse }, acc{};
		resetImpulse();
		//ΣF = ma <=> a = ΣF.m-1
		acc = vecTotal / m_mass;
		//v = da.dt-1 = a.t + v0
		m_velocity = acc * timeStep;
		m_position += (Vec2i)m_velocity;
		//m_shape.move((Vec2i)m_velocity);
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

	void Body::playAnimation(uint index, bool force) noexcept
	{
		if (force)
		{
			m_animationsPlayList.clear();
		}
		m_animationsPlayList.push_back(index);
	}

	Vec2f Body::moveTest(double timeStep)
	{
		Vec2f vecTotal{ m_force + m_impulse }, acc{};
		//ΣF = ma <=> a = ΣF.m-1
		acc = vecTotal / m_mass;
		//v = da.dt-1 = a.t + v0
		return acc * timeStep;
	}

	bool Body::verifyTargeting(Body& body)
	{
		return inVector(body.m_collisionTargets, m_collisionType) &&
			inVector(m_collisionTargets, body.m_collisionType);
	}

	bool verifyTargeting(Body& bA, Body& bB)
	{
		return bA.verifyTargeting(bB);
	}
}
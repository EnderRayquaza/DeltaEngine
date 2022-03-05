#include "Body.hpp"


namespace DeltaEngine
{
	Body::Body(jsonStr jsonPath):m_jsonStr{jsonPath}
	{}

	Body::Body(Vertex position, Vertex center, double angle, uint displayScreen, //Basics
		uint shapeManagerIndex, uint textureManagerIndex, Vec2i startState, Vec2i texSize,
		std::vector<Animation> animations, //Render
		ulong mass, ulong density, ulong friction, ulong restitution, moveType mt,
		collisionType ct, collisionTargets cts) : //Physics
		m_position{ position }, m_center{ center }, m_angle{ angle }, m_displayScreen{ displayScreen },
		m_smIndex{ shapeManagerIndex }, m_tmIndex{ textureManagerIndex }, m_state{ startState },
		m_texSize{ texSize }, m_animations{ animations }, m_mass{ mass }, m_density{ density },
		m_friction{ friction }, m_restitution{ restitution }, m_moveType{ mt },
		m_collisionType{ ct }, m_collisionTargets{ cts }
	{}

	Shape& const Body::get_shape(ShapeManager& sm) const noexcept
	{
		return sm[m_smIndex][m_state];
	}

	sf::IntRect Body::get_textureRect() const noexcept
	{
		return sf::IntRect{ {m_state.x * m_texSize.x, m_state.y * m_texSize.y}, m_texSize };
	}

	//Basic
	void Body::set_position(Vertex position) noexcept
	{
		m_position = position;
	}

	void Body::set_angle(double angle) noexcept
	{
		m_angle = angle;
	}

	//                                               --> Todo NOW!!! <--                                               //
	void Body::load()
	{
		
		json j{ returnJson(m_jsonStr) };

		//Basic members
		m_position = Vertex{ j["position"][0], j["position"][1] };
		m_center = Vertex{ j["center"][0], j["center"][1] };
		m_angle = (double)j["angle"];
		m_displayScreen = (uint)j["displayScreen"];

		//Render members
		m_smIndex = (uint)j["shapeManagerIndex"];
		m_tmIndex = (uint)j["textureManagerIndex"];
		m_state = Vec2i{ j["startingState"][0], j["startingState"][1] };
		m_texSize = Vec2i{ j["textureSize"][0], j["textureSize"][1] };
		for (auto& jsonPath : j["animations"])
		{
			m_animations.push_back(Animation{ (jsonStr)jsonPath });
		}

		//Physics members
		m_mass = (ulong)j["mass"];
		m_density = (ulong)j["density"];
		m_friction = (ulong)j["friction"];
		m_restitution = (ulong)j["restitution"];
		m_moveType = (moveType)j["moveType"];
		m_collisionType = (collisionType)j["collisionType"];
		for (auto& cT : j["collisionTargets"])
		{
			m_collisionTargets.push_back((collisionType)cT);
		}
	}

	//Render
	void Body::playAnimation(uint index, bool force) noexcept
	{
		if (force)
		{
			m_animationsPlayList.clear();
		}
		m_animationsPlayList.push_back(index);
	}

	//Physic
	void Body::move(double timeStep)
	{
		Vec2f vecTotal{ m_force + m_impulse }, acc{};
		resetImpulse();
		//ΣF = ma <=> a = ΣF.m-1
		acc = vecTotal / m_mass;
		//v = da.dt-1 = a.t + v0
		m_velocity = acc * timeStep;
		m_position += (Vec2i)m_velocity;
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



	bool verifyTargeting(Body& lhs, Body& rhs)
	{
		return lhs.verifyTargeting(rhs);
	}
}
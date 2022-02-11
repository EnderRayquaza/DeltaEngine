#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Body.hpp"
#include "World.hpp"

namespace DeltaEngine
{
	class Sensor;
	class Collision;
	class Contact;
	class Impact;

	class Sensor : public Identifiable
	{
	public:
		Sensor() = delete;
		Sensor(Vertex pos, AABB, std::function<void()> on, std::function<void()> off);
		~Sensor() = default;

		void set_pos(Vertex pos) noexcept;

		bool verifySense(double timeStep);
		std::function<void()> exeFuncOn() const noexcept;
		std::function<void()> exeFuncOff() const noexcept;

		friend class Area;
	protected:
		Vertex m_pos;
		AABB const m_aabb;
		bool m_on{ false };
		std::function<void()> const m_funcOn;
		std::function<void()> const m_funcOff;
		std::vector<Body> const m_bodies;
	};

	class Collision : public Identifiable
	{
	public:
		Collision() = delete;
		Collision(Body& bodyA, Body& bodyB);
		~Collision() = default;

		virtual bool isThereCollision(double timeStep) = 0;
		virtual void begin() = 0;
		virtual void end() = 0;

		friend Area;
	protected:
		Body& m_bodyA, & m_bodyB;
	};

	class Contact : public Collision
	{
	public:
		Contact() = delete;
		Contact(Body& bodyA, Body& bodyB);
		~Contact() = default;

		virtual bool isThereCollision(double timeStep);
		virtual void begin();
		virtual void end();

		friend Area;

	protected:

	};

	class Impact : public Collision
	{
	public:
		Impact() = delete;
		Impact(Body& bodyA, Body& bodyB);
		~Impact() = default;

		virtual bool isThereCollision(double timeStep);
		virtual void begin();
		virtual void end();
		virtual void solve(bool preSolve = false);

		friend Area;

	protected:
		std::array<Vec2i, 2> line{};
	};

}
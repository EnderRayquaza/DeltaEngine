#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Body.hpp"
#include "World.hpp"

namespace DeltaEngine
{
	class Body;
	class ShapeManager;

	class Sensor;
	class Collision;
	class Contact;
	class Impact;

	class Sensor : public Identifiable
	{
	public:
		Sensor() = delete;
		Sensor(Vertex pos, Shape, std::function<void()> on, std::function<void()> off);
		~Sensor() = default;

		void set_pos(Vertex pos) noexcept;

		bool verifySense(double timeStep);
		std::function<void()> exeFuncOn() const noexcept;
		std::function<void()> exeFuncOff() const noexcept;

		friend class Area;
	protected:
		Vertex m_pos;
		Shape const m_shape;
		std::vector<Body> m_bodies;

		bool m_on{ false };
		std::function<void()> const m_funcOn;
		std::function<void()> const m_funcOff;
	};

	class Collision : public Identifiable
	{
	public:
		Collision() = delete;
		Collision(Body& bodyA, Body& bodyB, ShapeManager&);
		~Collision() = default;

		virtual bool isThereCollision(double timeStep) = 0;
		virtual void begin() = 0;
		virtual void end() = 0;

		friend class Area;
	protected:
		Body& m_bodyA, & m_bodyB;
		ShapeManager& m_shapeMng;
	};

	class Contact : public Collision
	{
	public:
		Contact() = delete;
		Contact(Body& bodyA, Body& bodyB, ShapeManager&);
		~Contact() = default;

		virtual bool isThereCollision(double timeStep);
		virtual void begin();
		virtual void end();

		friend class Area;

	protected:

	};

	class Impact : public Collision
	{
	public:
		Impact() = delete;
		Impact(Body& bodyA, Body& bodyB, ShapeManager&);
		~Impact() = default;

		virtual bool isThereCollision(double timeStep);
		virtual void begin();
		virtual void end();
		virtual void solve(bool preSolve = false);

		friend class Area;

	protected:
		std::array<Vec2i, 2> line{};
	};

	bool pointInShape(Vertex point, Shape);

}
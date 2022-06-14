#pragma once
#include "../config.hpp"
#include "Body.hpp"
#include "Manager.hpp"
#include "Shape.hpp"
#include "ShapeSheet.hpp"

namespace DeltaEngine
{
	class Collision
	{
	public:
		Collision() = delete;
		Collision(Body&, Body&, Manager<ShapeSheet>&);
		~Collision() = default;

		virtual bool isThereCollision(double time)=0;
		virtual void begin() = 0;
		virtual void end() = 0;
		friend class Area;
		friend class Impact;

	protected:
		Body& m_bodyA, & m_bodyB;
		Manager<ShapeSheet>& m_shapeMng;
	};

	class Contact : public Collision
	{
	public:
		Contact() = delete;
		Contact(Body&, Body&, Manager<ShapeSheet>&);
		~Contact() = default;

		virtual bool isThereCollision(double time);
		virtual void begin();
		virtual void end();
		friend class Area;

	protected:
	};

	class Impact : public Collision
	{
	public:
		Impact() = delete;
		Impact(Collision&);
		Impact(Body&, Body&, Manager<ShapeSheet>&);
		~Impact() = default;

		virtual bool isThereCollision(double time);
		virtual void begin();
		virtual void end();
		virtual void solve(bool pre_solve = false);
		friend class Area;

	protected:
		std::array<Vec2i, 2> line{};
	};
}

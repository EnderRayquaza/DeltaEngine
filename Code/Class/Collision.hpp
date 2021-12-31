#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Body.hpp"

namespace DeltaEngine
{
	class Collision : public Identifiable
	{
	public:
		Collision() = delete;
		Collision(Body& bodyA, Body& bodyB);
		~Collision() = default;

		virtual bool isThereCollision() = 0;
		virtual void begin() = 0;
		virtual void end() = 0;
	protected:
		Body& m_bodyA, & m_bodyB;
	};

	class Contact : public Collision
	{
	public:
		virtual bool isThereCollision();

	protected:

	};

	class Impact : public Collision
	{
	public:
		virtual bool isThereCollision();

	protected:

	};

}
#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Body.hpp"

namespace DeltaEngine
{
	class Impact : public Identificable
	{
	public:
		Impact() = delete;
		Impact(Body& bodyA, Body& bodyB);
		~Impact() = default;

	protected:
		Body& m_bodyA, & m_bodyB;
	};

	class Contact : public Impact
	{
	public:

	protected:

	};

	class Collision : public Impact
	{
	public:

	protected:

	};

}
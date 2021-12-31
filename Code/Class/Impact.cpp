#include "Impact.hpp"

namespace DeltaEngine
{
	Impact::Impact(Body& bodyA, Body& bodyB):Identificable(), m_bodyA(bodyA), m_bodyB(bodyB)
	{}
}
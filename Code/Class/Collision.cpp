#include "Collision.hpp"

namespace DeltaEngine
{
	Collision::Collision(Body& bodyA, Body& bodyB):Identifiable(), m_bodyA(bodyA), m_bodyB(bodyB)
	{}

	bool Contact::isThereCollision()
	{
		//Do a lot of complex calculs...
		return false;
	}

	bool Impact::isThereCollision()
	{
		//Do more complex calculs...
		return false;
	}
}
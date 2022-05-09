#include "../Class_headers/Collision.hpp"

namespace DeltaEngine
{
	//Collision
	Collision::Collision(Body& bodyA, Body& bodyB, Manager<ShapeSheet>& ssm) :
		m_bodyA{ bodyA }, m_bodyB{ bodyB }, m_shapeMng{ ssm }
	{
		if (m_bodyA.m_displayScreen != m_bodyB.m_displayScreen)
			this->~Collision();
	}

	//Contact
	Contact::Contact(Body& bodyA, Body& bodyB, Manager<ShapeSheet>& ssm) : Collision(bodyA, bodyB, ssm)
	{}

	bool Contact::isThereCollision(double time)
	{
		AABB a{ m_shapeMng[m_bodyA.m_indexSSMng][m_bodyA.getCoordShape()].getAABB(m_bodyA.m_pos +
			(Vertex)m_bodyA.moveTest(time),	m_bodyA.m_angle) };
		AABB b{ m_shapeMng[m_bodyB.m_indexSSMng][m_bodyB.getCoordShape()].getAABB(m_bodyB.m_pos +
			(Vertex)m_bodyB.moveTest(time), m_bodyB.m_angle) };
		if (a.intersects(b))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void Contact::begin()
	{
		std::cout << "A Contact begins..." << std::endl;
	}

	void Contact::end()
	{
		std::cout << "A Contact ends..." << std::endl;
	}

	//Impact
	Impact::Impact(Body& bodyA, Body& bodyB, Manager<ShapeSheet>& ssm) : Collision(bodyA, bodyB, ssm)
	{}

	bool Impact::isThereCollision(double timeStep)
	{
		Vertex velA{ m_bodyA.moveTest(timeStep) }, velB{ m_bodyB.moveTest(timeStep) };
		Shape& const a{ m_shapeMng[m_bodyA.m_indexSSMng][m_bodyA.getCoordShape()] };
		Shape& const b{ m_shapeMng[m_bodyB.m_indexSSMng][m_bodyB.getCoordShape()] };

		for (auto& pt : b.getVertices(velB, m_bodyB.m_angle))
		{ //For all points of the shapeB
			if (pointInShape(pt, a.getVertices(velA, m_bodyA.m_angle)))
				return true;
		}
		return false; //If all points aren't in, the shapes aren't touching each other.
	}

	void Impact::begin()
	{
		std::cout << "An Impact begins..." << std::endl;
	}

	void Impact::end()
	{
		std::cout << "The Impact ends..." << std::endl;
	}

	void Impact::solve(bool preSolve)
	{
		double rAB{ -sqrt(pow(m_bodyB.m_velocity.x, 2) + pow(m_bodyB.m_velocity.y, 2)) }; //√x²+y²
		double rBA{ -sqrt(pow(m_bodyA.m_velocity.x, 2) + pow(m_bodyA.m_velocity.y, 2)) }; //Idem
		if (preSolve)
		{
			//If preSolving, the bodies haven't touched each other, so we reduce only the speed to avoid the body goes 
			//through the other.
			rAB /= 2;
			rBA /= 2;
		}
		Vec2f vecAB{ m_bodyA.m_pos - m_bodyB.m_pos }, vecBA{ -vecAB };
		Vec2f uAB{ vecAB / sqrt(pow(vecAB.x, 2) + pow(vecAB.y, 2)) }, uBA{ -uAB }; // AB / ||AB||
		Vec2f RAB{ rAB * vecAB }, RBA{ rBA * vecBA };
		if (m_bodyA.m_moveType == moveType::Dynamic)
		{
			m_bodyA.applyImpulse(RBA);
		}
		if (m_bodyB.m_moveType == moveType::Dynamic)
		{
			m_bodyB.applyImpulse(RAB);
		}

	}
}
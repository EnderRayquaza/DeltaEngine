#include "Collision.hpp"

namespace DeltaEngine
{
	Sensor::Sensor(Vertex pos, AABB aabb, std::function<void()> funcOn, std::function<void()> funcOff) :
		m_pos(pos), m_aabb(aabb), m_funcOn(funcOn), m_funcOff(funcOff)
	{}

	Collision::Collision(Body& bodyA, Body& bodyB):Identifiable(), m_bodyA(bodyA), m_bodyB(bodyB)
	{
		if (m_bodyA.m_displayScreen != m_bodyB.m_displayScreen)
			this->~Collision();
	}

	Contact::Contact(Body& bodyA, Body& bodyB): Collision(bodyA, bodyB)
	{}

	bool Contact::isThereCollision(double timeStep)
	{
		Vec2f velA{ m_bodyA.moveTest(timeStep) }, velB{ m_bodyB.moveTest(timeStep) };
		AABB a{ m_bodyA.get_shape().m_aabb }, b{ m_bodyB.get_shape().m_aabb };
		a.move((Vec2i)velA);
		b.move((Vec2i)velB);
		if (a.x >= b.x + b.w &&
			a.x + a.w <= b.x &&
			a.y >= b.y + b.h &&
			a.y + a.h <= b.y )
			return false;
		else
			return true;
	}

	void Contact::begin()
	{
		std::cout << "A Contact begins..." << std::endl;
	}

	void Contact::end()
	{
		std::cout << "The Contact ends..." << std::endl;
	}

	Impact::Impact(Body& bodyA, Body& bodyB) : Collision(bodyA, bodyB)
	{}

	bool Impact::isThereCollision(double timeStep)
	{
		Vec2f velA{ m_bodyA.moveTest(timeStep) }, velB{ m_bodyB.moveTest(timeStep) };
		Shape a{ m_bodyA.get_shape() }, b{ m_bodyB.get_shape() };

		a.move((Vec2i)velA);
		b.move((Vec2i)velB);

		for (auto& pt : b.m_vertices)
		{ //For all points of the shapeB
			if (pointInShape(pt, a))
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
		Vec2f vecAB{ m_bodyA.m_position - m_bodyB.m_position }, vecBA{ -vecAB };
		Vec2f uAB{ vecAB / -sqrt(pow(vecAB.x, 2) + pow(vecAB.y, 2)) }, uBA{ -uAB }; // AB / ||AB||
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

	bool pointInShape(Vertex pt, Shape shape)
	{
		for (size_t i{ 0 }; i < shape.m_vertices.size(); i++)
		{ //For all points of the shapeA
			Vertex vtx, vtx1;
			if (i + 1 < shape.m_vertices.size())
				vtx = shape.m_vertices[i], vtx1 = shape.m_vertices[i + 1];
			else
				vtx = shape.m_vertices[i], vtx1 = shape.m_vertices[0];
			Vec2f aa{ vtx1.x - vtx.x, vtx1.y - vtx.y }, ab{ pt.x - vtx.x, pt.y - vtx.y }; //Calculs the vector vtx;vtx+1 and vtx;pt.
			double det{ aa.x - ab.y * aa.y - ab.x }; //Calculs their determinant.
			if (det >= 0) //Verifies the sign of the determinant
			{
				return true;
			}
		}
		return false;
	}
}
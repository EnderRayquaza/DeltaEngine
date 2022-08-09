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
		if (m_bodyA.m_displayScreen != m_bodyB.m_displayScreen)
		{
			return false;
		}
		if (*std::find(m_bodyB.m_collisionTarget.begin(), m_bodyB.m_collisionTarget.end() - 1,
			m_bodyA.m_collisionType) == m_bodyA.m_collisionType)
		{
			//std::cout << "Contact begins..." << std::endl << "bodyB -> " << m_bodyB._id.intKey1 << std::endl;;
			AABB a{ m_shapeMng[m_bodyA.m_indexSSMng][m_bodyA.getCoordShape()].getAABB(m_bodyA.m_pos +
				(Vertex)m_bodyA.moveTest(time), m_bodyA.get_center(true), m_bodyA.m_angle) };
			//std::cout << "AABB a ok" << std::endl;
			AABB b{ m_shapeMng[m_bodyB.m_indexSSMng][m_bodyB.getCoordShape()].getAABB(m_bodyB.m_pos +
				(Vertex)m_bodyB.moveTest(time), m_bodyA.get_center(true), m_bodyB.m_angle) };
			//std::cout << "AABB b ok" << std::endl;
			if (a.intersects(b))
			{
				/*std::cout << "a : " << a.left << "/" << a.top << "<>" << a.width << "/" << a.height << std::endl;
				std::cout << "b : " << b.left << "/" << b.top << "<>" << b.width << "/" << b.height << std::endl;*/
				//std::cout << "Contact here !" << std::endl;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			//std::cout << "not compatible" << std::endl;
			return false;
		}
	}

	//Impact
	Impact::Impact(Collision& c):Impact(c.m_bodyA, c.m_bodyB, c.m_shapeMng)
	{}

	Impact::Impact(Body& bodyA, Body& bodyB, Manager<ShapeSheet>& ssm) : Collision(bodyA, bodyB, ssm)
	{}

	bool Impact::isThereCollision(double timeStep)
	{
		Vertex velA{ m_bodyA.moveTest(timeStep) }, velB{ m_bodyB.moveTest(timeStep) };
		Shape& a{ m_shapeMng[m_bodyA.m_indexSSMng][m_bodyA.getCoordShape()] };
		Shape& b{ m_shapeMng[m_bodyB.m_indexSSMng][m_bodyB.getCoordShape()] };


		for (auto& pt : a.getVertices(m_bodyA.m_pos + velA, m_bodyA.get_center(true), m_bodyA.m_angle))
		{ //For all points of the shapeB
			if (pointInShape(pt, b.getVertices(m_bodyB.m_pos + velB, m_bodyB.get_center(true), m_bodyB.m_angle)))
			{
				return true;
			}
		}
		return false; //If all points aren't in, the shapes aren't touching each other.
	}

	void Impact::solve(bool preSolve)
	{
		//Finds the unit vector for repulsion.
		Shape& a{ m_shapeMng[m_bodyA.m_indexSSMng][m_bodyA.getCoordShape()] };
		Shape& b{ m_shapeMng[m_bodyB.m_indexSSMng][m_bodyB.getCoordShape()] };

		Vec2f vCenter{ m_bodyB.get_center() - m_bodyA.get_center()}; //Gets the vector between the two centers.
		Vec2f vSide{ whichSideCutted(b, m_bodyB.m_pos, m_bodyB.m_angle, m_bodyB.get_center(), m_bodyA.get_center())}; //Gets the side of the Shapde cutted by vCenter.
		float x{ vSide.x }, y{ vSide.y };
		if (x != 0 || y != 0)
		{
			Vec2f n{y , x}, unit{}; //Calculs the normal vector of vSide
			if (det(vSide, vCenter) / abs(det(vSide, vCenter)) == det(vSide, n) / abs(det(vSide, n)))
			{//Verfies if n is in the same direction then vCenter
				unit = Vec2f{ -n / sqrt(n.x * n.x + n.y * n.y) };
			}
			else
			{
				unit = Vec2f{ n / sqrt(n.x * n.x + n.y * n.y) };
			}

			//Calculates the force of repulsion.
			double rAB{ sqrt(pow(m_bodyA.m_velocity.x*unit.x, 2) + pow(m_bodyA.m_velocity.y*unit.y, 2)) }; //√x²+y²
			if (preSolve)
			{
				//If preSolving, the bodies haven't touched each other, so we reduce only the speed to avoid the body goes 
				//through the other.
				rAB /= 2;
			}


			//Applies the repulsion.
			Vec2f vR_AB{ unit * rAB };
			if (m_bodyA.m_moveType == moveType::Dynamic)
			{
				m_bodyA.applyImpulse(vR_AB);
			}
			if (m_bodyB.m_moveType == moveType::Dynamic)
			{
				m_bodyB.applyImpulse(-vR_AB);
			}
		}
		else
		{
			std::cerr << "echec of solving..." << std::endl;
		}
		std::cout << std::endl;
	}
}
#include "../Class_headers/Area.hpp"

namespace DeltaEngine
{
	Area::Area(Manager<Body>& mngB, Manager<ShapeSheet>& mngSS) :m_mngBody{ mngB }, m_mngSS{ mngSS } //, m_box{ box }
	{}

	void Area::step(double time)
	{
		std::vector<Contact> vContact{};
		for (size_t i{ 0 }; i < m_bodyId.size(); i++)
		{
			//std::cout << "Step're here !" << std::endl;
			Body& bodyA{ m_mngBody[m_bodyId[i]]};
			for (size_t j{ 0 }; j < m_bodyId.size(); j++)
			{
				if (i == j or bodyA._id.intKey1 == 41)
				{
					continue;
				}
				//std::cout << "bodyA : " << bodyA._id.intKey1 << std::endl;
				Body& bodyB{ m_mngBody[m_bodyId[j]] };

				Contact c{bodyA, bodyB, m_mngSS};
				if (c.isThereCollision(time))
				{
					//std::cout << "+1 contact" << std::endl;
					vContact.push_back(c);
				}
				else
				{
					c.~Contact();
				}

			}
		}
		for (auto& c : vContact)
		{
			Impact i{ c };
			if (i.isThereCollision(time))
			{
				//i.solve(time > 0);
			}
		}
	}

	bool Area::addBody(Id id)
	{
		if (inManager(m_mngBody, id))
		{
			m_bodyId.push_back(id);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Area::removeBody(Id id)
	{
		if (inVector(m_bodyId, id))
		{
			eraseElem(m_bodyId, id);
			return true;
		}
		else
		{
			return false;
		}
	}
}
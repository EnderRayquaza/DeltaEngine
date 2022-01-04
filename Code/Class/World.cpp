#include "World.hpp"

namespace DeltaEngine
{
	Area::Area(std::vector<Body> bodies):m_bodies{bodies}
	{}

	void Area::add_body(Body& body) noexcept
	{
		m_bodies.push_back(body);
	}

	void Area::remove_body(Body& const body)
	{
		remove_body(body.m_id);
	}

	void Area::remove_body(Id const id)
	{
		int idx2remove{ -1 };
		for (size_t i{ 0 }; i < m_bodies.size(); i++)
		{
			if (m_bodies[i].m_id == id)
			{
				idx2remove = i;
				break;
			}
		}
		if (idx2remove != -1 && m_bodies.begin() + idx2remove != m_bodies.end())
		{
			m_bodies.erase(m_bodies.begin() + idx2remove);
		}
	}

	void Area::step(double timeStep)
	{
		verifyContacts(0);
		verifyImpacts(0);
		for (auto& impact : m_impacts)
		{
			impact.solve();
		}
		verifyContacts(timeStep);
		verifyImpacts(timeStep);
		for (auto& impact : m_impacts)
		{
			impact.solve(true);
		}
		for (auto& body : m_bodies)
		{
			body.move(timeStep);
		}

		
	}

	void Area::verifyContacts(double timeStep)
	{
		for (size_t i{ 0 }; i < m_contacts.size(); i++)
		{ //For all contacts
			if (!m_contacts[i].isThereCollision(timeStep))
			{ //If they're no longer active...
				m_contacts[i].end(); //It ends it,
				auto elem = m_contacts.begin() + i; //Finds it,
				if (elem != m_contacts.end())
					m_contacts.erase(elem); //And deletes it.
			}
		}
		for (auto& bodyA : m_bodies)
		{
			for (auto& bodyB : m_bodies)
			{
				if ((bodyA.m_displayScreen == bodyB.m_displayScreen) && verifyTargeting(bodyA, bodyB))
				{//If they're on the same displayScreen
					Contact c(bodyA, bodyB); //It creates a contact between everybody
					if (!c.isThereCollision(timeStep) || contactAlreadyIn(c))
					{
						c.~Contact(); //If there's no contact, it destroys it.
						continue;
					}
					else
					{
						c.begin(); //Else it begins
						m_contacts.push_back(c); //And adds to the vector.
					}
				}
			}
		}
	}

	void Area::verifyImpacts(double timeStep)
	{
		for (size_t i{ 0 }; i < m_impacts.size(); i++)
		{ //For all impacts
			if (!m_impacts[i].isThereCollision(timeStep))
			{ //If they're no longer active...
				m_impacts[i].end(); //It ends it,
				auto elem = m_impacts.begin() + i; //Finds it,
				if (elem != m_impacts.end())
					m_impacts.erase(elem); //And deletes it.
			}
		}
		for (auto& c : m_contacts)
		{
			Impact im(c.m_bodyA, c.m_bodyB); //It creates a impact between every bodies which are in contact.
			if (!im.isThereCollision(timeStep) || impactAlreadyIn(im))
			{
				im.~Impact(); //If there's no impact, it destroys it.
				continue;
			}
			else
			{
				im.begin(); //Else it begins
				m_impacts.push_back(im); //And adds to the vector.
			}
		}
	}

	bool Area::contactAlreadyIn(const Contact& contact) const
	{
		for (auto& c : m_contacts)
		{
			if (c.m_id == contact.m_id)
				return true;
		}
		return false;
	}

	bool Area::impactAlreadyIn(const Impact& impact) const
	{
		for (auto& i : m_contacts)
		{
			if (i.m_id == impact.m_id)
				return true;
		}
		return false;
	}
}
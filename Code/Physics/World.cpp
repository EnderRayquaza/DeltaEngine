#include "World.hpp"

namespace DeltaEngine
{
	Area::Area(bool enable, std::vector<Body> bodies):m_enable(enable), m_bodies(bodies)
	{}

	bool Area::get_enable() const
	{
		return m_enable;
	}

	void Area::set_enable(bool enable)
	{
		m_enable = enable;
	}

	void Area::add_body(Body& body)
	{
		m_bodies.push_back(body);
	}

	void Area::step(double timeStep)
	{
		for (auto& body : m_bodies)
		{
			body.move(timeStep);
		}
		verifyContacts();
		verifyCollisions();
		for (auto& collision : m_collisions)
		{
			collision.execute();
		}
	}

	void Area::verifyContacts()
	{
		for (size_t i{0};i<m_contacts.size();i++)
		{
			if (!m_contacts[i].isThereContact())
			{
				m_contacts[i].end();
				auto elem = m_contacts.begin() + i;
				if(elem != m_contacts.end())
					m_contacts.erase(elem);
			}
		}
		for (auto& bodyA : m_bodies)
		{
			for (auto& bodyB : m_bodies)
			{
				Contact c(bodyA, bodyB);
				if (!c.isThereContact() || contactAlreadyIn(c))
				{
					c.~Contact();
					continue;
				}
				else
				{
					c.begin();
					m_contacts.push_back(c);
				}
			}
		}
	}

	void Area::verifyCollisions()
	{
		for (size_t i{ 0 }; i < m_collisions.size(); i++)
		{
			if (!m_collisions[i].isThereCollision())
			{
				m_collisions[i].end();
				auto elem = m_collisions.begin() + i;
				if (elem != m_collisions.end())
					m_collisions.erase(elem);
			}
		}
		for (auto& contact : m_contacts)
		{
			Collision c(contact);
			if (!c.isThereCollision() || collisionAlreadyIn(c))
			{
				c.~Collision();
				continue;
			}
			else
			{
				c.begin();
				m_collisions.push_back(c);
			}
		}
	}

	bool Area::contactAlreadyIn(const Contact& contact) const
	{
		for (auto& c : m_contacts)
		{
			if (c.get_id() == contact.get_id())
				return true;
		}
		return false;
	}

	bool Area::collisionAlreadyIn(const Collision& collision) const
	{
		for (auto& c : m_collisions)
		{
			if (c.get_id() == collision.get_id())
				return true;
		}
		return false;
	}
}
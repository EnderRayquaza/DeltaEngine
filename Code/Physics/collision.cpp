#include "collision.hpp"

namespace DeltaEngine
{
	//Operators
	bool operator==(const Contact& c1, const Contact& c2)
	{
		return c1.isEgal(c2);
	}

	bool operator==(const Collision& c1, const Collision& c2)
	{
		return c1.isEgal(c2);
	}

	//Contacts
	Contact::Contact(Body* bodyA, Body* bodyB):m_bodyA(bodyA), m_bodyB(bodyB)
	{
		do
		{
			m_id = std::rand();
		} while (*std::find(listId.begin(), listId.end(), m_id) == m_id);
		listId.push_back(m_id);
	}


	int Contact::get_id() const
	{
		return m_id;
	}

	Body* Contact::get_bodyA() const 
	{
		return m_bodyA;
	}

	Body* Contact::get_bodyB() const
	{
		return m_bodyB;
	}


	bool Contact::isThereContact()
	{

	}

	void Contact::begin()
	{
		std::cout << "A contact begins !" << std::endl;
	}

	void Contact::end()
	{
		std::cout << "The contact ends..." << std::endl;
	}

	bool Contact::isEgal(const Contact& c) const 
	{
		return (m_bodyA->m_id == c.m_bodyA->m_id && m_bodyB->m_id == c.m_bodyB->m_id);
	}


	//Collisions
	Collision::Collision(Body* bodyA, Body* bodyB) :m_bodyA(bodyA), m_bodyB(bodyB)
	{
		do
		{
			m_id = std::rand();
		} while (*std::find(listId.begin(), listId.end(), m_id) == m_id);
		listId.push_back(m_id);
	}

	Collision::Collision(Contact& contact):m_bodyA(contact.get_bodyA()), m_bodyB(contact.get_bodyB())
	{
		do
		{
			m_id = std::rand();
		} while (*std::find(listId.begin(), listId.end(), m_id) == m_id);
		listId.push_back(m_id);
	}


	int Collision::get_id() const
	{
		return m_id;
	}

	Body* Collision::get_bodyA() const
	{
		return m_bodyA;
	}

	Body* Collision::get_bodyB() const
	{
		return m_bodyB;
	}


	bool Collision::isThereCollision()
	{

	}

	void Collision::execute()
	{
		std::cout << "Calculs in progress..." << std::endl;
	}

	void Collision::begin()
	{
		std::cout << "A Collision begins !" << std::endl;
	}

	void Collision::end()
	{
		std::cout << "The Collision ends..." << std::endl;
	}

	bool Collision::isEgal(const Collision& c) const
	{
		return (m_bodyA->m_id == c.m_bodyA->m_id && m_bodyB->m_id == c.m_bodyB->m_id);
	}
}
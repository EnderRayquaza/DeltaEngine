#include "../Class_headers/Area.hpp"

namespace DeltaEngine
{
	Area::Area(Manager<Body>& mng, sf::IntRect box) :m_mngBody{ mng }, m_box{ box }
	{}

	void Area::step(double time)
	{
		//Physic "step()"
		//Will be coded in the part II
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
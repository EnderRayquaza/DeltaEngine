#pragma once

#include "../config.hpp"
#include "Body.hpp"
#include "Identifiable.hpp"
#include "Manager.hpp"

namespace DeltaEngine
{
	class Area
	{
	public:
		Area() = delete;
		Area(Manager<Body>&, sf::IntRect box);
		~Area() = default;

		void step(double time);

		bool addBody(Id);
		bool removeBody(Id);

	protected:
		Manager<Body>& m_mngBody; //The manager of all the bodies in the Game.
		std::vector<Id> m_bodyId{}; //A list of all the body who're in the Area.
		sf::IntRect m_box; //The box which define the edge of the Area.
	};
}
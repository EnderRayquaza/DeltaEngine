#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Body.hpp"
#include "Collision.hpp"
#include "Fluid.hpp"

namespace DeltaEngine
{
	class Area : public Identifiable
	{
	public:
		Area() = default;
		Area(std::vector<Body> bodies);
		~Area() = default;

		void add_body(Body& const) noexcept;
		void remove_body(Body& const);
		void remove_body(Id const);
		void step(double timeStep);
		void verifySensor(double timeStep);
		void verifyContacts(double timeStep);
		void verifyImpacts(double timeStep);
		bool contactAlreadyIn(const Contact&) const;
		bool impactAlreadyIn(const Impact&) const;

		bool _enable{ false };

	protected:
		std::vector<Body> m_bodies;
		std::vector<Sensor> m_sensors;
		std::vector<Contact> m_contacts;
		std::vector<Impact> m_impacts;
		std::vector<Fluid> m_fluids;
	};
		
	typedef std::vector<Area> World;
}
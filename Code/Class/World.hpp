#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Body.hpp"
#include "Collision.hpp"

namespace DeltaEngine
{
	class Area : public Identifiable
	{
	public:
		void set_enable(bool) noexcept;
		void add_body(Body&);

		void step(double timeStep);
		void verifyContacts();
		void verifyCollisions();
		bool contactAlreadyIn(const Contact&) const;
		bool impactAlreadyIn(const Impact&) const;

	protected:
		bool m_enable;
		std::vector<Body> m_bodies;
		std::vector<Contact> m_contacts;
		std::vector<Impact> m_impacts;
	};

	struct World
	{
		std::vector<Area> m_vArea;
	};
}
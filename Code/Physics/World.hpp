#pragma once

#include "../DeltaEngine.hpp"

namespace DeltaEngine
{
	struct World;
	class Area;

	struct World
	{
		World() = default;
		~World() = default;
		std::vector<Area> areas;
	};

	class Area
	{
	public:
		Area(bool enable = false, std::vector<Body> bodies = {});
		~Area() = default;

		bool get_enable() const noexcept;

		void set_enable(bool) noexcept;
		void add_body(Body&);

		void step(double timeStep);
		void verifyContacts();
		void verifyCollisions();
		bool contactAlreadyIn(const Contact&) const;
		bool collisionAlreadyIn(const Collision&) const;

	protected:
		bool m_enable;
		std::vector<Body> m_bodies;
		std::vector<Contact> m_contacts;
		std::vector<Collision> m_collisions;
	};
}


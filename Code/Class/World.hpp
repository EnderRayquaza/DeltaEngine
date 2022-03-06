#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Body.hpp"
#include "Collision.hpp"
#include "Fluid.hpp"

namespace DeltaEngine
{
	class Fluid;
	class Sensor;

	class Area : public Identifiable
	{
	public:
		Area() = default;
		Area(std::vector<Body> bodies, std::vector<Fluid> fluids, std::vector<Sensor> sensors,
			ShapeManager& shapeMng);
		~Area() = default;

		void add_body(Body& const) noexcept;
		void remove_body(Body& const);
		void remove_body(Id const);

		void add_fluid(Fluid& const) noexcept;
		void remove_fluid(Fluid& const);
		void remove_fluid(Id const);

		void add_sensor(Sensor& const) noexcept;
		void remove_sensor(Sensor& const);
		void remove_sensor(Id const);

		void step(double timeStep);

		void verifySensor(double timeStep);
		void verifyContacts(double timeStep);
		void verifyImpacts(double timeStep);
		bool contactAlreadyIn(const Contact&) const;
		bool impactAlreadyIn(const Impact&) const;

		bool _enable{ false };

	protected:
		std::vector<Body> m_bodies;
		std::vector<Fluid> m_fluids;
		std::vector<Sensor> m_sensors;

		ShapeManager& m_shapeMng;

		std::vector<Contact> m_contacts;
		std::vector<Impact> m_impacts;
	};
		
	typedef std::vector<Area> World;
}
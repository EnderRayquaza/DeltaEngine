#pragma once

#include "../config.hpp"
#include "../basic.hpp"

namespace DeltaEngine
{
	class Body : public Identifiable
	{
	public:
		Body() = delete;
		Body(std::string jsonPath);
		Body(Shape shape, AABB aabb, double density = 1, double friction = 0, double restituion = 0,
			Vertex position = {0, 0}, double angle = 0);
		~Body() = default;

		void set_position(Vertex position) noexcept;
		void set_angle(double angle) noexcept;

		void move(double time);
		void rotate(double angle) noexcept;
		void applyForce(Vec2f force) noexcept;
		void applyImpulse(Vec2f impulse) noexcept;
		void resetForce() noexcept;
		void resetImpulse() noexcept;

		bool _enable;

	protected:
		Vertex m_position;
		double m_angle;
		Shape m_shape;
		AABB m_aabb;
		double m_mass, m_density, m_friction, m_restitution;
		Vec2f m_force{0, 0}, m_impulse{0, 0}, m_velocity{0, 0};
	};
}
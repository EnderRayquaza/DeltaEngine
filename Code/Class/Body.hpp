#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Animation.hpp"

namespace DeltaEngine
{
	class Body : public Identifiable
	{
	public:
		Body() = delete;
		Body(std::string jsonPath);
		Body(Vec2i state, moveType, collisionType, collisionTargets, int displayScreen, double density = 1, 
			double friction = 0, double restituion = 0, Vertex position = {0, 0}, double angle = 0);
		~Body() = default;

		Shape& get_shape() const noexcept;
		sf::IntRect get_textureRect() const noexcept;

		void set_position(Vertex position) noexcept;
		void set_angle(double angle) noexcept;

		void move(double timeStep);
		void rotate(double angle) noexcept;
		void applyForce(Vec2f force) noexcept;
		void applyImpulse(Vec2f impulse) noexcept;
		void resetForce() noexcept;
		void resetImpulse() noexcept;
		void playAnimation(uint index, bool force) noexcept;
		Vec2f moveTest(double timeStep);
		bool verifyTargeting(Body&);

		bool _enable;

		friend class Game;
		friend Area;
		friend Collision;
		friend Contact;
		friend Impact;

	protected:
		Vertex m_position;
		Vertex m_center;
		double m_angle;
		uint m_smIndex, m_tmIndex; //ShapeManager - TextureManager
		vec_uint m_animationsPlayList;
		Vec2i m_state, m_size; //For Shapesheet/Textures
		std::vector<Animation> m_animations;
		double m_mass, m_density, m_friction, m_restitution;
		Vec2f m_force{0, 0}, m_impulse{0, 0}, m_velocity{0, 0};
		int m_displayScreen;
		moveType m_moveType;
		collisionType m_collisionType;
		collisionTargets m_collisionTargets;
	};

	bool verifyTargeting(Body& bA, Body& bB);
}
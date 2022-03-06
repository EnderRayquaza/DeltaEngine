#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Animation.hpp"
#include "Game.hpp"
#include "Manager.hpp"

namespace DeltaEngine
{
	class ShapeManager;

	class Body : public Identifiable
	{
	public:
		Body() = delete;
		Body(jsonStr jsonPath);
		Body(Vertex position, Vertex center, double angle, uint displayScreen, //Basics
			uint shapeManagerIndex, uint textureManagerIndex, Vec2i startState, Vec2i texSize, 
			std::vector<Animation> animations, //Render
			ulong mass, ulong density, ulong friction, ulong restitution, moveType, collisionType,
			collisionTargets); //Physics
		//Body(const Body&);
		~Body() = default;

		Shape& const get_shape(ShapeManager& aeugh) const;
		sf::IntRect get_textureRect() const noexcept;

		//Basic
		void set_position(Vertex position) noexcept;
		void set_angle(double angle) noexcept;
		void load();

		//Render
		void playAnimation(uint index, bool force) noexcept;
		void setState(Vec2i state) noexcept;

		//Physic
		void move(double timeStep);
		void rotate(double angle) noexcept;
		void applyForce(Vec2f force) noexcept;
		void applyImpulse(Vec2f impulse) noexcept;
		void resetForce() noexcept;
		void resetImpulse() noexcept;
		Vec2f moveTest(double timeStep);
		bool verifyTargeting(Body&);

		bool _enable;

		friend class Game;
		friend class Fluid;
		friend class Area;
		friend class Collision;
		friend class Contact;
		friend class Impact;

	protected:
		//Basic members
		jsonStr m_jsonStr;
		Vertex m_position;
		Vertex m_center;
		double m_angle;
		uint m_displayScreen;

		//Render members
		uint m_smIndex, m_tmIndex; //ShapeManager - TextureManager
		Vec2i m_state, m_texSize; //For Shapesheet/Textures
		vec_uint m_animationsPlayList{};
		std::vector<Animation> m_animations;

		//Physics members
		ulong m_mass, m_density, m_friction, m_restitution;
		Vec2f m_force{0, 0}, m_impulse{0, 0}, m_velocity{0, 0};
		moveType m_moveType;
		collisionType m_collisionType;
		collisionTargets m_collisionTargets;
	};

	bool verifyTargeting(Body& lhs, Body& rhs);
}
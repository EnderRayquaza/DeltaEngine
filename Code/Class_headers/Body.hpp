#pragma once

#include "../config.hpp"
#include "Animation.hpp"
#include "Collision.hpp"
#include "func.hpp"
#include "Identifiable.hpp"
#include "Loadable.hpp"

namespace DeltaEngine
{
	class Body : public Identifiable, public Loadable
	{
	public:
		Body();
		Body(jsonStr);
		~Body() = default;

		///Accessors.
		void set_pos(Vertex position);
		void set_angle(double angle, bool inRad = true);
		void set_displayScreen(uint ds);

		///Basic func.
		bool load(); //Load the stats of the body by a file. Return the success.
		void move(float time); //Move the body with its velocity and its forces/impulses.
		void rotate(int angle, bool inRad = true); //Rotate the body (in the anti-clockwise).

		///Render func.
		Vec2i getCoordShape();
		void playAnimationSS(uint index, bool force = false); //Add an animation to the playlist.
		void nextAnimationSS(); //Switch to the next animation in the playlist.
		void nextFrameSS(); //Switch to the next frame.
		Vec2i getCoordTex();
		void playAnimationTex(uint index, bool force = false); //Add an animation to the playlist.
		void nextAnimationTex(); //Switch to the next animation in the playlist.
		void nextFrameTex(); //Switch to the next frame.

		///Physic func.
		Vec2f moveTest(float time) const; //Return the future velocity without modifying the body stats.
		void applyForce(Vec2f force); //Apply a force to the body.
		void applyImpulse(Vec2f impulse); //Apply an impulse to the body.
		void resetForce(); //Delete all the forces applied to the body.
		void resetImpulse(); //Delete all the impulses before they are applied.

		friend class Game;

	protected:
		///Basic Members
		Vertex m_pos{}; //The position of the body (in px).
		Vertex /*Not sure about useness.*/ m_center{}; //The center of the body.
		double m_angle{ 0 }; //The angle of the body (in rad).
		uint m_displayScreen{ 0 }; //The DS where the body is.

		///Render Members
		uint m_indexSSMng{ 0 }, m_indexTexMng{ 0 }; //The index of the body for the Managers.
		//Vec2i m_posFrameSS{}, m_posFrameTex{}; //(PM) The Position of the frame in the Manager;
		vec_uint m_animationPlayListSS{}, m_animationPlayListTex{}; //(pl)The list with the odrer of the animations.
		std::vector<Animation> m_vAnimationSS{}, m_vAnimationTex{}; //(vA) The containers of all Animation of the Body.
		uint m_frameSS{ 0 }, m_frameTex{ 0 }; //(AF) The current Frame of the Animation.
		uint m_defaultFrameSS{}, m_defaultFrameTex{}; //(DefF) The DEFault Frame displayed (index of vA).

		///Physic Members
		ulong m_mass{ 0 }, m_density{ 0 }, m_friction{ 0 }, m_restitution{ 0 }; //For speed moving, evolution in fluids, tailback or bouncing.
		Vec2f m_force{ 0, 0 }, m_impulse{ 0, 0 }, m_velocity{ 0, 0 }; //Forces stay after implementation, impulses disappear. Both increase the velocity of the body.
		moveType m_moveType{ moveType::Static }; //Define if the body can move, and how it can.
		collisionType m_collisionType{ collisionType::Nothing }; //To define which collides with it.
		collisionTargets m_collisionTarget{}; //To define with which it collides.
	};
}
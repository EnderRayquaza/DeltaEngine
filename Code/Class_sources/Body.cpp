#include "../Class_headers/Body.hpp"

namespace DeltaEngine
{
	Body::Body(jsonStr path):Loadable(path)
	{}

	///Accessors.
	void Body::set_pos(Vertex pos)
	{
		m_pos = pos;
	}

	void Body::set_angle(double angle, bool inRad)
	{
		if (inRad)
		{
			m_angle = angle;
		}
		else
		{
			m_angle = angle * DEG2RAD;
		}
	}

	void Body::set_displayScreen(uint ds)
	{
		m_displayScreen = ds;
	}

	///Basic func.
	bool Body::load()
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TODO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		return false;
	}

	void Body::move(float time)
	{
		Vec2f totalForces{ m_force + m_impulse }, acc{}; //It calculs the total of all the forces (and impulses) applied.
		resetImpulse(); //Impulses are deleted.
		//ΣF = ma <=> a = ΣF/m
		acc = Vec2f{ totalForces.x / m_mass, totalForces.y / m_mass };
		//a = dv/dt <=> v = a*t + v0
		m_velocity += Vec2f{ acc.x * time, acc.y * time };
		m_pos += Vec2i{ m_velocity };
	}

	void Body::rotate(int angle, bool inRad)
	{
		if (inRad)
		{
			m_angle += angle;
		}
		else
		{
			m_angle += angle * DEG2RAD;
		}
	}

	///Render func.
	void Body::playAnimationSS(uint index, bool force)
	{
		if(force)
		{
			m_animationPlayListSS.clear(); //Delete all animations which had to be played.
		}
		m_animationPlayListSS.push_back(index); //Add the animation at the end of the playlist.
	}

	void Body::nextAnimationSS()
	{
		m_animationPlayListSS.erase(m_animationPlayListSS.begin()); //Delete the first element.
	}

	void Body::nextFrameSS()
	{
		m_frameSS++;
	}

	void Body::playAnimationTex(uint index, bool force)
	{
		if (force)
		{
			m_animationPlayListTex.clear(); //Delete all animations which had to be played.
		}
		m_animationPlayListTex.push_back(index); //Add the animation at the end of the playlist.
	}

	void Body::nextAnimationTex()
	{
		m_animationPlayListTex.erase(m_animationPlayListTex.begin()); //Delete the first element.
	}

	void Body::nextFrameTex()
	{
		m_frameTex++;
	}

	///Physic func.
	Vec2f Body::moveTest(float time) const
	{
		Vec2f totalForces{ m_force + m_impulse }, acc{}; //It calculs the total of all the forces (and impulses) applied.
		//ΣF = ma <=> a = ΣF/m
		acc = Vec2f{ totalForces.x / m_mass, totalForces.y / m_mass };
		//a = dv/dt <=> v = a*t + v0
		return Vec2f{ acc.x * time, acc.y * time };// return the velocity.
	}

	void Body::applyForce(Vec2f force)
	{
		m_force += force;
	}

	void Body::applyImpulse(Vec2f impulse)
	{
		m_impulse += impulse;
	}

	void Body::resetForce()
	{
		m_force = Vec2f{ 0, 0 };
	}

	void Body::resetImpulse()
	{
		m_impulse = Vec2f{ 0, 0 };
	}
}
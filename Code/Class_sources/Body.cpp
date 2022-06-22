#include "../Class_headers/Body.hpp"

namespace DeltaEngine
{
	Body::Body() :Identifiable()
	{}

	Body::Body(jsonStr path) : Identifiable(), Loadable(path)
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
		json j{ returnJson(_path) };

		//Basic members
		m_pos = Vertex{ (int)j["pos"][0], (int)j["pos"][1] };
		m_center = Vertex{ (int)j["center"][0], (int)j["center"][1] };
		m_angle = (double)j["angle"];
		m_displayScreen = (uint)j["displayScreen"];

		//Render members
		m_indexSSMng = (uint)j["indexSSMng"];
		m_indexTexMng = (uint)j["indexTexMng"];
		jsonStr jStr{ j["animationSS"] };
		json jSS{ returnJson("json/body1/animSS.json")};
		for (auto& js : jSS)
		{
			m_vAnimationSS.push_back(Animation(js));
			m_vAnimationSS.back().loadByJson();
		}
		json jTex{ returnJson(j["animationTex"]) };
		for (auto& js : jTex)
		{
			m_vAnimationTex.push_back(Animation(js));
			m_vAnimationTex.back().loadByJson();
		}
		m_defAnimSS = j["defAnimSS"];
		m_defAnimTex = j["defAnimTex"];

		//Physics members
		m_mass = (ulong)j["mass"];
		m_density = (ulong)j["density"];
		m_friction = (ulong)j["friction"];
		m_restitution = (ulong)j["restitution"];
		m_moveType = (moveType)(int)j["moveType"];
		m_collisionType = (collisionType)(int)j["collisionType"];
		for (auto& cT : j["collisionTarget"])
		{
			m_collisionTarget.push_back((collisionType)(int)cT);
		}

		playAnimationSS(0);
		playAnimationTex(0);

		return false;
	}

	void Body::move(float time)
	{
		Vec2f totalForces{ m_force + m_impulse }, acc{}; //It calculs the total of all the forces (and impulses) applied.
		resetImpulse(); //Impulses are deleted.
		//ΣF = ma <=> a = ΣF/m
		if (m_mass != 0)
			acc = totalForces / m_mass;
		else
			acc = totalForces;
		//a = dv/dt <=> v = a*t + v0
		m_velocity += acc * time;
		if (acc.x != 0 or acc.y != 0)
		{
			std::cout << "acc : " << acc.x << "/" << acc.y << std::endl;
			std::cout << "vel : " << m_velocity.x << "/" << m_velocity.y << std::endl << std::endl;
		}
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
	Vec2i Body::getCoordShape()
	{
		verifPlaylistEmptySS();
		return  m_vAnimationSS[m_animationPlayListSS[0]]._vCoord[m_frameSS];
	}

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
		if (m_animationPlayListSS.size() == 0)
		{
			m_animationPlayListSS.push_back(m_defAnimSS);
		}
	}

	void Body::nextFrameSS()
	{
		verifPlaylistEmptySS();
		if (m_clockAnimSS.getElapsedTime() >= m_vAnimationSS[m_animationPlayListSS[0]]._time)
		{
			m_clockAnimSS.restart();
			m_frameSS++; //Increases the frame to go to the next one. 
			if (m_frameSS >= m_vAnimationSS[m_animationPlayListSS[0]].size()) //If it reaches the end of the animation...
			{
				m_frameSS = 0; //... it resets the counter.
				nextAnimationSS();//... and switches to the next animation ...
			}
		}
	}

	void Body::verifPlaylistEmptySS()
	{
		if (m_animationPlayListSS.empty())
		{
			playAnimationSS(m_defAnimSS);
		}
	}


	Vec2i Body::getCoordTex()
	{
		verifPlaylistEmptyTex();
		return  m_vAnimationTex[m_animationPlayListTex[0]]._vCoord[m_frameTex];
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
		if (m_animationPlayListTex.size() == 0)
		{
			m_animationPlayListTex.push_back(m_defAnimSS);
		}
	}

	void Body::nextFrameTex()
	{
		verifPlaylistEmptyTex();
		if (m_clockAnimTex.getElapsedTime() >= m_vAnimationTex[m_animationPlayListTex[0]]._time)
		{
			m_frameTex++; //Increases the frame to go to the next one. 
			if (m_frameTex >= m_vAnimationTex[m_animationPlayListTex[0]].size()) //If it reaches the end of the animation...
			{
				m_frameTex = 0; //... it resets the counter.
				nextAnimationTex();//... and switches to the next animation ...
			}
		}
	}

	void Body::verifPlaylistEmptyTex()
	{
		if (m_animationPlayListTex.empty())
		{
			playAnimationTex(m_defAnimTex);
		}
	}

	///Physic func.
	Vec2f Body::moveTest(float time) const
	{
		Vec2f totalForces{ m_force + m_impulse }, acc{}; //It calculs the total of all the forces (and impulses) applied.
		//ΣF = ma <=> a = ΣF/m
		acc = totalForces / m_mass;
		//a = dv/dt <=> v = a*t + v0
		return acc * time;// return the velocity.
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
//DeltaEngine.cpp
#include "DeltaEngine.hpp"

namespace DeltaEngine //Func
{
	void print(std::string str, std::string end)
	{
		if (end == "none")
			std::cout << str << std::endl;
		else
			std::cout << str << end;
	}

	json returnJson(std::string jsonPath)
	{
		std::ifstream file(jsonPath);
		if (!file)
			std::cout << "Erreur : File not open (" << jsonPath << ")" << std::endl;
		json j{};
		file >> j;
		return j;
	}
}

namespace DeltaEngine //Project
{
	Project::Project(std::string name, int version_Major, int version_minor, bool debug, std::string icon) :
		m_name(name), m_ver_M(version_Major), m_ver_m(version_minor), m_debug(debug), m_ico(icon)
	{}

	std::string Project::get_title()
	{
		std::string title{ m_name };
		if (m_debug)
			title += " v." + std::to_string(m_ver_M) + "." + std::to_string(m_ver_m);
		return title;
	}

	bool Project::get_debug()
	{
		return m_debug;
	}

}

namespace DeltaEngine //Game
{
	Game::Game(Project& prj, b2Vec2& gravity, sf::Color& bgColor, float timeStep, int32 velIt, int32 posIt) :
		m_prj(prj), m_win(sf::VideoMode(800, 600), prj.get_title(), sf::Style::Default), m_bgColor(bgColor),
		m_gravity(gravity), m_world(m_gravity), m_timeStep(timeStep), m_velIt(velIt), m_posIt(posIt)
	{}

	sf::RenderWindow& Game::get_win()
	{
		return m_win;
	}

	std::vector<Object>& Game::get_vObj() 
	{
		return m_vObj;
	}

	std::vector<Entity>& Game::get_vEnt() 
	{
		return m_vEnt;
	}

	std::vector<Light>& Game::get_vLgh() 
	{
		return m_vLgh;
	}

	b2World& Game::get_world()
	{
		return m_world;
	}

	float Game::get_timeStep()
	{
		return m_timeStep;
	}

	int32 Game::get_velIt()
	{
		return m_velIt;
	}

	int32 Game::get_posIt()
	{
		return m_posIt;
	}

	void Game::draw()
	{
		//Init
		std::vector<Part> vPartObj, vPartEnt;
		sf::Sprite sprite;
		sf::RenderTexture debTex, lghTex;
		debTex.create(800, 600);
		lghTex.create(800, 600);

		m_win.clear();
		debTex.clear();
		lghTex.clear(m_bgColor);
		
		for (unsigned int i{ 0 }; i < m_vObj.size(); i++)
		{	
			for (int j{ 0 }; j < m_vObj[i].get_nb_part(); j++)
			{
				vPartObj.push_back(m_vObj[i].get_vPart()[j]);
			}
		}
		//Add all Parts to vPartObj
		for (unsigned int i{ 0 }; i < m_vEnt.size(); i++)
		{
			m_vEnt[i].updateLight();
			for (int j{ 0 }; j < m_vEnt[i].get_nb_part(); j++)
			{
				vPartEnt.push_back(m_vEnt[i].get_vPart()[j]);
			}
		}
		//Idem for Entity

		for (unsigned int i{ 0 }; i < vPartObj.size(); i++)
		{
			if (vPartObj[i].get_textureOn())
			{
				if (vPartObj[i].get_shapeTex())
				{
					vPartObj[i].get_shape().setTexture(&vPartObj[i].get_texture());
					vPartObj[i].get_shape().setPosition(vPartObj[i].get_pos());
					vPartObj[i].get_shape().setRotation(vPartObj[i].get_angle());
					m_win.draw(vPartObj[i].get_shape());
				}
				else
				{
					sprite.setTexture(vPartObj[i].get_texture());
					sprite.setPosition(vPartObj[i].get_pos());
					sprite.setRotation(vPartObj[i].get_angle());
					m_win.draw(sprite);
				}
			}
			if (!vPartObj[i].get_textureOn() || m_prj.get_debug())
			{
				for (unsigned int j{ 0 }; j < vPartObj[i].get_nb_vtx(); j++)
				{
					vPartObj[i].get_shape().setPosition(vPartObj[i].get_pos());
					vPartObj[i].get_shape().setRotation(vPartObj[i].get_angle());
					vPartObj[i].get_shape().setOutlineColor(sf::Color::Blue);
					vPartObj[i].get_shape().setFillColor(sf::Color::Transparent);
					vPartObj[i].get_shape().setOutlineThickness(2.f);
				}
				debTex.draw(vPartObj[i].get_shape());
			}

			for (unsigned int j{ 0 }; j < vPartObj[i].get_vLgh().size(); j++)
			{
				m_vPartLgh.push_back(vPartObj[i].get_vLgh()[j]);
			}
			
		}
		//Gets textures and draw them.
		for (unsigned int i{ 0 }; i < vPartEnt.size(); i++)
		{
			if (vPartEnt[i].get_textureOn() || m_prj.get_debug())
			{
				if (vPartEnt[i].get_shapeTex())
				{
					vPartEnt[i].get_shape().setTexture(&vPartEnt[i].get_texture());
					vPartEnt[i].get_shape().setPosition(vPartEnt[i].get_pos());
					vPartEnt[i].get_shape().setRotation(vPartEnt[i].get_angle());
					m_win.draw(vPartEnt[i].get_shape());
				}
				else
				{
					sprite.setTexture(vPartEnt[i].get_texture());
					sprite.setPosition(vPartEnt[i].get_pos());
					sprite.setRotation(vPartEnt[i].get_angle());
					m_win.draw(sprite);
				}
			}
			if (!vPartEnt[i].get_textureOn() || m_prj.get_debug())
			{
				for (unsigned int j{ 0 }; j < vPartEnt[i].get_nb_vtx(); j++)
				{
					vPartEnt[i].get_shape().setPosition(vPartEnt[i].get_pos());
					vPartEnt[i].get_shape().setRotation(vPartEnt[i].get_angle());
					vPartEnt[i].get_shape().setOutlineColor(sf::Color::Blue);
					vPartEnt[i].get_shape().setFillColor(sf::Color::Transparent);
					vPartEnt[i].get_shape().setOutlineThickness(2.f);
				}
				debTex.draw(vPartEnt[i].get_shape());
			}

			for (unsigned int j{ 0 }; j < vPartEnt[i].get_vLgh().size(); j++)
			{
				m_vPartLgh.push_back(vPartEnt[i].get_vLgh()[j]);
			}
			//Adds Lights from Parts to Game.
		}
		//Idem for Entities.
		
		for (unsigned int i{ 0 }; i < m_vLgh.size(); i++)
		{
			lghTex.draw(m_vLgh[i].get_vtxArr());
		}
		//print("size-light : " + std::to_string(m_vPartLgh.size()));
		for (unsigned int i{ 0 }; i < m_vPartLgh.size(); i++)
		{
			lghTex.draw(m_vPartLgh[i].get_vtxArr());
		}
		m_vPartLgh.clear();
		//Draws Lights on lghTex

		debTex.display();
		lghTex.display();
		sf::Sprite lghSpr(lghTex.getTexture()), debSpr(debTex.getTexture());
		m_win.draw(lghSpr, sf::BlendMultiply);
		m_win.draw(debSpr, sf::BlendAdd);

		m_win.display();
	}

	void Game::addObj(Object& obj)
	{
		m_vObj.push_back(obj);
	}

	void Game::addEnt(Entity& ent)
	{
		m_vEnt.push_back(ent);
	}

	void Game::addLgh(Light& lgh)
	{
		m_vLgh.push_back(lgh);
	}

}

namespace DeltaEngine //Part
{
	Part::Part(std::string jsonPath, b2World& world, sf::Vector2f pos)
	{
		//---JSON---
		json j{ returnJson(jsonPath) }; //Collects data from json.
		//---Class---
		m_coef = j["coef"]; //Defines the members vars with the json file.
		m_priority = j["priority"];
		m_type = j["type"];
		m_bodyType = j["bodyType"];
		m_nb_vtx = j["nb_vtx"];
		//---SFML---
		m_shape = sf::ConvexShape(m_nb_vtx); //Makes a shape with [nb_vtx] vertices.
		double vtxPosX{ 0 }, vtxPosY{ 0 };
		for (int i{ 0 }; i < m_nb_vtx; i++)
		{
			vtxPosX = j["vtxPos"][i][0]; vtxPosY = j["vtxPos"][i][1];
			m_shape.setPoint(i, sf::Vector2f(vtxPosX*m_coef, vtxPosY*m_coef));
		}
		m_shapeTex = j["shapeTex"];
		m_tex_load = m_tex.loadFromFile(j["texPath"]);
		////m_shape.setTexture(&m_tex);
		//Set the vertices to their own pos.
		//---Box2D---
		b2Vec2 vertices[b2_maxPolygonVertices]; //Create an array of vertices.
		for (int i{ 0 }; i < m_nb_vtx; i++)
		{
			vertices[i].Set(j["vtxPos"][i][0], j["vtxPos"][i][1]);
		}
		//Set the vertices to their own pos.
		b2PolygonShape partShape; //Create a shape for the part.
		partShape.Set(vertices, m_nb_vtx); //Set the vertices for the shape.
		b2FixtureDef fixtureDef; //Create a FixtureDef.
		fixtureDef.shape = &partShape; //Set the shape to the FixtureDef.
		fixtureDef.density = j["density"]; //Set the density of the part.
		fixtureDef.friction = j["friction"]; //Set the friction of the part.
		fixtureDef.restitution = j["restitution"]; //...
		b2BodyDef bodyDef; //Create a BodyDef.
		float posX{ j["pos"][0] + pos.x }, posY{ j["pos"][1] + pos.y };
		bodyDef.position.Set(posX, posY);

		switch (m_bodyType)
		{
		case STATICBODY:
			bodyDef.type = b2_staticBody;
			break;
		case KINEMATICBODY:
			bodyDef.type = b2_kinematicBody;
			break;
		case DYNAMICBODY:
			bodyDef.type = b2_dynamicBody;
			bodyDef.fixedRotation = true;
			break;
		default:
			break;
		}
		fixtureDef.filter.categoryBits = m_type;
		switch (m_type)
		{
		case DECOR:
			fixtureDef.filter.maskBits = NOTHING;
			break;
		case GROUND:
			fixtureDef.filter.maskBits = PLAYER | PNJ | ENEMY | BULLET;
			break;
		case PLAYER:
			fixtureDef.filter.maskBits = GROUND | ENEMY | BULLET;
			break;
		case PNJ:
			fixtureDef.filter.maskBits = GROUND | ENEMY | BULLET;
			break;
		case ENEMY:
			fixtureDef.filter.maskBits = GROUND | PLAYER | PNJ | ENEMY | BULLET;
			break;
		case BULLET:
			fixtureDef.filter.maskBits = GROUND | PLAYER | PNJ | ENEMY;
			break;
		default:
			break;
		}
		//Set the type of the part.
		m_body = world.CreateBody(&bodyDef); //Create the part.
		m_body->CreateFixture(&fixtureDef); //Set the fixture to the part.

		//---Light--
		for (unsigned int i{ 0 }; i < j["nbLgh"]; i++)
		{
			m_vLgh.push_back(Light(sf::Vector2f((float)j["lights"][i]["lPos"][0], (float)j["lights"][i]["lPos"][1]),
				j["lights"][i]["lRad"], j["lights"][i]["lVtx"], sf::Vector3f(j["lights"][i]["lColor"][0],
					j["lights"][i]["lColor"][1], j["lights"][i]["lColor"][2])));
			m_vLgh.back().set_pos(sf::Vector2f(j["pos"][0]*m_coef, j["pos"][1]*m_coef));
		}
	}

	double Part::get_coef()
	{
		return m_coef;
	}

	int Part::get_priority()
	{
		return m_priority;
	}

	int Part::get_nb_vtx()
	{
		return m_nb_vtx;
	}

	sf::ConvexShape& Part::get_shape()
	{
		return m_shape;
	}

	sf::Texture& Part::get_texture()
	{
		return m_tex;
	}

	bool Part::get_shapeTex()
	{
		return m_shapeTex;
	}

	bool Part::get_textureOn()
	{
		if (m_tex_load)
			return TEXTURE_ON;
		else
			return false;
	}

	b2Body* Part::get_body()
	{
		return m_body;
	}

	sf::Vector2f Part::get_pos(bool inPx)
	{
		b2Vec2 pos{ m_body->GetPosition() };
		if(inPx)
			return sf::Vector2f(pos.x*m_coef, pos.y*m_coef);
		else
			return sf::Vector2f(pos.x, pos.y);
	}

	double Part::get_angle(bool inDeg)
	{
		if (inDeg)
			return m_body->GetAngle() * RAD2DEG;
		else
			return m_body->GetAngle();
	}

	std::vector<Light>& Part::get_vLgh()
	{
		return m_vLgh;
	}
}

namespace DeltaEngine //Object
{
	Object::Object(std::string jsonPath, b2World& world, sf::Vector2f pos)
	{
		json j{ returnJson(jsonPath) }; //Collect data from json.
		m_id = j["id"]; //Set the id.
		m_name = j["name"]; //...
		m_nb_part = j["nb_part"]; //...
		for (int i{ 0 }; i < m_nb_part; i++)
		{
			m_vPart.push_back(Part(j["parts"][i], world, pos));
		}
		//Create and add part to the object.
	}

	int Object::get_nb_part()
	{
		return m_nb_part;
	}

	std::vector<Part>& Object::get_vPart()
	{
		return m_vPart;
	}

}

namespace DeltaEngine //Entity
{
	Entity::Entity(std::string jsonPath, b2World& world, sf::Vector2f pos):Object::Object(jsonPath, world, pos)
	{
		json j{returnJson(jsonPath)};
		m_hpMax = j["hp"];
		m_hp = j["hp"];
		m_isAlive = true;
	}

	bool Entity::verifyIfAlive()
	{
		if (m_hp <= 0)
		{
			m_hp = 0;
			print(m_name + "is dead...");
			m_isAlive = false;
		}
		else
		{
			m_isAlive = true;
		}
		return m_isAlive;
	}

	void Entity::updateLight()
	{
		for (auto part : m_vPart)
		{
			sf::Vector2f pos{ part.get_body()->GetPosition().x * (float)part.get_coef(),
				part.get_body()->GetPosition().y * (float)part.get_coef() }; //Gets the pos of the Part
			for (auto lgh : part.get_vLgh())
			{
				lgh.set_pos(pos); //Sets the pos of the Light.
			}
		}
	}

	void Entity::damage(double val)
	{
		m_hp -= val;
		verifyIfAlive();
	}

	void Entity::heal(double val)
	{
		m_hp += val;
		if (m_hp > m_hpMax)
			m_hp = m_hpMax;
	}

	void Entity::move(int dir, double val, double drag, double acc)
	{
		b2Vec2 vel{ 0.f, 0.f };
		for (int i{ 0 }; i < m_nb_part; i++)
		{
			vel += m_vPart[i].get_body()->GetLinearVelocity();
		}
		double desiredVel = 0;
		switch (dir)
		{
		case -1:  desiredVel = b2Min(vel.x - acc, -val); break;
		case 0:  desiredVel = vel.x * drag; break;
		case 1: desiredVel = b2Max(vel.x + acc, val); break;
		}
		double velChange{ desiredVel - vel.x };
		double force{ 0 };
		for (int i{ 0 }; i < m_nb_part; i++)
		{
			force = m_vPart[i].get_body()->GetMass() * velChange / (1 / 60.0); //f = mv/t
			m_vPart[i].get_body()->ApplyForce(b2Vec2(force, 0), m_vPart[i].get_body()->GetWorldCenter(), true);
		}
	}

	void Entity::tp(b2Vec2 pos)
	{
		for (int i{ 0 }; i < m_nb_part; i++)
		{
			m_vPart[i].get_body();
		}
	}
}

namespace DeltaEngine //Light
{
	Light::Light(sf::Vector2f pos, double rad, int vtx, sf::Vector3f color)
	{
		m_rad = rad;
		m_vtxArr = sf::VertexArray(sf::TriangleFan, vtx);
		m_vtxArr[0].position = pos;
		std::cout << "pos_0 : " << pos.x << '/' << pos.y << std::endl;
		m_vtxArr[0].color = sf::Color(color.x, color.y, color.z, 255);
		for (int i{ 1 }; i < vtx; i++)
		{
			double angle{ 2 * i * b2_pi / (vtx-2) };
			m_vtxArr[i].position = sf::Vector2f(pos.x + cos(angle)*m_rad, pos.y + sin(angle)*m_rad);
			//std::cout << "pos_" << i << " : " << pos.x + cos(angle) * rad << '/' << pos.y + sin(angle) * rad << std::endl;
			m_vtxArr[i].color = sf::Color(color.x, color.y, color.z, 255/m_rad);
		}
		m_pos = pos;
		
	}

	sf::VertexArray& Light::get_vtxArr()
	{
		return m_vtxArr;
	}

	void Light::set_pos(sf::Vector2f pos)
	{
		m_vtxArr[0].position = pos+m_pos;
		for (unsigned int i{ 1 }; i < m_vtxArr.getVertexCount(); i++)
		{
			double angle{ 2 * i * b2_pi / (m_vtxArr.getVertexCount() - 2) };
			sf::Vector2f vAngle(cos(angle) * m_rad, sin(angle) * m_rad);
			m_vtxArr[i].position = pos + m_pos + vAngle;
		}
	}
}
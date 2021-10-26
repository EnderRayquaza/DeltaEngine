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
		std::ifstream file(jsonPath); //Opens the file.
		if (!file) //Returns an error if it can't.
			std::cout << "Erreur : File not open (" << jsonPath << ")" << std::endl;
		json j{}; //Creates a json variable.
		file >> j; //Puts the data from the file in the json var.
		return j; //Returns it.
	}

	sf::Texture findSpr_texSheet(sf::Texture tex, sf::Vector2i sizeSpr, sf::Vector2i posSpr)
	{
		sf::Sprite spr{};
		spr.setTexture(tex);
		sf::Vector2i pos{ posSpr.x * sizeSpr.x, posSpr.y * sizeSpr.y };
		spr.setTextureRect(sf::IntRect(pos.x, pos.y, pos.x+sizeSpr.x, pos.y+sizeSpr.y));
		return *spr.getTexture();
	}
}

namespace DeltaEngine //Project
{
	Project::Project(std::string name, int version_Major, int version_minor, bool debug, std::string icon) :
		m_name(name), m_ver_M(version_Major), m_ver_m(version_minor), m_debug(debug), m_ico(icon)
	{}

	std::string Project::get_title()
	{
		std::string title{ m_name }; //Sets the name for title.
		if (m_debug) //If we're in debug mode, we show the version.
			title += " v." + std::to_string(m_ver_M) + "." + std::to_string(m_ver_m); //Adds the version to the title.
		return title; //Returns the title.
	}

	bool Project::get_debug()
	{
		return m_debug;
	}

	void Project::set_debug(bool val)
	{
		m_debug = val;
	}

}

namespace DeltaEngine //Game
{
	Game::Game(Project& prj, b2Vec2& gravity, sf::Color& bgColor, float timeStep, int32 velIt, int32 posIt) :
		m_prj(prj), m_win(sf::VideoMode(800, 600), prj.get_title(), sf::Style::Default), m_bgColor(bgColor),
		m_gravity(gravity), m_world(m_gravity), m_timeStep(timeStep), m_velIt(velIt), m_posIt(posIt)
	{}

	Project& Game::get_project()
	{
		return m_prj;
	}

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
		std::vector<Part> vPart; //Creates a vector to contain Parts.
		sf::Sprite sprite; //Creates a sprite to show the Parts.
		sf::RenderTexture debTex, lghTex; //Creates RenderTexture to draw on it debug hitboxes and Lights.
		debTex.create(800, 600); //Inits the debTex by the size of the window.
		lghTex.create(800, 600); //Idem for lghTex.

		m_win.clear(); //Clears the RenderWindow.
		debTex.clear(); //Idem.
		lghTex.clear(m_bgColor); //Idem with the color of bgColor.
		
		for (auto obj : m_vObj)
		{	
			obj.updateLight(); //Updates the Lights position.
			for (auto part : obj.get_vPart())
			{
				vPart.push_back(part);
			}
		}
		//Add all Parts to vPartObj
		for (auto ent : m_vEnt)
		{
			ent.updateLight(); //Updates the Lights position.
			for (auto part : ent.get_vPart())
			{
				vPart.push_back(part);
			}
		}
		//Idem for Entity

		for (unsigned int i{ 0 }; i < 5; i++)
		{
			for (auto part : vPart)
			{
				if (part.get_priority() == i)
				{
					if (part.get_textureOn()) //If the textures are enabled.
					{
						if (part.get_shapeTex()) //If the Part shapes/cuts the Texture with the Shape.
						{
							part.get_shape().setTexture(&part.get_texture()); //Puts the Tex in the shape.
							if (part.get_animated())
								part.get_shape().setTextureRect(part.get_currSprRect());
							part.get_shape().setPosition(part.get_pos()); //Sets to its pos.
							part.get_shape().setRotation(part.get_angle()); //Rotates it.
							m_win.draw(part.get_shape()); //Draws it to the RenderWindow.
						}
						else // /!\ The texture can be out of the Shape ! /!\ 
						{
							sprite.setTexture(part.get_texture()); //Puts the Texture to the Sprite.
							if (part.get_animated())
								sprite.setTextureRect(part.get_currSprRect());
							sprite.setPosition(part.get_pos()); //Sets to its pos.
							sprite.setRotation(part.get_angle()); //Rotates it.
							m_win.draw(sprite); //Draws to the RenderWindow.
						}
					}
					if (!part.get_textureOn() || m_prj.get_debug()) //If the Textures are disabled or the Project is in debug mode.
					{
						for (unsigned int i{ 0 }; i < part.get_nb_vtx(); i++)
						{
							part.get_shape().setPosition(part.get_pos()); //Sets the Shape to its position.
							part.get_shape().setRotation(part.get_angle()); //Rotates it.
							part.get_shape().setOutlineColor(sf::Color::Blue); //Colors it.
							part.get_shape().setFillColor(sf::Color::Transparent); //Idem
							part.get_shape().setOutlineThickness(2.f);
						}
						debTex.draw(part.get_shape()); //Draws the Shape to the debug Texture.
					}

					for (auto lgh : part.get_vLgh())
					{
						m_vPartLgh.push_back(lgh);
					}
				}
			}
		}
		//Gets textures and draw them.

		for (auto lgh : m_vLgh)
		{
			lghTex.draw(lgh.get_vtxArr());
		}
		for (auto lgh : m_vPartLgh)
		{
			lghTex.draw(lgh.get_vtxArr());
		}
		//Draws Lights on lghTex
		m_vPartLgh.clear(); //Clear vPartLgh to avoid duplication.

		debTex.display(); //Displays the debug Texture.
		lghTex.display(); //Idem for Light Texture.
		sf::Sprite lghSpr(lghTex.getTexture()), debSpr(debTex.getTexture()); //Creates Sprites with the RenderTextures.
		m_win.draw(lghSpr, sf::BlendMultiply); //Draws the Light Texture on the RenderWindow.
		m_win.draw(debSpr, sf::BlendAdd); //Draws the debug Texture on the RenderWindow.

		m_win.display(); //Displays the RenderWindow.
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
		for (unsigned int i{ 0 }; i<j["nb_vtx"]; i++)
		{
			vtxPosX = j["vtxPos"][i][0]; vtxPosY = j["vtxPos"][i][1]; //Collects the position from the .json file.
			m_shape.setPoint(i, sf::Vector2f(vtxPosX*m_coef, vtxPosY*m_coef)); //Sets vertices to their pos(which converted from meters to px).
		}
		m_shapeTex = j["shapeTex"];
		m_tex_load = m_tex.loadFromFile(j["texPath"]);
		m_animated = j["animated"];
		m_sizeSpr = sf::Vector2i(j["sizeSpr"][0], j["sizeSpr"][1]);
		m_currentSprPos = sf::Vector2i(j["startSprPos"][0], j["startSprPos"][1]);
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
		for (auto jLights : j["lights"])
		{
			m_vLgh.push_back(Light(sf::Vector2f((float)jLights["lPos"][0], (float)jLights["lPos"][1]),
				jLights["lRad"], jLights["lVtx"], sf::Vector3f(jLights["lColor"][0], jLights["lColor"][1],
					jLights["lColor"][2])));
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

	bool Part::get_animated()
	{
		return m_animated;
	}

	sf::Vector2i Part::get_sizeSpr()
	{
		return m_sizeSpr;
	}

	sf::Vector2i Part::get_currentSprPos()
	{
		return m_currentSprPos;
	}

	sf::IntRect Part::get_currSprRect()
	{
		sf::Vector2i currSprPos{ m_currentSprPos.x * m_sizeSpr.x, m_currentSprPos.x * m_sizeSpr.x };
		return sf::IntRect(currSprPos, m_sizeSpr);
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
		json j{ returnJson(jsonPath) }; //Collects data from json.
		m_id = j["id"]; //Sets the id.
		m_name = j["name"]; //...
		m_nb_part = j["nb_part"]; //...
		for (unsigned int i{ 0 }; i < m_nb_part; i++)
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

	void Object::updateLight()
	{
		for (auto& part : m_vPart)
		{
			sf::Vector2f pos{ part.get_body()->GetPosition().x * (float)part.get_coef(),
				part.get_body()->GetPosition().y * (float)part.get_coef() }; //Gets the pos of the Part
			for (auto& lgh : part.get_vLgh())
			{
				lgh.set_pos(pos); //Sets the pos of the Light.
			}
		}
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

	void Entity::move(float dir, float val, double drag, float acc)
	{
		float t{ 1 / 60.0 }, m{ 0 };
		b2Vec2 vmax{ cos(dir) * val, sin(dir) * val }, v0{ 0, 0 }, dv{ 0, 0 }, a{ 0, 0 }, f{ 0, 0 };
		for (auto part : m_vPart)
		{
			v0 += part.get_body()->GetLinearVelocity();
		}

		b2Vec2 v_{ 0, 0 };
		if (0 <= dir && dir < (b2_pi / 2))
			v_ = b2Vec2{ b2Max(v0.x + acc, vmax.x), b2Max(v0.y + acc, vmax.y) };
		else if (b2_pi / 2 <= dir && dir < b2_pi)
			v_ = b2Vec2{ b2Min(v0.x - acc, vmax.x), b2Max(v0.y + acc, vmax.y) };
		else if (b2_pi <= dir && dir < 1.5 * b2_pi)
			v_ = b2Vec2{ b2Min(v0.x - acc, vmax.x), b2Min(v0.y - acc, vmax.y) };
		else if (1.5 * b2_pi <= dir && dir < 2 * b2_pi)
			v_ = b2Vec2{ b2Max(v0.x + acc, vmax.x), b2Min(v0.y - acc, vmax.y) };
		else
			print("dir must be in [0, 2pi]");
		b2Vec2 a_{ (v_.x - v0.x)/t, (v_.y - v0.y)/t }, f_{ 0, 0 };
		for (auto part : m_vPart)
		{
			m = part.get_body()->GetMass();
			f_ = b2Vec2{ a_.x * m, a_.y * m }; //f = ma
			part.get_body()->ApplyForce(f_, part.get_body()->GetWorldCenter(), true);
		}
	}

	void Entity::tp(b2Vec2 pos)
	{
	}
}

namespace DeltaEngine //Light
{
	Light::Light(sf::Vector2f pos, double rad, int vtx, sf::Vector3f color)
	{
		m_rad = rad; //Sets the radius.
		m_vtxArr = sf::VertexArray(sf::TriangleFan, vtx); //Creates a VertexArray with the TriangleFan model.
		m_vtxArr[0].position = pos; //Sets the center of the circle.
		m_vtxArr[0].color = sf::Color(color.x, color.y, color.z, 255); //Sets the color.
		for (unsigned int i{ 1 }; i < vtx; i++)
		{
			double angle{ 2 * i * b2_pi / (vtx-2) }; //Calculates the angle of the vertex.
			m_vtxArr[i].position = sf::Vector2f(pos.x + cos(angle)*m_rad, pos.y + sin(angle)*m_rad); //Sets it to its pos.
			m_vtxArr[i].color = sf::Color(color.x, color.y, color.z, 255/m_rad); //Colors it to make a shade.
		}
		m_pos = pos; //Sets the pos.
		
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
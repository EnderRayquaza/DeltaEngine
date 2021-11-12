//DeltaEngine.cpp
#include "DeltaEngine.hpp"

namespace DeltaEngine //Functions
{
	json returnJson(std::string jsonPath)
	{
		std::ifstream file(jsonPath); //Opens the file.
		if (!file) //Returns an error if it can't.
			std::cout << "Erreur : File not open (" << jsonPath << ")" << std::endl;
		json j{}; //Creates a json variable.
		file >> j; //Puts the data from the file in the json var.
		return j; //Returns it.
	}
}

namespace DeltaEngine //Game
{
	Game::Game(std::string name, int version_Major, int version_minor, bool debug, bool textureOn,
		std::string icon, ShaderManager* shaderManager, sf::Color& bgColor, b2Vec2& gravity,
		float timeStep = 1.f / 60.f, int32 velocityIt = 6, int32 positionIt = 3):m_name(name),
		m_version_M(version_Major), m_version_m(version_minor), m_debug(debug), 
		m_textureOn(textureOn), m_icon(icon), m_shaderManager(shaderManager),
		m_window(sf::VideoMode(800, 600), ""), m_bgColor(bgColor), m_gravity(gravity),
		m_world(m_gravity), m_timeStep(timeStep), m_velocityIt(velocityIt),
		m_positionIt(positionIt)
	{
		m_window.setTitle(get_title());
	}

	//Getters
	std::string Game::get_title(bool showVersion)
	{
		std::string title{ m_name }; //Sets the name for title.
		if (m_debug || showVersion) //If we're in debug mode, we show the version.
			title += " v." + std::to_string(m_version_M) + "." + std::to_string(m_version_m); //Adds the version to the title.
		return title; //Returns the title.
	}

	bool Game::get_debug()
	{
		return m_debug;
	}

	std::vector<Object>& Game::get_vObject()
	{
		return m_vObject;
	}

	std::vector<Entity>& Game::get_vEntity()
	{
		return m_vEntity;
	}

	std::vector<Light>& Game::get_vLight()
	{
		return m_vLight;
	}

	sf::RenderWindow& Game::get_window()
	{
		return m_window;
	}

	b2World& Game::get_world()
	{
		return m_world;
	}

	float Game::get_timeStep()
	{
		return m_timeStep;
	}

	int32 Game::get_velocityIt()
	{
		return m_velocityIt;
	}

	int32 Game::get_positionIt()
	{
		return m_positionIt;
	}

	//Setters
	void Game::set_debug(bool value)
	{
		m_debug = value;
	}

	void Game::addObject(Object& object)
	{
		m_vObject.push_back(object);
	}

	void Game::addEntity(Entity& entity)
	{
		m_vEntity.push_back(entity);
	}

	void Game::addLight(Light& light)
	{
		m_vLight.push_back(light);
	}

	void Game::removeObject(int index)
	{
		m_vObject[index].~Object();
		auto delElem = m_vObject.begin() + index;
		if (delElem != m_vObject.end())
		{
			m_vObject.erase(delElem);
		}
	}

	void Game::removeEntity(int index)
	{
		m_vEntity[index].~Entity();
		auto delElem = m_vEntity.begin() + index;
		if (delElem != m_vEntity.end())
		{
			m_vEntity.erase(delElem);
		}
	}

	void Game::removeLight(int index)
	{
		m_vLight[index].~Light();
		auto delElem = m_vLight.begin() + index;
		if (delElem != m_vLight.end())
		{
			m_vLight.erase(delElem);
		}
	}

	//Others
	void Game::draw()
	{
		//Init
		std::vector<Part> vPart; //Creates a vector to contain Parts.
		sf::Sprite sprite; //Creates a sprite to show the Parts.
		sf::RenderTexture debTex, lightTex; //Creates RenderTexture to draw on it debug hitboxes 
											//and Lights.
		debTex.create(800, 600); //Inits the debTex by the size of the window.
		lightTex.create(800, 600); //Idem for lghTex.

		m_window.clear(); //Clears the RenderWindow.
		debTex.clear(); //Idem.
		lightTex.clear(m_bgColor); //Idem with the color of bgColor.

		for (auto& obj : m_vObject)
		{
			obj.updateLight(); //Updates the Lights position.
			for (auto& part : obj.m_vPart)
			{
				vPart.push_back(part);
			}
		}
		//Add all Parts to vPartObj
		for (auto& ent : m_vEntity)
		{
			ent.updateLight(); //Updates the Lights position.
			for (auto& part : ent.m_vPart)
			{
				vPart.push_back(part);
			}
		}
		//Idem for Entity

		for (int i{ 0 }; i < PRIORITIES; i++)
		{
			for (auto& part : vPart)
			{
				if (part.m_priority == i)
				{
					if (m_debug)
					{
						part.m_shape.setTexture(&part.m_texture);
						part.m_shape.setPosition(part.get_position());
						part.m_shape.setRotation(part.get_angle());
						switch (part.m_bodyType)
						{
						case STATICBODY:
							part.m_shape.setOutlineColor(sf::Color::Blue);
							break;
						case KINEMATICBODY:
							part.m_shape.setOutlineColor(sf::Color(138, 43, 226)); //Violet
							break;
						case DYNAMICBODY:
							part.m_shape.setOutlineColor(sf::Color::Green);
							break;
						default:
							part.m_shape.setOutlineColor(sf::Color::Red);
							break;
						}
						part.m_shape.setFillColor(sf::Color::Transparent);
						part.m_shape.setOutlineThickness(2.f);
						debTex.draw(part.m_shape);
					}
					if (m_textureOn)
					{
						if (part.m_shapeTexture)
						{
							part.m_shape.setTexture(&part.m_texture);
							if (part.m_animated)
								part.m_shape.setTextureRect(part.get_currentSpriteRect());
							part.m_shape.setPosition(part.get_position());
							part.m_shape.setRotation(part.get_angle());
							m_window.draw(part.m_shape, m_shaderManager->get_shader(part.m_shaderIndexes[0]));
						}
						else
						{
							sprite.setTexture(part.m_texture);
							if (part.m_animated)
								sprite.setTextureRect(part.get_currentSpriteRect());
							sprite.setPosition(part.get_position());
							sprite.setRotation(part.get_angle());
							m_window.draw(sprite, m_shaderManager->get_shader(part.m_shaderIndexes[0]));
						}
					}
				}
			}
		}
		//Gets textures and draw them.

		for (auto& part : vPart)
		{
			for (auto& light : part.m_vLight)
			{
				m_vPartLight.push_back(light);
			}
		}
		//Collects the lights linked to the parts.

		for (auto& light : m_vLight)
		{
			lightTex.draw(light.get_vertexArray());
		}
		for (auto& light : m_vPartLight)
		{
			lightTex.draw(light.get_vertexArray());
		}
		//Draws Lights on lightTex
		m_vPartLight.clear(); //Clear vPartLight to avoid duplication.

		debTex.display(); //Displays the debug Texture.
		lightTex.display(); //Idem for Light Texture.
		sf::Sprite lightSprite(lightTex.getTexture()), debSprite(debTex.getTexture()); //Creates 
		//Sprites with the RenderTextures.
		m_window.draw(lightSprite, sf::BlendMultiply); //Draws the Light Texture on the 
													   //RenderWindow.
		m_window.draw(debSprite, sf::BlendAdd); //Draws the debug Texture on the RenderWindow.

		m_window.display(); //Displays the RenderWindow.
	}
}

namespace DeltaEngine //Part
{
	Part::Part(std::string jsonPath, b2World& world, sf::Vector2f position = sf::Vector2f(0, 0))
	{
		//JSON
		json j{ returnJson(jsonPath) }; //Collects data from json.

		//Class members
		m_priority = j["priority"];
		for (auto jIdx : j["shaderIndexes"])
		{
			m_shaderIndexes.push_back(jIdx);
		}
		for (auto jL : j["lights"])
		{
			m_vLight.push_back(Light(jL["radius"], jL["vertices"], 
				sf::Vector2f(jL["position"][0], jL["position"][1]), 
				sf::Color(jL["color"][0],jL["color"][1], jL["color"][2]), jL["intensity"]));
			m_vLight.back().set_position(sf::Vector2f(j["pos"][0] * m_coef, j["pos"][1] * m_coef));
		}
		for (auto jDL : j["lights"])
		{
			m_vLight.push_back(Light(jDL["radius"], jDL["vertices"],
				sf::Vector2f(jDL["position"][0], jDL["position"][1]),
				jDL["abscissa_angle"], jDL["opening_angle"],
				sf::Color(jDL["color"][0], jDL["color"][1], jDL["color"][2]), jDL["intensity"]));
			m_vLight.back().set_position(sf::Vector2f(j["pos"][0] * m_coef, j["pos"][1] * m_coef));
		}

		m_coef = j["coef"];
		m_nb_vertices = j["nb_vertices"];

		//Class members (SFML)
		m_shape = sf::ConvexShape(m_nb_vertices);
		double vtxPosX{ 0 }, vtxPosY{ 0 };
		for (int i{ 0 }; i < m_nb_vertices; i++)
		{
			vtxPosX = j["vertexPosition"][i][0]; vtxPosY = j["vertexPosition"][i][1];//Collects the
			//position from the .json file.
			m_shape.setPoint(i, sf::Vector2f(vtxPosX * m_coef, vtxPosY * m_coef)); //Sets vertices 
			//to their position (which converted from meters to px).
		}
		if (!m_texture.loadFromFile(j["texture"]))
			std::cout << "Texture not loaded" << std::endl;
		m_shapeTexture = j["shapeTexture"];
		m_animated = j["animated"];
		m_sizeSprite = sf::Vector2i(j["sizeSprite"][0], j["sizeSprite"][1]);
		m_currentSpritePosition = sf::Vector2i(j["startSpritePosition"][0],
			j["startSpritePosition"][1]);

		//Class members (Box2d)
		m_type = j["type"];
		m_bodyType = j["bodyType"];
		//Creation of the body
		b2Vec2 vertices[b2_maxPolygonVertices]; //Creates an array of vertices.
		for (int i{ 0 }; i < m_nb_vertices; i++)
		{
			vertices[i].Set(j["vtxPos"][i][0], j["vtxPos"][i][1]);
		}
		//Sets the vertices to their own pos.
		b2PolygonShape partShape; //Creates a shape for the part.
		partShape.Set(vertices, m_nb_vertices); //Sets the vertices for the shape.
		b2FixtureDef fixtureDef; //Creates a FixtureDef.
		fixtureDef.shape = &partShape; //Set the shape to the FixtureDef.
		fixtureDef.density = j["density"]; //Set the density of the part.
		fixtureDef.friction = j["friction"]; //Set the friction of the part.
		fixtureDef.restitution = j["restitution"]; //...
		b2BodyDef bodyDef; //Create a BodyDef.
		float posX{ j["position"][0] + position.x }, posY{ j["position"][1] + position.y };
		//Calculate the position of the part.
		bodyDef.position.Set(posX, posY); //Sets it.
		switch (m_bodyType) //Defines the bodyType
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
		fixtureDef.filter.categoryBits = m_type; //Defines what collides with what.
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
		m_body = world.CreateBody(&bodyDef); //Create the body.
		m_body->CreateFixture(&fixtureDef); //Set the fixture to the body.
	}

	//Getters
	sf::IntRect Part::get_currentSpriteRect()
	{
		sf::Vector2i currSprPos{ m_currentSpritePosition.x * m_sizeSprite.x,
			 m_currentSpritePosition.y * m_sizeSprite.y };
		return sf::IntRect(currSprPos, m_sizeSprite);
	}

	sf::Vector2f Part::get_position(bool inPx = true)
	{
		b2Vec2 pos{ m_body->GetPosition() };
		if (inPx)
			return sf::Vector2f(pos.x * m_coef, pos.y * m_coef);
		else
			return sf::Vector2f(pos.x, pos.y);
	}

	double Part::get_angle(bool inDeg = true)
	{
		if (inDeg)
			return m_body->GetAngle() * RAD2DEG;
		else
			return m_body->GetAngle();
	}

	//Setters
	void Part::set_currentSpritePosition(sf::Vector2i position)
	{
		m_currentSpritePosition = position;
	}

	void Part::set_currentSpritePosition(unsigned int positionX, unsigned int positionY)
	{
		m_currentSpritePosition = sf::Vector2i(positionX, positionY);
	}
}

namespace DeltaEngine //Object
{
	Object::Object(std::string jsonPath, b2World& world, sf::Vector2f position = sf::Vector2f(0, 0))
	{
		json j{ returnJson(jsonPath) };
		m_id = j["id"];
		m_name = j["name"];
		m_nb_part = j["nb_part"];
		for (int i{ 0 }; i < m_nb_part; i++)
		{
			m_vPart.push_back(Part(j["parts"][i], world, position));
		}
	}

	void Object::updateLight()
	{
		for (auto& part : m_vPart)
		{
			sf::Vector2f pos{ part.m_body->GetPosition().x * (float)part.m_coef,
				part.m_body->GetPosition().y * (float)part.m_coef }; //Gets the pos of the Part
			for (auto& light : part.m_vLight)
			{
				light.set_position(pos); //Sets the pos of the Light.
			}
		}
	}
}

namespace DeltaEngine //Entity
{
	Entity::Entity(std::string jsonPath, b2World& world, sf::Vector2f position = sf::Vector2f(0, 0))
		:Object::Object(jsonPath, world, position)
	{}

	void Entity::move(float direction, float value, float acceleration = 0.1)
	{
		float t{ 1 / 60.0 }, m{ 0 };
		b2Vec2 v_{ cos(direction) * value, sin(direction) * value }, v0{ 0, 0 }, dv{ 0, 0 }, a{ 0, 0 }, f{ 0, 0 };
		for (auto part : m_vPart)
		{
			v0 += part.m_body->GetLinearVelocity();
		}
		b2Vec2 a_{ (v_.x - v0.x) / t, (v_.y - v0.y) / t }, f_{ 0, 0 };
		if (v_.x == 0) a_.x = 0;
		if (v_.y == 0) a_.y = 0;
		for (auto part : m_vPart)
		{
			m = part.m_body->GetMass();
			f_ = b2Vec2{ a_.x * m, a_.y * m }; //f = ma
			part.m_body->ApplyForce(f_, part.m_body->GetWorldCenter(), true);
		}
	}
}

namespace DeltaEngine //Light
{
	Light::Light(double radius, int vertices, sf::Vector2f position,
		sf::Color color = sf::Color(255, 255, 255), double intensity = 255):m_radius(radius),
		m_vertexArray(sf::TriangleFan, vertices), m_position(position), m_color(color), 
		m_intensity(intensity), m_directed(false), m_abscissa_angle(0), m_opening_angle(0)
	{
		generate();
	}
	Light::Light(double radius, int vertices, sf::Vector2f position, double abscissa_angle,
		double opening_angle, sf::Color color = sf::Color(255, 255, 255),
		double intensity = 255) : m_radius(radius), m_vertexArray(sf::TriangleFan, vertices),
		m_position(position), m_color(color), m_intensity(intensity), m_directed(true),
		m_abscissa_angle(abscissa_angle),m_opening_angle(opening_angle)
	{
		generate();
	}

	//Getters
	sf::VertexArray& Light::get_vertexArray()
	{
		return m_vertexArray;
	}
	
	//Setters
	void Light::set_position(sf::Vector2f position)
	{
		m_position = position;
		generate();
	}

	//Others
	void Light::generate()
	{
		m_vertexArray[0].position = m_position;
		m_vertexArray[0].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);
		double angle{ 0 };
		for(int i{1}; i<m_vertexArray.getVertexCount(); i++) //The first vertex is already placed.
		{
			if (m_directed)
				angle = i * m_opening_angle * DEG2RAD / (m_vertexArray.getVertexCount() - 2)
				+ m_abscissa_angle;
			else
				angle = 2 * b2_pi * i / (m_vertexArray.getVertexCount() - 2); //Calculate the
				//angle (0-Center-Vextex) | The last vertex will be at the same place than the first.
			m_vertexArray[i].position = sf::Vector2f(m_position.x + cos(angle) * m_radius,
				m_position.y + sin(angle) * m_radius); //Sets the vertex at its pos with trigo.
			m_vertexArray[i].color = sf::Color(m_color.r, m_color.b, m_color.g
				, m_intensity / m_radius);//More the radius is big, less the intensity will be.
		}
	}
}

namespace DeltaEngine //ShaderManager
{
	ShaderManager::ShaderManager(std::string jsonPath)
	{
		json j{ returnJson(jsonPath) };
		for (auto e : j["vert"])
		{
			sf::Shader* shader = new sf::Shader();
			shader->loadFromFile(e, sf::Shader::Type::Vertex);
			m_vShader.push_back(shader);
		}
		for (auto e : j["frag"])
		{
			sf::Shader* shader = new sf::Shader();
			shader->loadFromFile(e, sf::Shader::Type::Fragment);
			m_vShader.push_back(shader);
		}
		for (auto e : j["vert+frag"])
		{
			sf::Shader* shader = new sf::Shader();
			shader->loadFromFile(e[0], (std::string)e[0]);
			m_vShader.push_back(shader);
		}
	}

	sf::Shader* ShaderManager::get_shader(int index)
	{
		return m_vShader[index];
	}
}
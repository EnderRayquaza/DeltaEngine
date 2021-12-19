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
		std::string icon, TextureManager* textureManager, ShaderManager* shaderManager,
		sf::Color& bgColor, b2Vec2& gravity, float timeStep, int32 velocityIt,
		int32 positionIt):m_name(name), m_version_M(version_Major), m_version_m(version_minor),
		m_debug(debug), m_textureOn(textureOn), m_icon(icon), m_shaderManager(shaderManager),
		m_textureManager(textureManager), m_window(sf::VideoMode(800, 600), ""),
		m_bgColor(bgColor), m_gravity(gravity),	m_world(m_gravity), m_timeStep(timeStep),
		m_velocityIt(velocityIt), m_positionIt(positionIt)
	{
		m_window.setTitle(get_title());
	}

	Game::~Game()
	{
		m_textureManager->~TextureManager();
		m_shaderManager->~ShaderManager(); 
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
	
	bool Game::get_textureOn()
	{
		return m_textureOn;
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

	void Game::set_textureOn(bool value)
	{
		m_textureOn = value;
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

	void Game::addLinearLight(LinearLight& light)
	{
		m_vLinLight.push_back(light);
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

	void Game::removeLinearLight(int index)
	{
		m_vLinLight[index].~LinearLight();
		auto delElem = m_vLinLight.begin() + index;
		if (delElem != m_vLinLight.end())
		{
			m_vLinLight.erase(delElem);
		}
	}

	//Others
	void Game::init()
	{
		for (auto& lgh : m_vLight)
			lgh.generate();
		for (auto& lgh : m_vLinLight)
			lgh.generate();
		m_textureManager->init();
		m_shaderManager->init();
	}

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
				sprite = sf::Sprite();//Reset the sprite
				if (part.m_priority == i)
				{
					if (m_debug)
					{
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
						sf::Texture* texture;
						texture = m_textureManager->get_texture(part.m_textureIndex);
						texture->setSmooth(part.m_smoothed);
						if (part.m_shapeTexture)
						{
							if (part.m_subTexture)
								part.m_shape.setTextureRect(part.get_currentSubTextureRect());
							part.m_shape.setTexture(texture);
							part.m_shape.setPosition(part.get_position());
							part.m_shape.setRotation(part.get_angle());
							if (part.m_shaderIndex != -1)
								m_window.draw(part.m_shape, m_shaderManager->get_shader(part.m_shaderIndex));
							else
								m_window.draw(part.m_shape);
						}
						else
						{
							if(part.m_subTexture)
								sprite.setTextureRect(part.get_currentSubTextureRect());
							sprite.setTexture(*texture);
							sprite.setPosition(part.get_position());
							sprite.setRotation(part.get_angle());
							if (part.m_shaderIndex != -1)
								m_window.draw(sprite, m_shaderManager->get_shader(part.m_shaderIndex));
							else
								m_window.draw(sprite);
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
			for (auto& light : part.m_vLinLight)
			{
				m_vPartLinLight.push_back(light);
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
		for (auto& light : m_vLinLight)
		{
			for (auto& quad : light.m_vVertexArray)
			{
				lightTex.draw(quad);
			}
		}
		for (auto& light : m_vPartLinLight)
		{
			for (auto& quad : light.m_vVertexArray)
			{
				lightTex.draw(quad);
			}
		}
		//Draws Lights on lightTex
		m_vPartLight.clear(); //Clear vPartLight to avoid duplication.
		m_vPartLinLight.clear(); //Clear vPartLight to avoid duplication.

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
	Part::Part(std::string jsonPath, b2World& world, sf::Vector2f position)
	{
		//JSON
		json j{ returnJson(jsonPath) }; //Collects data from json.

		//Class members(Lights)
		//Class members(Lights)
		for (auto jL : j["lights"])
		{
			m_vLight.push_back(Light(jL, _Light::CLASSIC));
			m_vLight.back().set_position(sf::Vector2f(position.x * m_coef, position.y * m_coef));
		}
		for (auto jL : j["dirLights"])
		{
			m_vLight.push_back(Light(jL, _Light::DIRECTIONAL));
			m_vLight.back().set_position(sf::Vector2f(position.x * m_coef, position.y * m_coef));
		}
		for (auto jL : j["linLights"])
		{
			m_vLinLight.push_back(LinearLight(jL));
			m_vLinLight.back().set_position(sf::Vector2f(position.x * m_coef, position.y * m_coef));
		}
		m_nb_vertices = j["nb_vertices"];

		//Class members (SFML)
		m_coef = (double)j["coef"];
		m_priority = (int)j["priority"];
		m_textureIndex = (int)j["textureIndex"];
		m_shaderIndex = (int)j["shaderIndex"];
		m_shapeTexture = (bool)j["shapeTexture"];
		m_subTexture = (bool)j["subTexture"];
		m_smoothed = (bool)j["smoothedTexture"];

		m_sizeSubTexture = sf::Vector2i((float)j["sizeSubTexture"][0], (float)j["sizeSubTexture"][1]);
		m_currentSubTexturePosition = sf::Vector2i(
			(float)j["startSubTexturePosition"][0],
			(float)j["startSubTexturePosition"][1]);

		m_shape = sf::ConvexShape(m_nb_vertices);
		double vtxPosX{ 0 }, vtxPosY{ 0 };
		for (int i{ 0 }; i < m_nb_vertices; i++)
		{
			vtxPosX = j["verticesPositions"][i][0]; vtxPosY = j["verticesPositions"][i][1];//Collects the
			//position from the .json file.
			m_shape.setPoint(i, sf::Vector2f(vtxPosX * m_coef, vtxPosY * m_coef)); //Sets vertices 
			//to their position (which converted from meters to px).
		}

		//Class members (Box2D)
		m_type = (int)j["type"];
		m_bodyType = (int)j["bodyType"];
		//Creation of the body
		b2Vec2 vertices[b2_maxPolygonVertices]; //Creates an array of vertices.
		for (int i{ 0 }; i < m_nb_vertices; i++)
		{
			vertices[i].Set(j["verticesPositions"][i][0], j["verticesPositions"][i][1]);
		}
		//Sets the vertices to their own pos.
		b2PolygonShape partShape; //Creates a shape for the part.
		partShape.Set(vertices, m_nb_vertices); //Sets the vertices for the shape.
		b2FixtureDef fixtureDef; //Creates a FixtureDef.
		fixtureDef.shape = &partShape; //Set the shape to the FixtureDef.
		fixtureDef.density = (float)j["density"]; //Set the density of the part.
		fixtureDef.friction = (float)j["friction"]; //Set the friction of the part.
		fixtureDef.restitution = (float)j["restitution"]; //...
		b2BodyDef bodyDef; //Create a BodyDef.
		//Calculate the position of the part.
		bodyDef.position.Set(position.x, position.y); //Sets it.
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
	sf::IntRect Part::get_currentSubTextureRect()
	{
		sf::Vector2i currSprPos{ m_currentSubTexturePosition.x * m_sizeSubTexture.x,
			 m_currentSubTexturePosition.y * m_sizeSubTexture.y };
		return sf::IntRect(currSprPos, m_sizeSubTexture);
	}

	sf::Vector2f Part::get_position(bool inPx)
	{
		b2Vec2 pos{ m_body->GetPosition() };
		if (inPx)
			return sf::Vector2f(pos.x * m_coef, pos.y * m_coef);
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

	//Setters
	void Part::set_currentSubTexturePosition(sf::Vector2i position)
	{
		m_currentSubTexturePosition = position;
	}

	void Part::set_currentSubTexturePosition(unsigned int positionX, unsigned int positionY)
	{
		m_currentSubTexturePosition = sf::Vector2i(positionX, positionY);
	}
}

namespace DeltaEngine //Object
{
	Object::Object(std::string jsonPath, b2World& world, sf::Vector2f position)
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
				light.set_position(pos); //Sets the pos of the Light.
			for (auto& light : part.m_vLinLight)
				light.set_position(pos); //Sets the pos of the Light.
		}
	}
}

namespace DeltaEngine //Entity
{
	Entity::Entity(std::string jsonPath, b2World& world, sf::Vector2f position)
		:Object::Object(jsonPath, world, position)
	{}

	void Entity::move(float direction, float value, float acceleration)
	{
		float t{ 1 / 60.0 }, m{ 0 };
		b2Vec2 v_{ cos(direction) * value, sin(direction) * value }, v0{ 0.f, 0.f }, dv{ 0, 0 }, a{ 0, 0 }, f{ 0, 0 };
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
	Light::Light(std::string jsonPath, _Light typeLight)
	{
		json j{ returnJson(jsonPath) };
		m_type = typeLight;
		m_coef = (double)j["coef"];
		m_radius = (double)j["radius"];
		m_brightness = (double)j["brightness"];
		m_intensity = (double)j["intensity"];
		m_position_origin.x = (float)j["position"][0]; m_position_origin.y = (float)j["position"][1];
		m_position.x = (float)j["position"][0]; m_position.y = (float)j["position"][1];
		m_color.r = (float)j["color"][0]; m_color.g = (float)j["color"][1]; m_color.b = (float)j["color"][2];
		switch (m_type)
		{
		case _Light::CLASSIC:
		{
			m_vertexArray = sf::VertexArray(sf::TriangleFan, (int)j["vertices"]);
		}
			break;
		case _Light::DIRECTIONAL:
		{
			m_vertexArray = sf::VertexArray(sf::TriangleFan, (int)j["vertices"]);
			m_abscissa_angle = (double)j["abscissa_angle"];
			m_opening_angle = (double)j["opening_angle"];
		}
			break;
		case _Light::LINEAR:
		{
			m_vertexArray = sf::VertexArray();
		}
			break;
		default:
			assert("Light::Light(std::string, _Light) -> default(switch(m_type)) (ln.531)[DeltaEngine.cpp]");
			break;
		}
	}

	//Getters
	sf::VertexArray& Light::get_vertexArray()
	{
		return m_vertexArray;
	}
	
	//Setters
	void Light::set_position(sf::Vector2f position)
	{
		m_position = m_position_origin + position;
		generate();
	}

	//Others
	void Light::generate()
	{
		m_vertexArray[0].position = sf::Vector2f(m_position.x*m_coef, m_position.y*m_coef);
		m_vertexArray[0].color = sf::Color(m_color.r, m_color.b, m_color.g, m_brightness);
		double angle{ 0 };
		for (size_t i{ 0 }; i < m_vertexArray.getVertexCount() - 1; i++) //The first vertex is already placed.
		{
			switch (m_type)
			{
			case _Light::CLASSIC:
			{
				angle = 2 * b2_pi * i / (m_vertexArray.getVertexCount() - 2); //Calculate the
				//angle (0-Center-Vextex) | The last vertex will be at the same place than the first.
				m_vertexArray[i + 1].position = sf::Vector2f((m_position.x + cos(angle) * m_radius)*m_coef,
					(m_position.y - sin(angle) * m_radius)*m_coef); //Sets the vertex at its pos with trigo.
				m_vertexArray[i + 1].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);
				
			}
				break;
			case _Light::DIRECTIONAL:
			{
				angle = i * m_opening_angle * DEG2RAD / (m_vertexArray.getVertexCount() - 2)
					+ (m_abscissa_angle)*DEG2RAD;
				m_vertexArray[i + 1].position = sf::Vector2f((m_position.x + cos(angle) * m_radius) * m_coef,
					(m_position.y - sin(angle) * m_radius) * m_coef); //Sets the vertex at its pos with trigo.
				m_vertexArray[i + 1].color = sf::Color(m_color.r, m_color.b, m_color.g
					, m_intensity);
			}
				break;
			case _Light::LINEAR:
			{}
				break;
			default:
				assert("Light::generate() -> default(switch (m_type)) (ln.587)[DeltaEngine.cpp]");
				break;
			}
		}
	}
}

namespace DeltaEngine //LinearLight
{
	LinearLight::LinearLight(std::string jsonPath):Light(jsonPath, _Light::LINEAR)
	{
		json j{ returnJson(jsonPath) };
		for (auto jvp : j["verticesPosition"])
		{
			m_verticesPosition.push_back(sf::Vector2f(jvp[0], jvp[1]));
		}
		for (size_t i{ 0 }; i < 2 * m_verticesPosition.size() + 2; i++)
		{
			m_vVertexArray.push_back(sf::VertexArray(sf::Quads, 4));
		}
	}

	//Others
	void LinearLight::generate()
	{
		for (size_t i{ 0 }; i < m_vVertexArray.size()-4; i++) //The 4 final quads are generated apart.
		{
			if (i < m_verticesPosition.size() - 1)
			{
				m_vVertexArray[i][0].position = sf::Vector2f(m_verticesPosition[i].x * m_coef,
					m_verticesPosition[i].y * m_coef);
				m_vVertexArray[i][0].color = sf::Color(m_color.r, m_color.b, m_color.g, m_brightness);
				m_vVertexArray[i][1].position = sf::Vector2f(m_verticesPosition[i+1].x * m_coef,
					m_verticesPosition[i+1].y * m_coef);
				m_vVertexArray[i][1].color = sf::Color(m_color.r, m_color.b, m_color.g, m_brightness);

				m_vVertexArray[i][2].position = sf::Vector2f(m_verticesPosition[i+1].x * m_coef,
					(m_verticesPosition[i+1].y + m_radius) * m_coef);
				m_vVertexArray[i][2].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);
				m_vVertexArray[i][3].position = sf::Vector2f(m_verticesPosition[i].x * m_coef,
					(m_verticesPosition[i].y + m_radius) * m_coef);
				m_vVertexArray[i][3].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);
			}
			else if (i < 2 * m_verticesPosition.size() - 2)
			{
				size_t i_{ i - m_verticesPosition.size() + 1 };
				m_vVertexArray[i][0].position = sf::Vector2f(m_verticesPosition[i_].x * m_coef,
					m_verticesPosition[i_].y * m_coef);
				m_vVertexArray[i][0].color = sf::Color(m_color.r, m_color.b, m_color.g, m_brightness);
				m_vVertexArray[i][1].position = sf::Vector2f(m_verticesPosition[i_+1].x * m_coef,
					m_verticesPosition[i_ + 1].y * m_coef);
				m_vVertexArray[i][1].color = sf::Color(m_color.r, m_color.b, m_color.g, m_brightness);

				m_vVertexArray[i][2].position = sf::Vector2f(m_verticesPosition[i_ + 1].x * m_coef,
					(m_verticesPosition[i_ + 1].y - m_radius) * m_coef);
				m_vVertexArray[i][2].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);
				m_vVertexArray[i][3].position = sf::Vector2f(m_verticesPosition[i_].x * m_coef,
					(m_verticesPosition[i_].y - m_radius) * m_coef);
				m_vVertexArray[i][3].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);
			}
			else
				std::cout << "(Err) i : " << i << std::endl;
		}
		for (size_t i{ 0 }; i < 4; i++)
		{
			std::array<int, 4> arr_i{ 0, 0, m_verticesPosition.size() - 1, m_verticesPosition.size() - 1 };
			std::array<int, 4> arr_x{ -1, -1, 1, 1 };
			std::array<int, 4> arr_y{ -1, 1, -1, 1 };
			size_t i_{ m_vVertexArray.size() - (i + 1) };
			m_vVertexArray[i_][0].position = sf::Vector2f(m_verticesPosition[arr_i[i]].x * m_coef,
				m_verticesPosition[arr_i[i]].y * m_coef);
			m_vVertexArray[i_][0].color = sf::Color(m_color.r, m_color.b, m_color.g, m_brightness);

			m_vVertexArray[i_][1].position = sf::Vector2f((m_verticesPosition[arr_i[i]].x + m_radius*arr_x[i]) * m_coef,
				m_verticesPosition[arr_i[i]].y * m_coef);
			m_vVertexArray[i_][1].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);

			m_vVertexArray[i_][2].position = sf::Vector2f((m_verticesPosition[arr_i[i]].x + m_radius*arr_x[i]) * m_coef,
				(m_verticesPosition[arr_i[i]].y + m_radius*arr_y[i]) * m_coef);
			m_vVertexArray[i_][2].color = sf::Color(m_color.r, m_color.b, m_color.g, 0);

			m_vVertexArray[i_][3].position = sf::Vector2f(m_verticesPosition[arr_i[i]].x * m_coef,
				(m_verticesPosition[arr_i[i]].y + m_radius*arr_y[i]) * m_coef);
			m_vVertexArray[i_][3].color = sf::Color(m_color.r, m_color.b, m_color.g, m_intensity);
		}
	}
}

namespace DeltaEngine //TextureManager
{
	TextureManager::TextureManager(std::string jsonPath):m_jsonPath(jsonPath)
	{}

	TextureManager::~TextureManager()
	{
		for (auto texture : m_vTexture)
		{
			delete texture;
		}
	}

	sf::Texture* TextureManager::get_texture(unsigned int index)
	{
		return m_vTexture[index];
	}

	void TextureManager::init()
	{
		json j{ returnJson(m_jsonPath) };
		for (auto e : j["textures"])
		{
			sf::Texture* texture = new sf::Texture();
			if (!texture->loadFromFile(e))
			{
				std::cout << "Error : can't load " << e << "." << std::endl;
			}
			m_vTexture.push_back(texture);
		}
	}
}

namespace DeltaEngine //ShaderManager
{
	ShaderManager::ShaderManager(std::string jsonPath):m_jsonPath(jsonPath)
	{}

	ShaderManager::~ShaderManager()
	{
		for (auto* shader : m_vShader)
		{
			delete shader;
		}
	}

	sf::Shader* ShaderManager::get_shader(int index)
	{
		return m_vShader[index];
	}

	void ShaderManager::init()
	{
		json j{ returnJson(m_jsonPath) };
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
}
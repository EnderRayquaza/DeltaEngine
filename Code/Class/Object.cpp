#include "Object.hpp"

namespace DeltaEngine
{
	Object::Object():Identifiable()
	{}

	Object::Object(std::string jsonPath)
	{
		load(jsonPath);
	}

	void Object::load(std::string jsonPath)
	{
		json j{ returnJson(jsonPath) };
		m_idxBody = (uint)j["indexBody"];
		m_idxTexture = (uint)j["indexTexture"];
		m_idxShader = (uint)j["indexShader"];
		m_displayScreen = (int)j["displayScreen"];
		m_moveType = (moveType)j["moveType"];
		m_collisionType = (collisionType)j["collisionType"];
	}
}
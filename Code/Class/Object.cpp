#include "Object.hpp"

namespace DeltaEngine
{
	Object::Object():Identifiable()
	{}

	Object::Object(jsonStr jsonPath):m_jStr(jsonPath)
	{}

	void Object::load()
	{
		json j{ returnJson(m_jStr) };
		//Bodies
		for (auto& bodyPath : j["body"])
		{
			m_vBody.push_back(Body((jsonStr)bodyPath));
		}
		for (auto& lightPath : j["classicLight"])
		{
			m_vLight.push_back(ClassicLight((jsonStr)lightPath));
		}
		for (auto& lightPath : j["DirectionalLight"])
		{
			m_vLight.push_back(DirectionalLight((jsonStr)lightPath));
		}
		for (auto& lightPath : j["LinearLight"])
		{
			m_vLight.push_back(LinearLight((jsonStr)lightPath));
		}
	}

	Body& Object::get_body(uint index) noexcept
	{
		return m_vBody[index];
	}
}
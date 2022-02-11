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
		//Todo
	}
}
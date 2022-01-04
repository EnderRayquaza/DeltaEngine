#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Body.hpp"

namespace DeltaEngine
{
	class Object : public Identifiable
	{
	public:
		Object();
		Object(std::string jsonPath);
		~Object() = default;

		void load(std::string jsonPath);
	protected:
		uint m_idxBody, m_idxTexture, m_idxShader;
		std::vector<Light> m_vLight;
		int m_displayScreen;
		moveType m_moveType;
		collisionType m_collisionType;

	};
}

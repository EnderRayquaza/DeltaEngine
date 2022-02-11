#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Body.hpp"
#include "Game.hpp"
#include "Light.hpp"

namespace DeltaEngine
{
	class Object : public Identifiable
	{
	public:
		Object();
		Object(jsonStr jsonPath);
		~Object() = default;

		void load();
		Body& get_body(uint index) const noexcept;

		friend class Game;

	protected:
		jsonStr m_jStr;
		std::vector<Body> m_vBody;
		std::vector<Light> m_vLight;
	};
}

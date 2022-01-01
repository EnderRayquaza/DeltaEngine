#pragma once

#include "../config.hpp"
#include "Body.hpp"

namespace DeltaEngine
{
	class BodyManager : public sf::NonCopyable
	{
	public:
		BodyManager() = default;
		BodyManager(std::string jsonPath);
		~BodyManager() = default;

		Body* operator()(size_t i, size_t j, size_t k);

		void set_jsonPath(std::string jsonPath) noexcept;

		void load();
	private:
		std::string m_jsonPath;
		std::array<size_t, 4> m_size;
		std::vector<Body*> m_items;
	};
}

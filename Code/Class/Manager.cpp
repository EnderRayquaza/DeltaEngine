#include "Manager.hpp"

namespace DeltaEngine
{
	BodyManager::BodyManager(std::string jsonPath) :m_jsonPath(jsonPath)
	{}

	Body* BodyManager::operator()(size_t i, size_t j, size_t k)
	{
		size_t index{ i + m_size[0] * j + (m_size[0] * m_size[1]) * k };
		if (index >= m_size[3])
			return nullptr;
		return m_items[index];
	}

	void BodyManager::set_jsonPath(std::string jsonPath) noexcept
	{
		m_jsonPath = jsonPath;
	}

	void BodyManager::load()
	{
		json j{ returnJson(m_jsonPath) };
		m_size = { (size_t)j["size"][0], (size_t)j["size"][1], (size_t)j["size"][2],
			(size_t)j["size"][0] * (size_t)j["size"][1] * (size_t)j["size"][2] };
		for (auto& e : j["Body"])
		{
			Body* item = new Body{(std::string)e};
			m_items.push_back(item);
		}
	}
}
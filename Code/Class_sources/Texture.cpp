#pragma once

#include "../Class_headers/Texture.hpp"

namespace DeltaEngine
{
	Texture::Texture() :sf::Texture(), Identifiable()
	{}

	Texture::Texture(jsonStr path) :sf::Texture(), Identifiable(), Loadable(path)
	{}

	bool Texture::load()
	{
		json j{ returnJson(_path) };
		m_frameSize = Vec2i{ (int)j["frameSize"][0], (int)j["frameSize"][1] };
		loadFromFile((std::string)j["texturePath"]);
		return false;
	}

	Vec2i Texture::get_frameSize() const
	{
		return m_frameSize;
	}

	void Texture::set_frameSize(Vec2i size)
	{
		m_frameSize = size;
	}
}
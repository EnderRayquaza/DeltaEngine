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
		m_scale = Vec2f{ j["scale"][0], j["scale"][1]};
		loadFromFile((std::string)j["texturePath"]);
		return false;
	}

	Vec2i Texture::get_frameSize() const
	{
		return m_frameSize;
	}

	Vec2f Texture::get_scale() const
	{
		return m_scale;
	}

	void Texture::set_frameSize(Vec2i size)
	{
		m_frameSize = size;
	}

	void Texture::set_scale(Vec2f scale)
	{
		m_scale = scale;
	}
}
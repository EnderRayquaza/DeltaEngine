#pragma once

#include "../Class_headers/Texture.hpp"

namespace DeltaEngine
{
	Texture::Texture() :sf::Texture(), Identifiable()
	{}

	Texture::Texture(jsonStr path) :sf::Texture(), Identifiable(), Loadable(path)
	{}

	bool load()
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TODO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
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
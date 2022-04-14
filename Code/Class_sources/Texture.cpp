#pragma once

#include "../Class_headers/Texture.hpp"

namespace DeltaEngine
{
	Texture::Texture(Vec2i frameSize):sf::Texture(), m_frameSize{frameSize}
	{}

	Vec2i Texture::get_frameSize() const
	{
		return m_frameSize;
	}

	void Texture::set_frameSize(Vec2i size)
	{
		m_frameSize = size;
	}
}
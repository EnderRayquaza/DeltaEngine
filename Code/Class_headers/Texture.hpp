#pragma once

#include "../config.hpp"

namespace DeltaEngine
{
	class Texture : public sf::Texture
	{
		Texture() = default;
		Texture(Vec2i frameSize);
		~Texture() = default;

		Vec2i get_frameSize() const;
		void set_frameSize(Vec2i size);

	protected:
		Vec2i m_frameSize{ 0, 0 }; //The size of one Frame.
	};
}
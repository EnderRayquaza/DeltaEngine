#pragma once

#include "../config.hpp"
#include "Identifiable.hpp"
#include "Loadable.hpp"


namespace DeltaEngine
{
	class Texture : public sf::Texture, public Identifiable, public Loadable
	{
		Texture();
		Texture(jsonStr);
		~Texture() = default;

		bool load();

		Vec2i get_frameSize() const;
		void set_frameSize(Vec2i size);

	protected:
		Vec2i m_frameSize{ 0, 0 }; //The size of one Frame.
	};
}
#pragma once

#include "../config.hpp"
#include "Identifiable.hpp"
#include "Loadable.hpp"


namespace DeltaEngine
{
	class Texture : public sf::Texture, public Identifiable, public Loadable
	{
	public:
		Texture();
		Texture(jsonStr);
		~Texture() = default;

		bool load();

		Vec2i get_frameSize() const;
		Vec2f get_scale() const;
		void set_frameSize(Vec2i size);
		void set_scale(Vec2f scale);

	protected:
		Vec2i m_frameSize{ 0, 0 }; //The size of one Frame.
		Vec2f m_scale{ 1, 1 }; //The scale that the texture will be displayed on the screen.
	};
}
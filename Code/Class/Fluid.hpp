#pragma once

#include "../config.hpp"
#include "../basic.hpp"
#include "Body.hpp"

namespace DeltaEngine
{
	class Fluid : public Identifiable
	{
	public:
		Fluid(Vertex pos, Shape shape, ulong viscosity, ulong density, Vec2f force);
		~Fluid() = default;

		void set_absForce(bool);

		bool BodyAlreadyIn(Body&);
		bool BodyMustBeIn(Body&);
		bool BodyMustBeOut(Body&);
		void add_body(Body&);
		void remove_body(Body&);

		friend class Area;
	protected:
		Vertex m_pos;
		Shape m_shape;
		ulong m_viscosity, m_density;
		bool m_absoluteForce{true};
		Vec2f m_force;
		std::vector<Body> m_vBodies;
		uint m_displayScreen;
	};
}

//Body.hpp
#pragma once

#include "../DeltaEngine.hpp"

namespace DeltaEngine
{
	struct AABB;
	struct Vertex;
	struct Shape;
	class Vector;
	class Body;

	class Body
	{
	public:
		Body();
		Body(Vector, Shape, double, double, double);
		~Body();

		friend class Contact;
		friend class Collision;

		Vector* get_position() const;
		double get_angle() const;

		void set_position(Vector& pos);
		void set_angle(double angle);

		void move(double time);
		void applyForce(Vector& force);
		void resetForces();
		void applyImpulse(Vector& impulse);
		void resetImpulses();

	protected:
		static std::vector<int> listId;
		int m_id;
		Vector* m_position;
		double m_angle;
		Vector* m_currentForce;
		Vector* m_currentImpulse;
		Vector* m_currentVelocity;
		AABB* m_aabb;
		Shape* m_shape;
		double m_mass;
		double m_density;
		double m_friction;
		double m_restitution;
	};
}

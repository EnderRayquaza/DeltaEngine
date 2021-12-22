#pragma once

#include "../DeltaEngine.hpp"

namespace DeltaEngine
{
	class Contact;
	class Collision;

	bool operator==(const Contact&, const Contact&);
	bool operator==(const Collision&, const Collision&);

	class Contact
	{
	public:
		Contact(Body&, Body&);
		~Contact() = default;

		int get_id() const noexcept;
		Body& get_bodyA() const noexcept;
		Body& get_bodyB() const noexcept;

		bool isThereContact();
		void begin();
		void end();
		bool isEgal(const Contact&) const;

	protected:
		static std::vector<int> listId;
		int m_id;
		Body& m_bodyA,& m_bodyB;
	};

	class Collision
	{
	public:
		Collision(Body&, Body&);
		Collision(Contact&);
		~Collision() = default;

		int get_id() const noexcept;
		Body& get_bodyA() const noexcept;
		Body& get_bodyB() const noexcept;

		bool isThereCollision();
		void execute();
		void begin();
		void end();
		bool isEgal(const Collision&) const;

	protected:
		static std::vector<int> listId;
		int m_id;
		Body& m_bodyA, & m_bodyB;
	};
}


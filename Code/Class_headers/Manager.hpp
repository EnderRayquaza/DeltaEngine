#pragma once

#include "../config.hpp"

namespace DeltaEngine
{
	template <class T>
	class Manager
	{
	public:
		Manager() = default;
		~Manager() = default;

		void addItem(T item); //Adds an Item to the manager. The item is moved in the manager so the arg will be empty.
		T& operator[](uint index); //Returns an Item by an index.

		void loadItem(); //Executes the fonction load() for all Loadable items.

	protected:
		std::vector<T> m_items{};
	};
}
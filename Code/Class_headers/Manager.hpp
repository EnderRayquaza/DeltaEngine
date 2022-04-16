#pragma once

#include "../config.hpp"
#include "../Class_headers/Identifiable.hpp"

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

		size_t size() const;

		void loadItem(); //Executes the fonction load() for all Loadable items.

	protected:
		std::vector<T> m_items{};
	};

	template <typename T>
	bool inManager(Manager<T>&, T&);

	template <class T>
	bool inManager(Manager<T>&, Id);
}
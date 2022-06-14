#pragma once

#include "../config.hpp"
#include "Identifiable.hpp"
#include "Loadable.hpp"

namespace DeltaEngine
{
	template <class T>
	class Manager
	{
	public:
		Manager() = default;
		~Manager() = default;

		//template <class T> //Adds an Item to the manager. The item is moved in the manager so the arg will be empty.
		void addItem(T item)
		{
			m_items.push_back(std::move(item));
		}


		//template <class T> //Returns an Item by an index.
		T& operator[](uint index)
		{
			return m_items[index];
		}

		//template <class T2> //Returns an Item by an Id. /!\ T must be a derived class of Identifiable.
		T& operator[](Id id)
		{
			for (T& item : m_items)
			{
				if (item._id == id)
				{
					return item;
				}
			}
		}

		//template <class T>
		size_t size() const
		{
			return m_items.size();
		}

		//template <class T> //Executes the fonction load() for all Loadable items.
		void loadItem()
		{
			for (T& item : m_items)
			{
				try
				{
					item.load();
				}
				catch (std::exception const& excp)
				{
					std::cout << "Error : " << excp.what() << std::endl;
				}
			}
		} 

	protected:
		std::vector<T> m_items{};
	};

	template <typename T>
	bool inManager(Manager<T>&, T&);

	template <class T>
	bool inManager(Manager<T>&, Id);
}
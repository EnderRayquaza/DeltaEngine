#include "../Class_headers/Manager.hpp"

namespace DeltaEngine
{
	template <class T>
	void Manager<T>::addItem(T item)
	{
		m_items.push_back(std::move(item));
	}

	template <class T>
	T& Manager<T>::operator[](uint index)
	{
		return m_items[index];
	}

	template <class T>
	size_t Manager<T>::size() const
	{
		return m_items.size();
	}

	template <class T>
	void Manager<T>::loadItem()
	{
		for (auto& item : m_items)
		{
			try
			{
				item.load();
			}
			catch (std::exception const& excp)
			{
				std::cout << typeid(excp) << "Error : " << excp.what() << std::endl;
			}
		}
	}

	template <typename T>
	bool inManager(Manager<T>& mng, T& t)
	{
		for (T& elem : mng)
		{
			if (&elem == &t)
			{
				return true;
			}
		}
		return false;
	}

	template <class T>
	bool inManager(Manager<T>& mng, Id id)
	{
		for (T& elem : mng)
		{
			if (elem.get_id() == id)
			{
				return true;
			}
		}
		return false;
	}
}
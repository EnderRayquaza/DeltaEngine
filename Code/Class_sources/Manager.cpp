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
}
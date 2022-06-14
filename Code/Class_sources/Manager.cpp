#include "../Class_headers/Manager.hpp"

namespace DeltaEngine
{
	template <class T>
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
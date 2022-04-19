#include "../Class_headers/Animation.hpp"

namespace DeltaEngine
{
	Animation::Animation(jsonStr path) :Loadable(path)
	{}

	bool Animation::load()
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TODO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		return false;
	}

	size_t Animation::size()
	{
		return _vCoord.size();
	}
}
#include "../Class_headers/Animation.hpp"

namespace DeltaEngine
{
	Animation::Animation(jsonStr path) :Loadable(path)
	{}

	bool Animation::load()
	{
		json j{ returnJson(_path) };
		for (auto& coord : j["coords"])
		{
			_vCoord.push_back(Vec2i{ (int)coord[0], (int)coord[1] });
		}
		return false;
	}

	size_t Animation::size()
	{
		return _vCoord.size();
	}
}
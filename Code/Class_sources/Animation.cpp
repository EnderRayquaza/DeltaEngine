#include "../Class_headers/Animation.hpp"

namespace DeltaEngine
{
	Animation::Animation(jsonStr path) :Loadable(path)
	{}

	Animation::Animation(json js)
	{
		_j = js;
	}

	bool Animation::load()
	{
		_j = returnJson(_path);
		return loadByJson();
	}

	bool Animation::loadByJson()
	{
		_time = sf::milliseconds((uint)_j["time"]);
		for (auto& coord : _j["coords"])
		{
			_vCoord.push_back(Vec2i{ (int)coord[0], (int)coord[1] });
		}
		return true;
	}

	size_t Animation::size()
	{
		return _vCoord.size();
	}
}
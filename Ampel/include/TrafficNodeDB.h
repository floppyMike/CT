#pragma once

#include "Includes.h"
#include "RoadsDB.h"

using TrafficNodes = std::vector<std::unique_ptr<TrafficNode>>;


auto operator<<(sdl::Renderer &r, const TrafficNodes &ls) -> sdl::Renderer &
{
	for (const auto &l : ls) r << *l;
	return r;
}

/*
template<typename T>
class TrafficNodeOnMouse : public crtp<T, TrafficNodeOnMouse>
{
public:
	auto trafficNodeOnMouse()
	{
		const auto mousePos = mousePosition();

		auto select = std::find_if(this->_().rbegin(), this->_().rend(),
								   [&mousePos](const auto &n) { return sdl::collision(n->shape(), mousePos); });

		return select;
	}
};

template<typename T>
class TrafficNodeDeleter : public crtp<T, TrafficNodeDeleter>
{
public:
	void removeNode(DNode *node)
	{
		for (auto &i : this->_()) i->nodes.erase(std::remove(i->nodes.begin(), i->nodes.end(), node), i->nodes.end());
	}
};
*/
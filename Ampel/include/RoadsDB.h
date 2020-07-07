#pragma once

#include "Includes.h"
#include "Line.h"


struct TrafficNode
{
	std::vector<Node*> nodes;
	std::vector<Link*> lines;
};


template<typename T>
class TraffNodeOnMouse : public crtp<T, TraffNodeOnMouse>
{
public:
	bool isTraffNodeOnMouse()
	{
		return sdl::collision(this->_().shape(), sdl::mouse_position());
	}
};

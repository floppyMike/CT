#pragma once

#include "Includes.h"
#include "TrafficConnector.h"
#include "Line.h"


template<template<typename> class... Func>
struct TrafficNode : TrafficConnector, Func<TrafficNode<Func...>>...
{
	using TrafficConnector::TrafficConnector;

	std::vector<DNode*> nodes;
	std::vector<DLink*> lines;
};


template<typename T>
class TraffNodeOnMouse : public crtp<T, TraffNodeOnMouse>
{
public:
	bool isTraffNodeOnMouse()
	{
		return sdl::collision(this->_().shape(), mousePosition());
	}
};


using DTrafficNode = TrafficNode<TraffNodeOnMouse>;
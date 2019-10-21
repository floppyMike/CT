#pragma once

#include "Includes.h"
#include "TrafficConnector.h"


template<template<typename> class... Func>
class TrafficNodeDB : std::vector<std::unique_ptr<DTrafficNode>>, public Func<TrafficNodeDB<Func...>>...
{
	using baseV = std::vector<std::unique_ptr<DTrafficNode>>;

public:
	using iterator = baseV::iterator;
	using reverse_iterator = baseV::reverse_iterator;

	TrafficNodeDB() = default;

	using baseV::begin;
	using baseV::rbegin;
	using baseV::end;
	using baseV::rend;

	using baseV::emplace_back;
	using baseV::erase;
	using baseV::size;
};


template<typename T>
class TrafficNodeOnMouse : public crtp<T, TrafficNodeOnMouse>
{
public:
	auto trafficNodeOnMouse()
	{
		const auto mousePos = mousePosition();

		auto select = std::find_if(this->_().rbegin(), this->_().rend(), [&mousePos](const auto& n)
			{ return sdl::collision(n->shape(), mousePos); });

		return select;
	}
};


template<typename T>
class TrafficNodeDeleter : public crtp<T, TrafficNodeDeleter>
{
public:
	void removeNode(DNode* node)
	{
		for (auto& i : this->_())
			i->nodes.erase(std::remove(i->nodes.begin(), i->nodes.end(), node), i->nodes.end());
	}
};

using DTrafficNodeDB = TrafficNodeDB<TrafficNodeOnMouse, TrafficNodeDeleter>;
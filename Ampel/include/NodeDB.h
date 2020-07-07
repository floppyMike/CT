#pragma once

#include "Includes.h"
#include "Node.h"

template<template<typename> class... Func>
class NodeDB : std::vector<std::unique_ptr<DNode>>, public Func<NodeDB<Func...>>...
{
	using baseV = std::vector<std::unique_ptr<DNode>>;

public:
	NodeDB() = default;

	using baseV::begin;
	using baseV::rbegin;
	using baseV::end;
	using baseV::rend;

	using baseV::emplace_back;
	using baseV::erase;
};


template<typename T>
class NodesOnMouse : public crtp<T, NodesOnMouse>
{
public:
	auto nodeOnMouse()
	{
		const auto mousePos = mousePosition();

		auto select = std::find_if(this->_().rbegin(), this->_().rend(), [&mousePos](const auto& n)
			{ return sdl::collision(n->shape(), mousePos); });

		return select;
	}
};

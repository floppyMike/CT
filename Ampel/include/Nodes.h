#pragma once

#include "Includes.h"
#include "Node.h"

class Nodes
{
public:
	Nodes() = default;

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

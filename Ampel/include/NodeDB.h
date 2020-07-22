#pragma once

#include "Includes.h"
#include "Node.h"

using Nodes = std::vector<std::unique_ptr<Node>>;

auto operator<<(sdl::Renderer &r, const Nodes &ns) noexcept -> sdl::Renderer &
{
	r.color(sdl::BLACK);
	for (const auto &n : ns) r << *n;
	return r;
}

/*
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
*/
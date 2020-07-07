#pragma once

#include "Includes.h"

/*
class Node
{
public:
	static constexpr mth::Dim<int> DIM = mth::Dim(5, 5);

	explicit Node(const mth::Point<int> &p)
		: Node(p.x, p.y)
	{
	}

	Node(int x, int y)
		: m_rect({ x, y, DIM.w, DIM.h })
	{
	}

	void						 translate(const mth::Point<int> &p) noexcept { m_rect.shape().translate(p); }
	[[nodiscard]] constexpr auto shape() const noexcept -> const auto & { return m_rect; }

private:
	sdl::RectFrame m_rect;
};
*/

static constexpr mth::Dim<int> NODE_DIM = { 5, 5 };

using Node = sdl::RectFrame;

/*
template<typename T>
class NodeOnMouse : public crtp<T, NodeOnMouse>
{
public:
	bool isNodeOnMouse() const { return sdl::collision(this->_().shape(), mousePosition()); }
};
*/

#pragma once

#include "Includes.h"

class Node
{
public:
	Node(sdl::Renderer* r, const sdl::Rect<int, int>& s)
		: m_rect(r)
	{
		m_rect.shape(s);
	}

	bool isInside(const sdl::Point<int>& p)
	{
		return sdl::collision(p, m_rect.shape());
	}

private:
	sdl::RectDraw<> m_rect;
};

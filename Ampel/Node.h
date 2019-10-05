#pragma once

#include "Includes.h"

class Node
{
public:
	static constexpr sdl::Dim<int> DIM = sdl::Dim(5, 5);

	Node(sdl::Renderer* r, const sdl::Point<int>& p)
		: m_rect(r)
	{
		m_rect.shape({ p, DIM });
	}

	void translate(const sdl::Point<int>& p) noexcept
	{
		m_rect.translate(p);
	}

	constexpr const auto& shape() const noexcept
	{
		return m_rect.shape();
	}

	void draw()
	{
		m_rect.renderer()->setColor(sdl::BLACK);
		m_rect.drawFilled();
	}

protected:
	sdl::RectDraw<> m_rect;
};


class NodeStart : Node
{
public:
	using Node::Node;

	void draw()
	{
		m_rect.renderer()->setColor(sdl::RED);
		m_rect.drawFilled();
	}

	using Node::shape;
	using Node::translate;

private:
	std::vector<Node*> m_path;
};

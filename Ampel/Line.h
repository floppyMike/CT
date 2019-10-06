#pragma once

#include "Includes.h"
#include "Node.h"


class Link
{
public:
	Link(sdl::Renderer* r, const sdl::Line<int>& l)
		: m_line(r)
	{
		m_line.shape(l);
	}

	auto& fromNode(Node* const ptr) { m_nodes.first = ptr; return *this; }
	auto& toNode(Node* const ptr) { m_nodes.second = ptr; return *this; }

	bool compareWith(const Node* const n) const noexcept
	{
		return n == m_nodes.first || n == m_nodes.second;
	}

	const auto& shape() const noexcept { return m_line.shape(); }
	auto& shape(const sdl::Line<int>& l) noexcept { m_line.shape(l); return *this; }

	void draw() const
	{
		m_line.draw();
	}

private:
	std::pair<Node*, Node*> m_nodes;
	sdl::LineDraw<> m_line;
};

#pragma once

#include "Includes.h"
#include "Node.h"

class Link
{
public:
	explicit Link(const mth::Line<int> &l)
		: m_line(l)
	{
	}

	auto fromNode(Node *const ptr) noexcept -> auto &
	{
		m_nodes.first = ptr;
		return *this;
	}
	auto fromNode() noexcept -> auto * { return m_nodes.first; }

	auto toNode(Node *const ptr) noexcept -> auto &
	{
		m_nodes.second = ptr;
		return *this;
	}
	auto toNode() noexcept -> auto & { return m_nodes.second; }

	[[nodiscard]] auto shape() const noexcept -> const auto & { return m_line.shape(); }
	auto shape(const mth::Line<int> &l) noexcept -> auto &
	{
		m_line.shape(l);
		return *this;
	}

	void draw(sdl::Renderer *r) { m_line.draw(r).line(); }

private:
	std::pair<Node *, Node *>	   m_nodes;
	sdl::ELineFrame<sdl::Drawable> m_line;
};

template<typename T>
class LinkComparison : public crtp<T, LinkComparison>
{
public:
	bool compareWith(const Node *const n) noexcept { return n == this->_().fromNode() || n == this->_().toNode(); }
};

// using DLink = Link<LinkComparison>;

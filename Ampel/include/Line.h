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

	explicit Link(Link *l) { link_from(*l); }

	auto from_node(Node *const ptr) noexcept -> void
	{
		m_nodes.first = ptr;
		m_line.shape().pos1(ptr->shape().w / 2 + ptr->shape().x, ptr->shape().h / 2 + ptr->shape().y);
	}
	[[nodiscard]] auto from_node() const noexcept { return m_nodes.first; }

	auto to_node(Node *const ptr) noexcept
	{
		m_nodes.second = ptr;
		m_line.shape().pos2(ptr->shape().w / 2 + ptr->shape().x, ptr->shape().h / 2 + ptr->shape().y);
	}
	[[nodiscard]] auto to_node() const noexcept { return m_nodes.second; }

	auto link_from(Link &l) noexcept -> void { from_node(l.m_nodes.first); }

	auto move_endpoint(const mth::Point<int> &p)
	{
		assert(m_nodes.second == nullptr && "Link shouldn't be set.");
		m_line.shape().pos2(p);
	}

	auto uses_node(const Node *const ptr) const noexcept { return ptr == m_nodes.first || ptr == m_nodes.second; }

	[[nodiscard]] auto shape() const noexcept -> const auto & { return m_line.shape(); }

	auto operator==(const Link &l) const noexcept { return l.m_nodes != m_nodes; }

	friend auto operator<<(sdl::Renderer &r, const Link &l) -> sdl::Renderer &
	{
		l.m_line.draw(&r).line();
		return r;
	}

private:
	std::pair<Node *, Node *>	   m_nodes = { nullptr, nullptr };
	sdl::ELineFrame<sdl::Drawable> m_line;
};

/*
struct Link
{
	std::pair<Node *, Node *>	   nodes;
	sdl::ELineFrame<sdl::Drawable> line;
};
*/

auto operator<<(sdl::Renderer &r, const Link &l) -> sdl::Renderer &
{
	l.line.draw(&r).line();
	return r;
}

/*
template<typename T>
class LinkComparison : public crtp<T, LinkComparison>
{
public:
	bool compareWith(const DNode *const n) noexcept { return n == this->_().fromNode() || n == this->_().toNode(); }
};
*/
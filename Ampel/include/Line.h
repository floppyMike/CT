#pragma once

#include "CustomLibrary/Line.h"
#include "Includes.h"
#include "Node.h"

class Link
{
public:
	explicit Link(const mth::Line<int> &l)
		: m_line(l)
	{
	}

	auto from_node(Node *const ptr) noexcept
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
	auto			   to_node(const mth::Point<int> &p) noexcept { m_line.shape().pos2(p); }

	auto uses_node(Node *const ptr) const noexcept { return ptr == m_nodes.first || ptr == m_nodes.second; }

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
template<typename T>
class LinkComparison : public crtp<T, LinkComparison>
{
public:
	bool compareWith(const DNode *const n) noexcept { return n == this->_().fromNode() || n == this->_().toNode(); }
};
*/
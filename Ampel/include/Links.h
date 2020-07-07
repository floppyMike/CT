#pragma once

#include "Includes.h"
#include "Node.h"
#include "TrafficLight.h"

struct Link
{
	Link() noexcept = default;

	explicit Link(TrafficLight *s) noexcept
		: start(s)
	{
	}

	TrafficLight *		start = nullptr;
	std::vector<Node *> path;
	TrafficLight *		end = nullptr;
};

class Links
{
public:
	Links() noexcept = default;

	void push_path(TrafficLight *start) { m_links.emplace_back(start); }
	void push_link(const mth::Point<int> &p) { m_gph.push(mth::Line<int>(p, p)); }
	void mov_loose_link(const mth::Point<int> &p) { m_gph.template data<mth::Line<int>>().back().pos2(p); }

	void attach_loose_link(Node *n)
	{
		m_gph.template data<mth::Line<int>>().back().pos2(n->shape().x + n->shape().w / 2,
														  n->shape().y + n->shape().h / 2);
		m_links.back().path.emplace_back(n);
	}

	void finish_loose_link(TrafficLight *end) { m_links.back().end = end; }

private:
	std::vector<Link>				m_links;
	sdl::MultiShape<mth::Line<int>> m_gph;
	std::vector<Link>::iterator		m_iter = m_links.begin();
};

/*
template<typename T>
class LinkRemover : public crtp<T, LinkRemover>
{
public:
	void eraseLinesToNode(DNode *ptr)
	{
		this->_().erase(
			std::remove_if(this->_().begin(), this->_().end(), [&ptr](const auto &n) { return n->compareWith(ptr); }),
			this->_().end());
	}
};

template<typename T>
class LinkFinder : public crtp<T, LinkFinder>
{
public:
	auto findSameLink(DNode *from, DNode *to)
	{
		return std::find_if(this->_().begin(), this->_().end(),
							[&from, &to](const auto &l) { return l->compareWith(from) && l->compareWith(to); });
	}
};
*/

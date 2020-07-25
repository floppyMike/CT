#pragma once

#include "Includes.h"
#include "Line.h"

using Links = std::vector<std::unique_ptr<Link>>;

template<typename Iter>
auto find_link(Iter beg, Iter end, Node *from,
			   Node *to) requires std::same_as<typename std::iterator_traits<Iter>::value_type, std::unique_ptr<Link>>
{
	return std::find_if(beg, end,
				 [from, to](const std::unique_ptr<Link> &l) { return l->uses_node(from) && l->uses_node(to); });
}

template<typename Arr>
auto range_collided(const Arr &arr) requires std::same_as<decltype(arr[0]), Link*>
{
	
}

auto operator<<(sdl::Renderer &r, const Links &ls) noexcept -> sdl::Renderer &
{
	for (const auto &l : ls) r << *l;
	return r;
}

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
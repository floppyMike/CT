#pragma once

#include "Includes.h"
#include "Line.h"

template<template<typename> class... Func>
class LinkDB : std::vector<std::unique_ptr<DLink>>, public Func<LinkDB<Func...>>...
{
	using baseV = std::vector<std::unique_ptr<DLink>>;

public:
	LinkDB() = default;

	using baseV::begin;
	using baseV::rbegin;
	using baseV::end;
	using baseV::rend;

	using baseV::emplace_back;
	using baseV::pop_back;
	using baseV::erase;
};


template<typename T>
class LinkRemover : public crtp<T, LinkRemover>
{
public:
	void eraseLinesToNode(DNode* ptr)
	{
		this->_().erase(std::remove_if(this->_().begin(), this->_().end(),
			[&ptr](const auto& n) { return n->compareWith(ptr); }), this->_().end());
	}
};


template<typename T>
class LinkFinder : public crtp<T, LinkFinder>
{
public:
	auto findSameLink(DNode* from, DNode* to)
	{
		return std::find_if(this->_().begin(), this->_().end(),
			[&from, &to](const auto& l) { return l->compareWith(from) && l->compareWith(to); });
	}
};

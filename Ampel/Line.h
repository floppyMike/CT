#pragma once

#include "Includes.h"
#include "Node.h"


template<template<typename> class... Func>
class Link : public Func<Link<Func...>>...
{
public:
	Link(sdl::Renderer* r, const sdl::Line<int>& l)
		: m_line(r)
	{
		m_line.shape(l);
	}

	auto& fromNode(DNode* const ptr) noexcept { m_nodes.first = ptr; return *this; }
	auto* fromNode() noexcept { return m_nodes.first; }

	auto& toNode(DNode* const ptr) noexcept { m_nodes.second = ptr; return *this; }
	auto& toNode() noexcept { return m_nodes.second; }

	const auto& shape() const noexcept { return m_line.shape(); }
	auto& shape(const sdl::Line<int>& l) noexcept { m_line.shape(l); return *this; }

	void draw() const
	{
		m_line.draw();
	}

private:
	std::pair<DNode*, DNode*> m_nodes;
	sdl::LineDraw<> m_line;
};


template<typename T>
class LinkComparison : public crtp<T, LinkComparison>
{
public:
	bool compareWith(const DNode* const n) noexcept
	{
		return n == this->_().fromNode() || n == this->_().toNode();
	}
};


using DLink = Link<LinkComparison>;

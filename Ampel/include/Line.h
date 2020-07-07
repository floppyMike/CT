#pragma once

#include "CustomLibrary/SDL/Drawable.h"
#include "CustomLibrary/SDL/Geometry.h"
#include "Includes.h"
#include "Node.h"


template<template<typename> class... Func>
class Link : public Func<Link<Func...>>...
{
public:
	Link(sdl::Renderer* r, const mth::Line<int>& l)
		: m_r(r)
	{
		m_line.shape(l);
	}

	auto& fromNode(DNode* const ptr) noexcept { m_nodes.first = ptr; return *this; }
	auto* fromNode() noexcept { return m_nodes.first; }

	auto& toNode(DNode* const ptr) noexcept { m_nodes.second = ptr; return *this; }
	auto& toNode() noexcept { return m_nodes.second; }

	const auto& shape() const noexcept { return m_line.shape(); }
	auto& shape(const mth::Line<int>& l) noexcept { m_line.shape(l); return *this; }

	void draw()
	{
		m_line.draw(m_r).line();
	}

private:
	sdl::Renderer *m_r;
	std::pair<DNode*, DNode*> m_nodes;
	sdl::ELineFrame<sdl::Drawable> m_line;
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

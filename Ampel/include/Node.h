#pragma once

#include "CustomLibrary/SDL/Drawable.h"
#include "CustomLibrary/SDL/Geometry.h"
#include "Includes.h"


template<template<typename> class... Func>
class Node : public Func<Node<Func...>>...
{
public:
	static constexpr mth::Dim<int> DIM = mth::Dim(5, 5);

	Node(sdl::Renderer* r, const mth::Point<int>& p)
		: m_r(r)
	{
		m_rect.shape({ p, DIM });
	}

	void translate(const mth::Point<int>& p) noexcept
	{
		m_rect.shape().translate(p);
	}

	constexpr const auto& shape() const noexcept
	{
		return m_rect.shape();
	}

	void draw()
	{
		m_rect.draw(m_r).filled_rect();
	}

private:
	sdl::Renderer *m_r;
	sdl::ERectFrame<sdl::Drawable> m_rect;
};


template<typename T>
class NodeOnMouse : public crtp<T, NodeOnMouse>
{
public:
	bool isNodeOnMouse() const
	{
		return sdl::collision(this->_().shape(), mousePosition());
	}
};


using DNode = Node<NodeOnMouse>;



//class NodeStart : Node
//{
//public:
//	using Node::Node;
//
//	void draw()
//	{
//		m_rect.renderer()->setColor(sdl::RED);
//		m_rect.drawFilled();
//	}
//
//	using Node::shape;
//	using Node::translate;
//
//private:
//	std::vector<Node*> m_path;
//};

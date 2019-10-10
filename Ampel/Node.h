#pragma once

#include "Includes.h"


template<template<typename> class... Func>
class Node : public Func<Node<Func...>>...
{
public:
	static constexpr sdl::Dim<int> DIM = sdl::Dim(5, 5);

	Node(sdl::Renderer* r, const sdl::Point<int>& p)
		: m_rect(r)
	{
		m_rect.shape({ p, DIM });
	}

	void translate(const sdl::Point<int>& p) noexcept
	{
		m_rect.translate(p);
	}

	constexpr const auto& shape() const noexcept
	{
		return m_rect.shape();
	}

	void draw()
	{
		m_rect.drawFilled();
	}

private:
	sdl::RectDraw<> m_rect;
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

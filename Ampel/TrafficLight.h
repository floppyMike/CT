#pragma once

#include "Includes.h"
#include "LightBox.h"
#include "LightBody.h"

class TrafficLight
{
public:
	TrafficLight(sdl::Renderer* r, const sdl::Point<int>& pos, int width, std::initializer_list<Light::Color>&& colors)
		: m_box(r, pos, width, std::move(colors))
		, m_body(r, { pos.x, pos.y + m_box.shape().h - 1 }, width)
	{
	}

	auto& flipLight(size_t idx) noexcept
	{
		m_box.flipLight(idx);
		return *this;
	}

	auto& change(size_t idx, bool s) noexcept
	{
		m_box.change(idx, s);
		return *this;
	}

	virtual void draw()
	{
		m_body.draw();
		m_box.draw();
	}

protected:
	LightBox m_box;
	LightBody m_body;
};
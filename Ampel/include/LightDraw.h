#pragma once

#include "Includes.h"
#include "TrafficLights.h"

class LightDraw
{
public:
	LightDraw(sdl::Renderer *r) noexcept
		: m_r(r)
	{
	}

	void draw(const TrafficLights &ts)
	{
		for (const auto &i : ts) { draw(i); }
	}

	void draw(const TrafficLight &t)
	{
		m_r->option().color(sdl::BLACK);
		t.veh_light().shape().draw(m_r).rect();
		t.ped_light().shape().draw(m_r).rect();
		t.node_in().shape().draw(m_r).filled_rect();

		m_r->option().color(sdl::RED);
		t.node_out().shape().draw(m_r).filled_rect();
	}

private:
	sdl::Renderer *m_r;
};

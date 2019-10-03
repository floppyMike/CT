#pragma once

#include "TrafficLight.h"

class RoadLights
{
	static constexpr int WIDTH = 21;

public:
	RoadLights(sdl::Renderer* r, const sdl::Point<int>& pos)
		: m_veh(r, pos, WIDTH, { Light::RED, Light::YELLOW, Light::GREEN })
		, m_ped(r, { pos.x + WIDTH + 5, pos.y }, WIDTH, { Light::RED, Light::GREEN })
		, m_dot(r)
	{
		m_dot.shape({ pos.x + WIDTH + 3, pos.y + m_veh.shape().y + 10, 5, 5 });
	}

	auto& translate(const sdl::Point<int>& delta)
	{
		m_veh.translate(delta);
		m_ped.translate(delta);
		return *this;
	}

	void draw()
	{
		m_dot.renderer()->setColor({ 0, 0, 0, 0xFF });
		m_veh.draw();
		m_ped.draw();
		m_dot.drawFilled();
	}

private:
	LightBox m_veh;
	LightBox m_ped;

	sdl::RectDraw<> m_dot;
};

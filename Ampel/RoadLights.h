#pragma once

#include "LightBox.h"
#include "Node.h"

class RoadLights
{
public:
	static constexpr int WIDTH = 21;
	static constexpr int DIS = 5;
	static constexpr int TOTAL_WIDTH = (WIDTH << 1) + DIS;

	RoadLights() = delete;

	RoadLights(sdl::Renderer* r, const sdl::Point<int>& pos)
		: m_veh(r, pos, WIDTH, { Light::RED, Light::YELLOW, Light::GREEN })
		, m_ped(r, { pos.x + WIDTH + DIS, pos.y }, WIDTH, { Light::RED, Light::GREEN })
	{
	}

	sdl::Rect<int, int> shape() const noexcept
	{
		return { m_veh.shape().pos(), { TOTAL_WIDTH, m_veh.shape().h } };
	}

	void translate(const sdl::Point<int>& delta)
	{
		m_veh.translate(delta);
		m_ped.translate(delta);
	}

	constexpr auto pos() const noexcept
	{
		return m_veh.shape().pos();
	}

	void draw()
	{
		m_veh.draw();
		m_ped.draw();
	}

protected:
	LightBox m_veh;
	LightBox m_ped;
};

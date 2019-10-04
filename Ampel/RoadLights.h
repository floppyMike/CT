#pragma once

#include "TrafficLight.h"

class RoadLights
{
public:
	static constexpr int WIDTH = 21;
	static constexpr int TOTAL_WIDTH = (WIDTH << 1) + 5;
	static constexpr sdl::Dim<int> IN_OUT_SHAPE = sdl::Dim(5, 5);
	static constexpr int IN_OUT_DIS = 10;

	RoadLights(sdl::Renderer* r, const sdl::Point<int>& pos)
		: m_veh(r, pos, WIDTH, { Light::RED, Light::YELLOW, Light::GREEN })
		, m_ped(r, { pos.x + WIDTH + 5, pos.y }, WIDTH, { Light::RED, Light::GREEN })
		, m_out(r)
		, m_in(r)
	{
		const auto yPos = pos.y + m_veh.shape().h + IN_OUT_DIS;
		m_out.shape({ pos.x + (WIDTH >> 1), yPos, IN_OUT_SHAPE.w, IN_OUT_SHAPE.h });
		m_in.shape({ pos.x + (WIDTH >> 1) + WIDTH, yPos, IN_OUT_SHAPE.w, IN_OUT_SHAPE.h });
	}

	bool isInOut(const sdl::Point<int>& r) noexcept
	{
		return sdl::collision(r, m_out.shape());
	}
	bool isInIn(const sdl::Point<int>& r) noexcept
	{
		return sdl::collision(r, m_in.shape());
	}

	sdl::Point<int> middle() const noexcept
	{
		return { m_veh.shape().x + (TOTAL_WIDTH >> 1), 
			m_veh.shape().y + (m_veh.shape().h + IN_OUT_DIS + IN_OUT_SHAPE.h >> 1) };
	}

	sdl::Rect<int, int> shape() const noexcept
	{
		return { { m_veh.shape().pos() }, { TOTAL_WIDTH, m_veh.shape().h + IN_OUT_DIS + IN_OUT_SHAPE.h } };
	}

	auto& translate(const sdl::Point<int>& delta)
	{
		m_veh.translate(delta);
		m_ped.translate(delta);
		m_out.translate(delta);
		m_in.translate(delta);
		return *this;
	}

	constexpr auto pos() const noexcept
	{
		return m_veh.shape().pos();
	}

	void draw()
	{
		m_out.renderer()->setColor({ 0, 0, 0, 0xFF });
		m_veh.draw();
		m_ped.draw();
		m_out.drawFilled();

		m_in.renderer()->setColor({ 0xFF, 0, 0, 0xFF });
		m_in.drawFilled();
	}

private:
	LightBox m_veh;
	LightBox m_ped;

	sdl::RectDraw<> m_out;
	sdl::RectDraw<> m_in;
};

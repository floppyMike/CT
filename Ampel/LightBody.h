#pragma once

#include "Includes.h"

class LightBody
{
	static constexpr int FLOOR = 450;

public:
	LightBody(sdl::Renderer* r, const mth::Point<int>& coord, int width)
		: m_pole(r)
		, m_foot(r)
	{
		const auto poleWidth = width >> 2;
		const auto footHight = width >> 3;

		m_pole.shape({ coord.x + ((width - poleWidth) >> 1), coord.y, poleWidth, FLOOR - coord.y - footHight + 1 });
		m_foot.shape({ coord.x, FLOOR - footHight, width, footHight });
	}

	void draw()
	{
		m_pole.renderer()->color({ 0, 0, 0, 0xFF });
		m_pole.draw_rect();
		m_foot.draw_rect();
	}

	constexpr auto poleShape() { return m_pole.shape(); }

private:
	sdl::RectFrame<sdl::EDrawable> m_pole;
	sdl::RectFrame<sdl::EDrawable> m_foot;
};
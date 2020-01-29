#pragma once

#include "Includes.h"

class Light
{
	static constexpr std::array<SDL_Color, 3> COLORS = { sdl::RED, sdl::YELLOW, sdl::GREEN };

public:
	enum Color { RED, YELLOW, GREEN };

	Light(sdl::Renderer* rend, const mth::Circle<int, Uint32>& c, Color col) noexcept
		: m_circle(rend)
		, m_color(col)
	{
		m_circle.shape(c);
	}

	Light& flipSwitch() noexcept
	{
		m_on = !m_on;
		return *this;
	}

	Light& change(bool s) noexcept
	{
		m_on = s;
		return *this;
	}

	void draw() const
	{
		if (m_on)
		{
			m_circle.renderer()->color(COLORS[m_color]);
			m_circle.draw_filled_circle();
		}

		m_circle.renderer()->color({ 0, 0, 0, 0xFF });
		m_circle.draw_circle();
	}

private:
	sdl::CircleFrame<sdl::EDrawable> m_circle;
	Color m_color;
	bool m_on = false;
};
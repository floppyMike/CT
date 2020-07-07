#pragma once

#include "CustomLibrary/SDL/Geometry.h"
#include "Includes.h"

class Light
{
	static constexpr std::array<SDL_Color, 3> COLORS = { sdl::RED, sdl::YELLOW, sdl::GREEN };

public:
	enum Color { RED, YELLOW, GREEN };

	Light(sdl::Renderer* rend, const mth::Circle<int, Uint32>& c, Color col) noexcept
		: m_r(rend)
		, m_circle(c)
		, m_color(col)
	{
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

	auto isOn() const noexcept
	{
		return m_on;
	}

	constexpr auto& translate(const mth::Point<int>& delta) noexcept
	{
		m_circle.shape().translate(delta);
		return *this;
	}

	constexpr const auto& shape() const noexcept
	{
		return m_circle.shape();
	}

	void draw()
	{
		if (m_on)
		{
			m_r->color(COLORS[m_color]);
			m_circle.draw(m_r).filled_circle();
		}

		m_r->color({ 0, 0, 0, 0xFF });
		m_circle.draw(m_r).circle();
	}

private:
	sdl::Renderer *m_r;

	sdl::ECircleFrame<sdl::Drawable> m_circle;
	Color m_color;
	bool m_on = false;
};
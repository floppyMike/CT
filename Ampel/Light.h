#pragma once

#include "Includes.h"

class Light
{
	static constexpr std::array<SDL_Color, 3> COLORS = { sdl::RED, sdl::YELLOW, sdl::GREEN };

public:
	enum Color { RED, YELLOW, GREEN };

	Light(sdl::Renderer* rend, const sdl::Circle<int, Uint32>& c, Color col) noexcept
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

	auto isOn() const noexcept
	{
		return m_on;
	}

	constexpr auto& translate(const sdl::Point<int>& delta) noexcept
	{
		m_circle.translate(delta);
		return *this;
	}

	constexpr const auto& shape() const noexcept
	{
		return m_circle.shape();
	}

	void draw() const
	{
		if (m_on)
		{
			m_circle.renderer()->setColor(COLORS[m_color]);
			m_circle.drawFilled();
		}

		m_circle.renderer()->setColor({ 0, 0, 0, 0xFF });
		m_circle.draw();
	}

private:
	sdl::CircleDraw<> m_circle;
	Color m_color;
	bool m_on = false;
};
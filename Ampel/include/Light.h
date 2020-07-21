#pragma once

#include "Includes.h"

class Light
{
public:
	Light(const mth::Circle<int, Uint32> &c, SDL_Color col) noexcept
		: m_circle(c)
		, m_color(col)
	{
	}

	auto						 change(bool s) noexcept { m_color.a = s ? 0xFF : 0; }
	[[nodiscard]] auto			 is_on() const noexcept { return m_color.a == 0xFF; }
	constexpr auto				 translate(const mth::Point<int> &delta) noexcept { m_circle.shape().translate(delta); }
	[[nodiscard]] constexpr auto shape() const noexcept -> const auto & { return m_circle.shape(); }

	friend auto operator<<(sdl::Renderer &r, const Light &l) -> sdl::Renderer &
	{
		r.color(l.m_color);
		l.m_circle.draw(&r).filled_circle();

		r.color({ 0, 0, 0, 0xFF });
		l.m_circle.draw(&r).circle();

		return r;
	}

private:
	sdl::ECircleFrame<sdl::Drawable> m_circle;
	SDL_Color						 m_color;
};
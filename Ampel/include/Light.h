#pragma once

#include "CustomLibrary/SDL/Drawable.h"
#include "CustomLibrary/SDL/Geometry.h"
#include "Includes.h"

class Light
{
public:
	Light(const mth::Circle<int, Uint32> &c, SDL_Color col) noexcept
		: m_circle(c)
		, m_color(col)
	{
	}

	constexpr void change(bool s) noexcept { m_color.a = s ? 0xFF : 0; }

	[[nodiscard]] constexpr auto is_on() const noexcept { return m_color.a == 0xFF; }

	constexpr void translate(const mth::Point<int> &delta) noexcept { m_circle.shape().translate(delta); }

	[[nodiscard]] constexpr auto shape() const noexcept -> const auto & { return m_circle; }
	[[nodiscard]] constexpr auto color() const noexcept -> const auto & { return m_color; }

	auto draw(sdl::Renderer *r)
	{
		r->color(m_color);
		m_circle.draw(r).filled_circle();
	}

private:
	sdl::ECircleFrame<sdl::Drawable> m_circle;
	SDL_Color				 m_color;
};

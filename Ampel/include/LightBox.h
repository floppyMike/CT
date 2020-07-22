#pragma once

#include "Includes.h"
#include "Light.h"

class LightBox
{
public:
	LightBox(const mth::Point<int> &coord, int width, std::initializer_list<SDL_Color> &&colors)
	{
		const Uint32 radius = width * 3 / 8;
		const auto	 pause	= width / 4;

		const mth::Dim<int> dim(width, 2 * radius * colors.size() + pause * (colors.size() + 1));
		m_box.shape({ coord, dim });

		m_lights.reserve(colors.size());
		for (int i = 0; i < colors.size(); ++i)
		{
			const mth::Circle<int, Uint32> cir(coord.x + width / 2, coord.y + pause + radius + i * (radius * 2 + pause),
											   radius);
			const auto &				   col = *(colors.begin() + i);

			m_lights.emplace_back(cir, col);
		}
	}

	auto			   change(size_t idx, bool s) { m_lights[idx].change(s); }
	[[nodiscard]] auto is_on(size_t idx) const noexcept { return m_lights[idx].is_on(); }

	[[nodiscard]] constexpr auto shape() const noexcept -> const auto & { return m_box.shape(); }

	auto translate(const mth::Point<int> &delta) noexcept
	{
		m_box.shape().translate(delta);
		for (auto &i : m_lights) i.translate(delta);
	}

	friend auto operator<<(sdl::Renderer &r, const LightBox &lb) -> sdl::Renderer &
	{
		r.color({ 0, 0, 0, 0xFF });
		lb.m_box.draw(&r).rect();

		for (const auto &l : lb.m_lights) r << l;

		return r;
	}

private:
	sdl::ERectFrame<sdl::Drawable> m_box;
	std::vector<Light>			   m_lights;
};

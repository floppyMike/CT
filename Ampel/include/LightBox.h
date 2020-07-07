#pragma once

#include "Includes.h"
#include "Light.h"

class LightBox
{
public:
	LightBox(const mth::Point<int> &coord, size_t w, std::initializer_list<SDL_Color> &&colors)
	{
		assert(colors.size() != 0 && "Lights colors amount must be at least 1");

		const size_t rad = w / 4;

		m_box.shape(mth::Rect<int, int>(coord.x, coord.y, w, rad * (1 + 3 * colors.size())));

		m_lights.reserve(colors.size());
		for (auto iter = colors.begin(); iter != colors.end(); ++iter)
		{
			mth::Circle<int, Uint32> cir(coord.x + w / 2, rad * (2 + 3 * std::distance(colors.begin(), iter)) + coord.y,
										 rad * 2);
			m_lights.emplace_back(cir, *iter);
		}
	}

	constexpr void change(size_t idx, bool s) { m_lights[idx].change(s); }

	[[nodiscard]] constexpr auto is_on(size_t idx) const noexcept { return m_lights[idx].is_on(); }

	[[nodiscard]] auto			 light(size_t idx) const noexcept -> const auto & { return m_lights[idx]; }
	[[nodiscard]] constexpr auto shape() const noexcept -> const auto & { return m_box.shape(); }

	void translate(const mth::Point<int> &delta) noexcept
	{
		m_box.shape().translate(delta);
		for (auto &i : m_lights) i.translate(delta);
	}

	void draw(sdl::Renderer *r)
	{
		r->color(sdl::BLACK);
		m_box.draw(r).rect();

		for (auto &l : m_lights) l.draw(r);
	}

private:
	sdl::ERectFrame<sdl::Drawable> m_box;
	std::vector<Light>			   m_lights;
};

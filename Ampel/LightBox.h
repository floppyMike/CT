#pragma once

#include "Includes.h"

class LightBox
{
public:
	LightBox(sdl::Renderer* r, const mth::Point<int>& coord, int width, std::initializer_list<Light::Color>&& colors)
		: m_box(r)
	{
		mth::Dim<int> dim;
		dim.w = width;

		const Uint32 radius = width * 3 >> 3;
		const auto pause = width >> 2;

		dim.h = 2 * radius * colors.size() + pause * (colors.size() + 1);
		m_box.shape({ coord, dim });

		m_lights.reserve(colors.size());
		for (int i = 0; i < colors.size(); ++i)
		{
			mth::Circle<int, Uint32> cir(coord.x + (width >> 1), coord.y + pause + radius + i * ((radius << 1) + pause), radius);
			const auto& col = *(colors.begin() + i);

			m_lights.emplace_back(r, cir, col);
		}
	}

	auto& flipLight(size_t idx)
	{
		m_lights[idx].flipSwitch();
		return *this;
	}

	auto& change(size_t idx, bool s)
	{
		m_lights[idx].change(s);
		return *this;
	}

	void draw()
	{
		m_box.renderer()->color({ 0, 0, 0, 0xFF });
		m_box.draw_rect();

		for (const auto& i : m_lights)
			i.draw();
	}

	constexpr const auto& shape() const { return m_box.shape(); }

private:
	sdl::RectFrame<sdl::EDrawable> m_box;
	std::vector<Light> m_lights;
};

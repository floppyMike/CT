#pragma once

#include "Includes.h"
#include "TrafficLight.h"

class Selected
{
public:
	Selected() = default;

	auto select(std::unique_ptr<TrafficLight> &&ptr) noexcept
	{
		auto old   = std::move(m_selected);
		m_selected = std::move(ptr);

		const auto shape = m_selected->shape();
		m_box.shape({ shape.x - 5, shape.y - 5, shape.w + 10, shape.h + 10 });

		return old;
	}

	auto clear() noexcept -> std::unique_ptr<TrafficLight>
	{
		auto temp  = std::move(m_selected);
		m_selected = nullptr;

		return temp;
	}

	auto get() noexcept -> auto *
	{
		assert(m_selected && "No selected TrafficNode.");
		return m_selected.get();
	}

	[[nodiscard]] auto is_selected() const noexcept -> bool { return m_selected.operator bool(); }

	auto isSelected(TrafficLight *ptr) const noexcept -> bool { return m_selected.get() == ptr; }

	void eraseLinks() {}

	void draw(sdl::Renderer *r)
	{
		if (m_selected != nullptr)
		{
			r->color(sdl::GREEN);
			m_box.draw(r).rect();

			r->color(sdl::BLACK);
			m_selected->draw();

			r->color(sdl::BLUE);
			for (auto &i : m_selected->lines) i->draw();
		}
	}

private:
	std::unique_ptr<TrafficLight>  m_selected = nullptr;
	sdl::ERectFrame<sdl::Drawable> m_box;
};

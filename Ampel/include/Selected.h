#pragma once

#include "Includes.h"
#include "RoadsDB.h"

class Selected
{
public:
	Selected() = default;

	auto select(std::unique_ptr<TrafficNode> &&ptr) noexcept
	{
		auto old   = std::move(m_selected);
		m_selected = std::move(ptr);

		const auto shape = m_selected->shape();
		m_box.shape({ shape.x - 5, shape.y - 5, shape.w + 10, shape.h + 10 });

		return old;
	}

	auto clear() noexcept -> std::unique_ptr<TrafficNode>
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

	auto is_selected(TrafficNode *ptr) const noexcept -> bool { return m_selected.get() == ptr; }

	friend auto operator<<(sdl::Renderer &r, const Selected &s) -> sdl::Renderer &
	{
		if (!s.m_selected)
			return r;

		r.color(sdl::GREEN);
		s.m_box.draw(&r).rect();

		r << *s.m_selected;

		r.color(sdl::BLUE);
		for (const auto &i : s.m_selected->links()) r << *i;

		return r;
	}

private:
	std::unique_ptr<TrafficNode>   m_selected = nullptr;
	sdl::ERectFrame<sdl::Drawable> m_box;
};

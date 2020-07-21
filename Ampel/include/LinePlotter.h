#pragma once

#include "Includes.h"
#include "Line.h"

class LinePlotter
{
public:
	LinePlotter() = default;

	void spawn(Node *from) noexcept
	{
		m_selected =
			std::make_unique<Link>(mth::Line{ { from->shape().x + 2, from->shape().y + 2 }, sdl::mouse_position() });

		m_selected->from_node(from);
	}

	auto place(Node *to) noexcept
	{
		m_selected->to_node(to);
		return std::move(m_selected);
	}

	void			   clear() noexcept { m_selected = nullptr; }
	auto			   get() noexcept -> auto * { return m_selected.get(); }
	[[nodiscard]] auto is_made() const noexcept -> bool { return m_selected.operator bool(); }
	auto			   sync_mouse() noexcept { m_selected->to_node(sdl::mouse_position()); }

	friend auto operator<<(sdl::Renderer &r, const LinePlotter &lp) -> sdl::Renderer &
	{
		if (!lp.m_selected)
			return r;

		r.color(sdl::ORANGE);
		r << *lp.m_selected;

		return r;
	}

private:
	std::unique_ptr<Link> m_selected;
};

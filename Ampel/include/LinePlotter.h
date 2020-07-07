#pragma once

#include "Includes.h"
#include "Line.h"

class LinePlotter
{
public:
	LinePlotter() noexcept = default;

	void spawn(Node *from) noexcept
	{
		m_selected =
			std::make_unique<Link>(mth::Line{ { from->shape().x + 2, from->shape().y + 2 }, sdl::mouse_position() });

		m_selected->fromNode(from);
	}

	auto place(Node *to) noexcept
	{
		m_selected->shape({ m_selected->shape().pos1(), { to->shape().pos() + mth::Point(2, 2) } }).toNode(to);
		return std::move(m_selected);
	}

	void			   clear() noexcept { m_selected = nullptr; }
	auto			   get() noexcept -> auto * { return m_selected.get(); }
	[[nodiscard]] auto is_made() const noexcept -> bool { return m_selected.operator bool(); }
	void translateEnd(const mth::Point<int> &delta) { m_selected->shape({ m_selected->shape().pos1(), delta }); }

	void draw(sdl::Renderer *r)
	{
		if (m_selected)
		{
			r->color(sdl::ORANGE);
			m_selected->draw(r);
		}
	}

private:
	std::unique_ptr<Link> m_selected;
};

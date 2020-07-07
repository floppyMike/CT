#pragma once

#include "Includes.h"
#include "Line.h"


class LinePlotter
{
public:
	LinePlotter(sdl::Renderer* r)
		: m_r(r)
	{
	}

	void spawn(DNode* from) noexcept
	{
		m_selected = std::make_unique<DLink>(m_r,
			mth::Line{ { from->shape().x + 2, from->shape().y + 2 }, mousePosition() });

		m_selected->fromNode(from);
	}

	auto place(DNode* to) noexcept
	{
		m_selected->shape({ m_selected->shape().pos1(), { to->shape().pos() + mth::Point(2, 2) } }).toNode(to);
		return std::move(m_selected);
	}

	void clear() noexcept
	{
		m_selected = nullptr;
	}

	auto* get() noexcept
	{
		return m_selected.get();
	}

	bool isMade() const noexcept
	{
		return m_selected.operator bool();
	}

	void translateEnd(const mth::Point<int>& delta)
	{
		m_selected->shape({ m_selected->shape().pos1(), delta });
	}

	void draw()
	{
		if (m_selected)
		{
			m_r->color(sdl::ORANGE);
			m_selected->draw();
		}
	}

private:
	sdl::Renderer* m_r;
	std::unique_ptr<DLink> m_selected;
};

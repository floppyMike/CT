#pragma once

#include "Includes.h"

class Selected
{
public:
	Selected(sdl::Renderer* r)
		: m_box(r)
	{
	}

	void select(TrafficNode* ptr) noexcept
	{
		m_selected = ptr;

		auto shape = ptr->light.shape();
		m_box.shape({ shape.x - 5, shape.y - 5, shape.w + 10, shape.h + 10 });
	}

	void clear() noexcept
	{
		m_selected = nullptr;
	}

	auto* get() noexcept
	{
		return m_selected;
	}

	bool isSelected() const noexcept
	{
		return m_selected != nullptr;
	}

	void draw()
	{
		if (m_selected != nullptr)
		{
			m_box.renderer()->setColor(sdl::GREEN);
			m_box.draw();
		}
	}

private:
	TrafficNode* m_selected = nullptr;
	sdl::RectDraw<> m_box;
};

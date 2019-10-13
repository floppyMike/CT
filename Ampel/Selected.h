#pragma once

#include "Includes.h"

class Selected
{
public:
	Selected(sdl::Renderer* r)
		: m_box(r)
	{
	}

	auto select(std::unique_ptr<DTrafficNode>&& ptr) noexcept
	{
		auto old = std::move(m_selected);
		m_selected = std::move(ptr);

		const auto shape = m_selected->shape();
		m_box.shape({ shape.x - 5, shape.y - 5, shape.w + 10, shape.h + 10 });

		return old;
	}

	void clear() noexcept
	{
		m_selected = nullptr;
	}

	auto* get() noexcept
	{
		assert(m_selected && "No selected TrafficNode.");
		return m_selected.get();
	}

	bool isSelected() const noexcept
	{
		return m_selected.operator bool();
	}

	bool isSelected(DTrafficNode* ptr) const noexcept
	{
		return m_selected.get() == ptr;
	}

	void eraseLinks()
	{

	}

	void draw()
	{
		if (m_selected != nullptr)
		{
			m_box.renderer()->setColor(sdl::GREEN);
			m_box.draw();

			m_box.renderer()->setColor(sdl::BLACK);
			m_selected->draw();

			m_box.renderer()->setColor(sdl::BLUE);
			for (auto& i : m_selected->lines)
				i->draw();
		}
	}

private:
	std::unique_ptr<DTrafficNode> m_selected = nullptr;
	sdl::RectDraw<> m_box;
};

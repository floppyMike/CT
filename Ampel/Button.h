#pragma once

#include "Includes.h"

class Button
{
public:
	Button(sdl::Renderer* r)
		: m_box(r)
		, m_button(r)
	{
		m_button.func([this] { m_event.push_event(); });
		m_event.user_type(Events::BUTTON_PRESS);
	}

	auto& boxShape(const mth::Rect<int, int>& s) noexcept
	{
		m_box.shape(s);
		m_button.shape({ s.x + (s.w >> 1), s.y + (s.h >> 1), std::min<Uint32>(s.w >> 1, s.h >> 1) - (s.w >> 2) });
		return *this;
	}

	void event(const SDL_Event& e)
	{
		m_button.event(e);
	}

	void draw()
	{
		m_box.renderer()->color({ 0xFF, 0xFF, 0xFF, 0xFF });
		m_box.draw_filled_rect();
		m_box.renderer()->color({ 0, 0, 0, 0xFF });
		m_box.draw_rect();

		m_box.renderer()->color({ 128, 128, 128, 0xFF });
		m_button.draw_filled_circle();
	}

private:
	sdl::RectFrame<sdl::EDrawable> m_box;
	sdl::CircleFrame<sdl::EButton, sdl::EDrawable> m_button;

	sdl::UserEvent m_event;
};
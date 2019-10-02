#pragma once

#include "Includes.h"

class Button
{
public:
	Button(sdl::Renderer* r)
		: m_box(r)
		, m_button(r)
	{
		m_button.func([this] { m_event.pushEvent(); });
		m_event.userType(Events::BUTTON_PRESS);
	}

	auto& boxShape(const sdl::Rect<int, int>& s) noexcept
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
		m_box.renderer()->setColor({ 0xFF, 0xFF, 0xFF, 0xFF });
		m_box.drawFilled();
		m_box.renderer()->setColor({ 0, 0, 0, 0xFF });
		m_box.draw();

		m_box.renderer()->setColor({ 128, 128, 128, 0xFF });
		m_button.drawFilled();
	}

private:
	sdl::RectDraw<> m_box;
	sdl::CircleDraw<sdl::ButtonEx> m_button;

	sdl::UserEvent m_event;
};
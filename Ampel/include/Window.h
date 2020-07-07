#pragma once

#include "Includes.h"
#include "Application.h"


class Window : public sdl::IWindow
{
	using Duration = std::chrono::steady_clock::duration;

	//class SSetup;

public:
	Window()
		: m_win("Ampel", WINDOW_SIZE)
		, m_rend(&m_win)
		, m_app(&m_rend, &m_doRender)
	{
	}

	void pre_pass()
	{
		m_app.pre_pass();
	}

	void event(const SDL_Event& e)
	{
		m_app.input(e);
	}

	void update()
	{
		m_app.update();
	}

	void fixed_update() {}

	void render()
	{
		if (m_doRender)
		{
			m_rend.render().fill(sdl::WHITE);

			m_app.draw();

			m_rend.render().render();
			//m_doRender = false;
		}
	}

private:
	sdl::Window m_win;
	sdl::Renderer m_rend;
	bool m_doRender = true;

	App m_app;
};

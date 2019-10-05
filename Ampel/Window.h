#pragma once

#include "Includes.h"
#include "Application.h"


class Window
{
	using Duration = std::chrono::steady_clock::duration;

	//class SSetup;

public:
	Window()
		: m_win("Ampel", WINDOW_SIZE)
		, m_rend(&m_win)
		, m_app(&m_rend)
	{
	}

	void event(const SDL_Event& e)
	{
		m_app.input(e);
	}

	void update()
	{
		m_app.update();
	}

	void fixedUpdate() {}

	void render()
	{
		if (true)
		{
			m_rend.setColor({ 0xFF, 0xFF, 0xFF, 0xFF });
			m_rend.fill();

			m_app.draw();

			m_rend.render();
			m_doRender = false;
		}
	}

private:
	sdl::Window m_win;
	sdl::Renderer m_rend;
	bool m_doRender = true;

	App m_app;
};

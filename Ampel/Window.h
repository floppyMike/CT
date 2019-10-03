#pragma once

#include "Includes.h"
#include "Light.h"
#include "VehicleLight.h"
#include "TrafficLight.h"

class Window
{
	using Duration = std::chrono::steady_clock::duration;

	struct SBlink;
	struct SPress;
	struct STurnRed;
	struct SPedestrian;
	struct STurnGreen;

public:
	Window();

	void event(const SDL_Event& e)
	{
		m_state->input(e);
	}

	void update()
	{
		m_state->update();
	}

	void fixedUpdate() {}

	void render()
	{
		if (m_doRender)
		{
			m_rend.setColor({ 0xFF, 0xFF, 0xFF, 0xFF });
			m_rend.fill();

			m_veh.draw();
			m_ped.draw();

			m_rend.render();

			m_doRender = false;
		}
	}

private:
	sdl::Window m_win;
	sdl::Renderer m_rend;
	bool m_doRender = true;

	std::unique_ptr<sdl::IState> m_state;

	ctl::Timer m_time;

	VehicleLight m_veh;
	TrafficLight m_ped;
};


struct Window::SBlink : sdl::IState
{
	SBlink(Window* w) : pthis(w) {}

	static constexpr Duration BLINKING = 3s;
	static constexpr Duration BLINK_TICK = (1000ms / 2);

	void update() override;

private:
	Window* pthis = nullptr;
	Duration m_point = Duration(0);
};


struct Window::SPress : sdl::IState
{
	SPress(Window* w) : pthis(w) {}

	void input(const SDL_Event& e) override;

private:
	Window* pthis = nullptr;
};


struct Window::STurnRed : sdl::IState
{
	STurnRed(Window* w) : pthis(w) {}

	static constexpr Duration PRESS_DELAY = 5s;

	void update() override;

private:
	Window* pthis = nullptr;
};


struct Window::STurnGreen : sdl::IState
{
	STurnGreen(Window* w) : pthis(w) {}

	static constexpr Duration TO_RED_DURATION = 2s;

	void update() override;

private:
	Window* pthis = nullptr;
};


struct Window::SPedestrian : sdl::IState
{
	SPedestrian(Window* w) : pthis(w) {}

	static constexpr Duration PEDESTRIAN_WAIT = 10s - Window::STurnGreen::TO_RED_DURATION;

	void update() override;

private:
	Window* pthis = nullptr;
};


//----------------------------------------------
//Implementation
//----------------------------------------------

inline Window::Window()
	: m_win("Ampel", { 640, 490 }, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)
	, m_rend(&m_win)
	, m_veh(&m_rend, { 200, 50 }, 50, { Light::RED, Light::YELLOW, Light::GREEN })
	, m_ped(&m_rend, { 400, 50 }, 50, { Light::RED, Light::GREEN })
{
	m_rend.setLogicalSize(m_win.dim());

	m_state = std::make_unique<SBlink>(this);

	m_time.start();
	m_veh.change(1, true);
}


inline void Window::SBlink::update()
{
	if (pthis->m_time.ticks<std::chrono::milliseconds>() >= BLINK_TICK)
	{
		m_point += pthis->m_time.ticks<std::chrono::milliseconds>();

		pthis->m_time.stop();
		pthis->m_time.start();

		pthis->m_veh.flipLight(1);
		pthis->m_doRender = true;

		if (m_point >= BLINKING)
		{
			pthis->m_veh.change(2, true);
			pthis->m_veh.change(1, false);
			pthis->m_ped.change(0, true);

			pthis->m_time.stop();

			pthis->m_state = std::make_unique<SPress>(pthis);
		}
	}
}


inline void Window::SPress::input(const SDL_Event& e)
{
	pthis->m_veh.event(e);

	if (e.user.type == Events::BUTTON_PRESS)
	{
		pthis->m_time.start();

		pthis->m_veh.change(1, true);
		pthis->m_veh.change(0, false);
		pthis->m_veh.change(2, false);
		pthis->m_doRender = true;

		pthis->m_state = std::make_unique<STurnRed>(pthis);
	}
}


inline void Window::STurnRed::update()
{
	if (pthis->m_time.ticks<>() >= PRESS_DELAY)
	{
		pthis->m_ped.change(1, true);
		pthis->m_ped.change(0, false);

		pthis->m_veh.change(0, true);
		pthis->m_veh.change(1, false);
		pthis->m_doRender = true;

		pthis->m_time.stop();
		pthis->m_time.start();

		pthis->m_state = std::make_unique<SPedestrian>(pthis);
	}
}


inline void Window::STurnGreen::update()
{
	if (pthis->m_time.ticks<>() >= TO_RED_DURATION)
	{
		pthis->m_veh.change(0, false);
		pthis->m_veh.change(1, false);
		pthis->m_veh.change(2, true);
		pthis->m_doRender = true;

		pthis->m_time.stop();

		pthis->m_state = std::make_unique<SPress>(pthis);
	}
}


inline void Window::SPedestrian::update()
{
	if (pthis->m_time.ticks<>() >= PEDESTRIAN_WAIT)
	{
		pthis->m_ped.change(1, false);
		pthis->m_ped.change(0, true);

		pthis->m_veh.change(1, true);
		pthis->m_doRender = true;

		pthis->m_time.stop();
		pthis->m_time.start();

		pthis->m_state = std::make_unique<STurnGreen>(pthis);
	}
}
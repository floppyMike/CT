#pragma once

#include "Includes.h"
#include "Light.h"
#include "VehicleLight.h"
#include "TrafficLight.h"

class Window
{
	using Duration = std::chrono::steady_clock::duration;

	static constexpr Duration BLINKING = 3s;
	static constexpr Duration PRESS_DELAY = 5s;
	static constexpr Duration GREEN_DURATION = 10s;

	static constexpr Duration BLINK_TICK = (1000ms / 2);

	enum class State
	{
		BLINK, PRESS, GREEN, WAIT
	};

public:
	Window()
		: m_win("Ampel", { 640, 490 })
		, m_rend(&m_win)
		, m_veh(&m_rend, { 200, 50 }, 50, { Light::RED, Light::YELLOW, Light::GREEN })
		, m_ped(&m_rend, { 400, 50 }, 50, { Light::RED, Light::GREEN })
	{
		m_time.start();

		m_veh.change(1, true);
	}

	void event(const SDL_Event& e)
	{
		switch (m_state)
		{
		case Window::State::BLINK:
			break;

		case Window::State::PRESS:
			m_veh.event(e);
			if (e.user.type == Events::BUTTON_PRESS)
			{
				m_time.start();

				m_veh.change(1, true);
				m_veh.change(0, false);
				m_veh.change(2, false);

				m_state = State::GREEN;
			}
			break;

		case Window::State::GREEN:
			break;

		default:
			break;
		}
	}

	void update()
	{
		switch (m_state)
		{
		case Window::State::BLINK:
			if (m_time.ticks<std::chrono::milliseconds>() >= BLINK_TICK)
			{
				m_point += m_time.ticks<std::chrono::milliseconds>();

				m_time.stop();
				m_time.start();

				m_veh.flipLight(1);
				if (m_point >= BLINKING)
				{
					m_state = State::PRESS;

					m_veh.change(2, true);
					m_veh.change(1, false);
					m_ped.change(0, true);

					m_time.stop();
				}
			}
			break;

		case Window::State::PRESS:
			break;

		case Window::State::GREEN:
			if (m_time.ticks<>() >= PRESS_DELAY)
			{
				m_ped.change(1, true);
				m_ped.change(0, false);

				m_veh.change(0, true);
				m_veh.change(1, false);

				m_time.stop();
				m_time.start();

				m_state = State::WAIT;
			}
			break;

		case State::WAIT:
			if (m_time.ticks<>() >= GREEN_DURATION)
			{
				m_ped.change(1, false);
				m_ped.change(0, true);

				m_veh.change(0, false);
				m_veh.change(2, true);

				m_time.stop();

				m_state = State::PRESS;
			}
			break;

		default:
			break;
		}
	}
	void fixedUpdate()
	{

	}
	void render()
	{
		m_rend.setColor({ 0xFF, 0xFF, 0xFF, 0xFF });
		m_rend.fill();

		m_veh.draw();
		m_ped.draw();

		m_rend.render();
	}

private:
	sdl::Window m_win;
	sdl::Renderer m_rend;

	State m_state = State::BLINK;

	ctl::Timer m_time;
	Duration m_point = Duration(0);

	VehicleLight m_veh;
	TrafficLight m_ped;
};
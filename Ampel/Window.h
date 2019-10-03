#pragma once

#include "Includes.h"
#include "Light.h"
#include "VehicleLight.h"
#include "TrafficLight.h"

#include "SetupState.h"

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

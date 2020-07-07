#pragma once

#include "Includes.h"

#include "Setup.h"
#include "Simulation.h"
#include "RoadsDB.h"

class Window
{
	using Duration = std::chrono::steady_clock::duration;

public:
	Window()
		: m_win("Ampel", WINDOW_DEFAULT_SIZE)
		, m_rend(&m_win)
	{
		m_state.set<Setup>(this);
	}

	void pre_pass() { m_state.update(); }
	void event(const SDL_Event &e) { m_state->input(e); }
	void update() { m_state->update(); }
	void fixed_update() {}
	void render()
	{
		if (m_rend.will_render())
		{
			m_rend.color({ 0xFF, 0xFF, 0xFF, 0xFF });
			m_rend.render().fill(sdl::BLACK);

			m_state->draw();

			m_rend.render().render();
		}
	}

private:
	sdl::Window							  m_win;
	sdl::ERenderer<sdl::LDelayedRenderer> m_rend;

	TrafficLights m_roads;

	sdl::StateManager<sdl::IState> m_state;
};

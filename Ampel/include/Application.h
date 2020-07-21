#pragma once

#include "Includes.h"
#include "NodeDB.h"
#include "TrafficNodeDB.h"
#include "LinkDB.h"

class SSetup;
class SSimulation;
class SCompile;

class App : public sdl::IWindow
{
	friend class SSetup;
	friend class SSimulation;
	friend class SCompile;

public:
	App();

	void pre_pass() override { m_state.update(); }
	void update() override { m_state->update(); }
	void event(const SDL_Event &e) override { m_state->input(e); }
	void fixed_update() override {}

	void render() override
	{
		m_rend.render().fill(sdl::WHITE);

		m_state->draw();

		m_rend.render().render();
	}

private:
	sdl::Window	  m_win;
	sdl::Renderer m_rend;

	sdl::StateManager<sdl::IState> m_state;

	TrafficNodes m_roads;
	Nodes		 m_nodes;
	Links		 m_links;
};

//----------------------------------------------
// States
//----------------------------------------------

#include "Setup.h"
// #include "Compile.h"
// #include "Simulation.h"

App::App()
	: m_win("Ampel", WINDOW_SIZE)
	, m_rend(&m_win)
{
	m_state.set<SSetup>(this);
	m_state.update();
}

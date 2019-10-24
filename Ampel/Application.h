#pragma once

#include "Includes.h"
#include "RoadsDB.h"
#include "Selected.h"
#include "SequenceDB.h"
#include "NodeDB.h"
#include "TrafficNodeDB.h"
#include "LinkDB.h"
#include "LinePlotter.h"


class App
{
	class SSetup;
	class SSimulation;
	class SCompile;

public:
	App(sdl::Renderer* r, bool* doRend);

	void update()
	{
		m_state->update();
		m_state.update();
	}

	void input(const SDL_Event& e)
	{
		m_state->input(e);
	}

	void draw()
	{
		_drawNodes_();
		m_state->draw();
	}

private:
	sdl::Renderer* m_r;

	sdl::StateManager<sdl::IState> m_state;

	TrafficNodeDB<TrafficNodeOnMouse, TrafficNodeDeleter> m_roads;
	NodeDB<NodesOnMouse> m_nodes;
	LinkDB<LinkRemover, LinkFinder> m_links;

	bool* m_doRender;

	void _drawNodes_()
	{
		m_r->setColor(sdl::BLACK);
		for (auto& i : m_nodes)
			i->draw();
	}
};


//----------------------------------------------
//Implementation
//----------------------------------------------


#include "Setup.ipp"
#include "Compile.ipp"
#include "Simulation.ipp"

App::App(sdl::Renderer* r, bool* doRend)
	: m_r(r)
	, m_doRender(doRend)
{
	m_state.set<SSetup>(this);
	m_state.update();
}

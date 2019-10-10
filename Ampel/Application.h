#pragma once

#include "Includes.h"
#include "RoadsDB.h"
#include "Node.h"
#include "Line.h"
#include "Selected.h"
#include "SequenceGenerator.h"


using TrafficNodeDB = std::vector<std::unique_ptr<TrafficNode>>;
using NodeDB = std::vector<std::unique_ptr<Node>>;
using LinkDB = std::vector<std::unique_ptr<Link>>;


class App
{
	class SSetup;
	class SSimulation;

public:
	App(sdl::Renderer* r);

	void input(const SDL_Event& e)
	{
		m_state->input(e);
	}

	void draw()
	{
		_drawNodes_();
		m_state->draw();

		m_state.update();
	}

private:
	sdl::Renderer* m_r;

	sdl::StateManager<sdl::IState> m_state;

	TrafficNodeDB m_roads;
	NodeDB m_nodes;
	LinkDB m_links;

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
#include "Simulation.ipp"

App::App(sdl::Renderer* r)
	: m_r(r)
{
	m_state.set<SSetup>(this);
	m_state.update();
}

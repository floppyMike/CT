#pragma once

#include "Includes.h"
#include "RoadsDB.h"
#include "Node.h"
#include "Selected.h"

using TrafficNodeDB = std::vector<TrafficNode>;
using NodeDB = std::vector<Node>;
using LinkDB = std::vector<sdl::LineDraw<>>;


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
		_drawTrafficNodes_();
		_drawNodes_();
		_drawLines_();

		m_state->draw();
	}

private:
	sdl::Renderer* m_r;

	std::unique_ptr<sdl::IState> m_state;

	TrafficNodeDB m_roads;
	NodeDB m_nodes;
	LinkDB m_lines;

	void _drawTrafficNodes_()
	{
		for (auto& i : m_roads)
			i.light.draw();
	}

	void _drawNodes_()
	{
		for (auto& i : m_nodes)
			i.draw();
	}

	void _drawLines_()
	{
		for (const auto& i : m_lines)
			i.draw();
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
	m_state = std::make_unique<SSetup>(this);
}

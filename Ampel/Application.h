#pragma once

#include "Includes.h"
#include "RoadsDB.h"
#include "Node.h"
#include "Selected.h"

class App
{
	class SSetup;

public:
	App(sdl::Renderer* r);

	void input(const SDL_Event& e)
	{
		m_state->input(e);
	}

	void update()
	{
		m_state->update();
	}

	void draw()
	{
		m_state->draw();

		for (auto& i : m_roads)
			i.light.draw();

		for (auto& i : m_nodes)
			i.draw();

		for (const auto& i : m_lines)
			i.draw();
	}

private:
	sdl::Renderer* m_r;

	std::unique_ptr<sdl::IState> m_state;

	LightsPairsDB m_roads;

	std::vector<Node> m_nodes;
	std::vector<sdl::LineDraw<>> m_lines;
};


//----------------------------------------------
//Implementation
//----------------------------------------------


#include "Setup.ipp"

App::App(sdl::Renderer* r)
	: m_r(r)
{
	m_state = std::make_unique<SSetup>(this);
}

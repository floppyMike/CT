#pragma once

#include "Includes.h"
#include "RoadsDB.h"


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
	}

private:
	sdl::Renderer* m_r;

	std::unique_ptr<sdl::IState> m_state;
	RoadsDB m_roads;
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

#pragma once

#include "Includes.h"
#include "RoadLights.h"


struct Road
{
	struct
	{
		TrafficLight light;
		std::chrono::steady_clock::time_point onTill;
		std::vector<size_t> path;
	} data;

	struct
	{
		sdl::Point<int> loc;
	} graphics;
};


class App
{
	class SSetup;

public:
	App(sdl::Renderer* r);

	void draw()
	{
		m_state->draw();
	}

private:
	sdl::Renderer* m_r;

	std::unique_ptr<sdl::IState> m_state;
	std::vector<Road> m_lights;
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

#pragma once

#include "Includes.h"
#include "RoadLights.h"


struct Road
{
	Road(sdl::Renderer* r, const sdl::Point<int>& pos)
		: light(r, pos)
	{
	}

	RoadLights light;
	//std::chrono::steady_clock::time_point onTill;
	//std::vector<size_t> path;
};


class App
{
	class SSetup;

public:
	App(sdl::Renderer* r);

	Road* insideWhich(const sdl::Point<int>& p) noexcept
	{
		Road* ptr = nullptr;
		for (auto iter = m_lights.rbegin(); iter != m_lights.rend(); ++iter)
			if (sdl::collision(iter->light.shape(), p))
			{
				ptr = &*iter;
				break;
			}

		return ptr;
	}

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

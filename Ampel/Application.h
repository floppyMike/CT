#pragma once

#include "Includes.h"
#include "RoadsDB.h"
#include "Node.h"

class App
{
	class SSetup;

public:
	App(sdl::Renderer* r);

	sdl::RectDraw<>* insideWhich(const sdl::Point<int>& p) noexcept
	{
		auto iter = m_nodes.end();
		if (!m_nodes.empty())
			do
			{
				--iter;
				if (sdl::collision(iter->shape(), p))
					break;
				else if (iter == m_nodes.begin())
				{
					iter = m_nodes.end();
					break;
				}
			} while (true);

		return iter == m_nodes.end() ? nullptr : &*iter;
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

		for (auto& i : m_roads)
			i.light.draw();

		m_r->setColor({ 0, 0, 0, 0xFF });
		for (const auto& i : m_nodes)
			i.drawFilled();

		for (const auto& i : m_lines)
			i.draw();
	}

private:
	sdl::Renderer* m_r;

	std::unique_ptr<sdl::IState> m_state;

	LightsPairsDB m_roads;

	std::vector<sdl::RectDraw<>> m_nodes;
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

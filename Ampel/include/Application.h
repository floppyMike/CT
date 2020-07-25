#pragma once

#include "Includes.h"
#include "Line.h"
#include "LinkDB.h"
#include "NodeDB.h"
#include "TrafficNodeDB.h"

class Graph
{
public:
	Graph() = default;

	void strip_links(const Node *const node)
	{
		m_links.erase(std::remove_if(m_links.begin(), m_links.end(),
									 [node](const std::unique_ptr<Link> &l) { return l->uses_node(node); }),
					  m_links.end());
	}

	void create_node(const mth::Point<int> &pos)
	{
		m_nodes.emplace_back(std::make_unique<Node>(mth::Rect(pos, NODE_DIM)));
	}

	auto create_line(const std::vector<Link *> &chain, const mth::Point<int> &p) noexcept
	{
		assert(m_links.back()->to_node() != nullptr && "Link search must have set Link");

		Link *from_node = nullptr;

		if (const auto select = std::find_if(chain.rbegin(),
											 chain.rend(), // Using reverse iterator for quicker responce
														   // newer things get deleted quicker
											 [&p](Link *l) { return sdl::collision(l->to_node()->shape(), p); });
			select != chain.rend())
			from_node = *select;

		m_links.emplace_back(from_node);
		m_links.back()->move_endpoint(m_links.back()->from_node()->shape().pos());
	}

	auto move_endpoint(const mth::Point<int> &p) noexcept
	{
		assert(m_links.back()->to_node() != nullptr && "Link movment must have set Link");
		m_links.back()->move_endpoint(p);
	}

	void remove_link(Link *l) { m_links.erase(std::find(m_links.begin(), m_links.end(), l)); }

private:
	Nodes m_nodes;
	Links m_links;
};

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

	Graph		 m_graph;
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

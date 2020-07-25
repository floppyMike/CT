#pragma once

#include "Includes.h"
#include "Application.h"

#include "Selected.h"
#include "LinePlotter.h"

class SSetup : public sdl::IState
{
public:
	explicit SSetup(App *p)
		: pthis(p)
	{
	}

	void input(const SDL_Event &e) override
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			if (e.key.repeat == 0)
				switch (e.key.keysym.sym)
				{
				case SDLK_c: _create_traffic_light_(); break;

				case SDLK_d:
					_delete_TrafficNode_();
					//_deleteNode_();
					break;

				case SDLK_p: _create_node_(); break;

				case SDLK_s:
					if (!m_linePlot.is_made())
						_start_sim_();
					break;

				default: break;
				}
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (m_selected_node.is_selected())
				_spawn_line_();
			_select_();
			break;

		case SDL_MOUSEBUTTONUP:
			if (m_linePlot.is_made())
				_put_line_();
			break;

		case SDL_MOUSEMOTION:
			if (m_linePlot.is_made())
				_translate_line_();
			break;

		default: break;
		}
	}

	void draw() override
	{
		pthis->m_rend << m_linePlot << pthis->m_roads << m_selected_node << pthis->m_nodes;
	}

private:
	App *pthis;

	Selected	m_selected_node;
	LinePlotter m_linePlot;

	void _create_traffic_light_()
	{
		auto prev = m_selected_node.select(std::make_unique<TrafficNode>(sdl::mouse_position()));

		if (prev)
			pthis->m_roads.emplace_back(std::move(prev));
	}

	void _strip_links_(TrafficNode *node)
	{
		pthis->m_links.erase(std::remove_if(pthis->m_links.begin(), pthis->m_links.end(),
											[node](const std::unique_ptr<Link> &l) {
												return l->uses_node(&node->in_node())
													|| l->uses_node(&node->out_node());
											}),
							 pthis->m_links.end());
	}

	void _delete_TrafficNode_()
	{
		if (m_selected_node.is_selected() && sdl::collision(m_selected_node.get()->shape(), sdl::mouse_position()))
		{
			for (auto *tn : m_selected_node.get()->links())
				pthis->m_graph.remove_link(tn);

			m_selected_node.clear();
		}

		else if (const auto select = range_collided(pthis->m_roads); select != pthis->m_roads.rend())
		{
			_strip_links_(select->get());
			ctl::fastRemove(pthis->m_roads, select.base() - 1);
		}
	}

	// void _deleteNode_()
	//{
	//	if (auto select = pthis->m_nodes.nodeOnMouse(); select != pthis->m_nodes.rend())
	//	{
	//		pthis->m_roads.removeNode(select->get());

	//		pthis->m_links.eraseLinesToNode(select->get());
	//		pthis->m_nodes.erase(select.base() - 1);
	//	}
	//}

	void _create_node_() { pthis->m_nodes.emplace_back(std::make_unique<Node>(mth::Rect(sdl::mouse_position(), NODE_DIM))); }

	void _start_sim_()
	{
		pthis->m_roads.emplace_back(m_selected_node.clear());
		// pthis->m_state.set<SCompile>(pthis);
	}

	void _spawn_line_()
	{
		Node *from_node = nullptr;

		if (sdl::collision(m_selected_node.get()->out_node().shape(), sdl::mouse_position()))
			from_node = &m_selected_node.get()->out_node();
		else if (const auto select = std::find_if(m_selected_node.get()->links().rbegin(),
						m_selected_node.get()->links().rend(), // Using reverse iterator for quicker responce
										// newer things get deleted quicker
						[](Link* l) { return sdl::collision(l->to_node()->shape(), sdl::mouse_position()); }); select != pthis->m_nodes.rend())
			from_node = select->to_node();
		else
			return;

		m_linePlot.spawn(from_node);
	}

	void _select_()
	{
		if (const auto select = range_collided(pthis->m_roads); select != pthis->m_roads.rend())
			if (*select = std::move(m_selected_node.select(std::move(*select))); !*select)
				ctl::fastRemove(pthis->m_roads, select.base() - 1);
	}

	void _translate_line_() { m_linePlot.sync_mouse(); }

	auto _find_node_() -> Node *
	{
		if (auto select = range_collided(pthis->m_nodes); select != pthis->m_nodes.rend())
			return select->get();

		if (auto select = range_collided(pthis->m_roads); select != pthis->m_roads.rend())
			return &(*select)->in_node();

		return nullptr;
	}

	void _put_line_()
	{
		if (Node *to_node = _find_node_(); to_node)
		{
			if (const auto select =
					find_link(pthis->m_links.begin(), pthis->m_links.end(), m_linePlot.get()->from_node(), to_node);
				select != pthis->m_links.end())
			{
				m_selected_node.get()->add_link(select->get());
				m_linePlot.clear();
			}
			else
				m_selected_node.get()->add_link(pthis->m_links.emplace_back(m_linePlot.place(to_node)).get());
		}
		else
			m_linePlot.clear();
	}
};
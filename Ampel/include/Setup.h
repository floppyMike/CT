#pragma once

#include "CustomLibrary/SDL/Renderer.h"
#include "Includes.h"
#include "TrafficLights.h"
#include "Links.h"
#include "Selected.h"
#include "LinePlotter.h"

class Setup : public sdl::IState
{
public:
	Setup() = default;

	void input(const SDL_Event &e) override
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			if (e.key.repeat == 0)
				switch (e.key.keysym.sym)
				{
				case SDLK_c: _createTrafficLightOnMouse_(); break;

				case SDLK_d:
					_deleteTrafficNode_();
					//_deleteNode_();
					break;

				case SDLK_p: _createNode_(); break;

				case SDLK_s:
					if (!m_linePlot.isMade())
						_startSim_();
					break;

				default: break;
				}
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (m_selected_node.isSelected())
				_spawnLine_();
			_select_();
			break;

		case SDL_MOUSEBUTTONUP:
			if (m_linePlot.isMade())
				_putLine_();
			break;

		case SDL_MOUSEMOTION:
			if (m_linePlot.isMade())
				_translateLine_(e);
			break;

		default: break;
		}
	}

	void draw(sdl::ERenderer<sdl::LDelayedRenderer> *r) override
	{
		m_line_plot.draw(r);

		for (auto &i : pthis->m_roads)
		{
			i->draw();

			r->color(sdl::BLACK);
			for (const auto &i : i->lines) i->draw();
		}

		m_selected_node.draw();
	}

private:
	sdl::MultiShape<mth::Rect<int, int>> m_nodes;
	Selected							 m_selected_node;
	LinePlotter							 m_line_plot;

	void _createTrafficLightOnMouse_()
	{
		auto prev = m_selected_node.select(std::make_unique<TrafficNode>(pthis->m_r, mousePosition()));

		if (prev)
			pthis->m_roads.emplace_back(std::move(prev));
	}

	void _stripLinks_(TrafficNode *node)
	{
		pthis->m_links.eraseLinesToNode(&node->inNode());
		pthis->m_links.eraseLinesToNode(&node->outNode());
	}

	void _deleteTrafficNode_()
	{
		if (m_selected_node.isSelected() && m_selected_node.get()->isTraffNodeOnMouse())
		{
			_stripLinks_(m_selected_node.get());
			m_selected_node.clear();
		}

		else if (auto select = pthis->m_roads.trafficNodeOnMouse(); select != pthis->m_roads.rend())
		{
			_stripLinks_(select->get());
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

	void _createNode_() { pthis->m_nodes.emplace_back(std::make_unique<DNode>(pthis->m_r, mousePosition())); }

	void _startSim_()
	{
		pthis->m_roads.emplace_back(m_selected_node.clear());
		pthis->m_state.set<SCompile>(pthis);
	}

	void _spawnLine_()
	{
		DNode *fromNode = nullptr;

		if (m_selected_node.get()->outNode().isNodeOnMouse())
			fromNode = &m_selected_node.get()->outNode();
		else if (const auto select = pthis->m_nodes.nodeOnMouse(); select != pthis->m_nodes.rend())
			fromNode = select->get();
		else
			return;

		m_linePlot.spawn(fromNode);
	}

	void _select_()
	{
		if (auto select = pthis->m_roads.trafficNodeOnMouse(); select != pthis->m_roads.rend())
			if (*select = std::move(m_selected_node.select(std::move(*select))); !*select)
				ctl::fastRemove(pthis->m_roads, select.base() - 1);
	}

	void _translateLine_(const SDL_Event &e) { m_line_plot.translateEnd({ e.motion.x, e.motion.y }); }

	DNode *_findNode_()
	{
		if (auto select = pthis->m_nodes.nodeOnMouse(); select != pthis->m_nodes.rend())
			return select->get();

		if (auto select = pthis->m_roads.trafficNodeOnMouse(); select != pthis->m_roads.rend())
			return &(*select)->inNode();

		return nullptr;
	}

	void _putLine_()
	{
		if (DNode *toNode = _findNode_(); toNode)
		{
			if (auto select = pthis->m_links.findSameLink(m_linePlot.get()->fromNode(), toNode);
				select != pthis->m_links.end())
			{
				m_selected_node.get()->lines.emplace_back(select->get());
				m_linePlot.clear();
			}
			else
				m_selected_node.get()->lines.emplace_back(pthis->m_links.emplace_back(m_linePlot.place(toNode)).get());

			m_selected_node.get()->nodes.emplace_back(toNode);
		}
		else
			m_linePlot.clear();
	}
};

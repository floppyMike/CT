
class App::SSetup : public sdl::IState
{
public:
	SSetup(App* p)
		: pthis(p)
		, m_selectedNode(p->m_r)
		, m_linePlot(p->m_r)
	{
	}

	void input(const SDL_Event& e) override
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			if (e.key.repeat == 0)
				switch (e.key.keysym.sym)
				{
				case SDLK_c:
					_createTrafficLightOnMouse_();
					break;

				case SDLK_d:
					_deleteTrafficNode_();
					//_deleteNode_();
					break;

				case SDLK_p:
					_createNode_();
					break;

				case SDLK_s:
					if (!m_linePlot.isMade())
						_startSim_();
					break;

				default:
					break;
				}
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (m_selectedNode.isSelected())
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

		default:
			break;
		}
	}

	void draw() override
	{
		m_linePlot.draw();

		for (auto& i : pthis->m_roads)
		{
			i->draw();

			pthis->m_r->color(sdl::BLACK);
			for (const auto& i : i->lines)
				i->draw();
		}

		m_selectedNode.draw();
	}

private:
	App* pthis;

	Selected m_selectedNode;
	LinePlotter m_linePlot;


	void _createTrafficLightOnMouse_()
	{
		auto prev = m_selectedNode.select(std::make_unique<DTrafficNode>(pthis->m_r, mousePosition()));
		
		if (prev)
			pthis->m_roads.emplace_back(std::move(prev));
	}

	void _stripLinks_(DTrafficNode* node)
	{
		pthis->m_links.eraseLinesToNode(&node->inNode());
		pthis->m_links.eraseLinesToNode(&node->outNode());
	}

	void _deleteTrafficNode_()
	{
		if (m_selectedNode.isSelected() && m_selectedNode.get()->isTraffNodeOnMouse())
		{
			_stripLinks_(m_selectedNode.get());
			m_selectedNode.clear();
		}

		else if (auto select = pthis->m_roads.trafficNodeOnMouse(); select != pthis->m_roads.rend())
		{
			_stripLinks_(select->get());
			ctl::fastRemove(pthis->m_roads, select.base() - 1);
		}
	}

	//void _deleteNode_()
	//{
	//	if (auto select = pthis->m_nodes.nodeOnMouse(); select != pthis->m_nodes.rend())
	//	{
	//		pthis->m_roads.removeNode(select->get());

	//		pthis->m_links.eraseLinesToNode(select->get());
	//		pthis->m_nodes.erase(select.base() - 1);
	//	}
	//}

	void _createNode_()
	{
		pthis->m_nodes.emplace_back(std::make_unique<DNode>(pthis->m_r, mousePosition()));
	}

	void _startSim_()
	{
		pthis->m_roads.emplace_back(m_selectedNode.clear());
		pthis->m_state.set<SCompile>(pthis);
	}

	void _spawnLine_()
	{
		DNode* fromNode = nullptr;

		if (m_selectedNode.get()->outNode().isNodeOnMouse())
			fromNode = &m_selectedNode.get()->outNode();
		else
			if (const auto select = pthis->m_nodes.nodeOnMouse(); select != pthis->m_nodes.rend())
				fromNode = select->get();
			else
				return;

		m_linePlot.spawn(fromNode);
	}

	void _select_()
	{
		if (auto select = pthis->m_roads.trafficNodeOnMouse(); select != pthis->m_roads.rend())
			if (*select = std::move(m_selectedNode.select(std::move(*select))); !*select)
				ctl::fastRemove(pthis->m_roads, select.base() - 1);
	}

	void _translateLine_(const SDL_Event& e)
	{
		m_linePlot.translateEnd({ e.motion.x, e.motion.y });
	}

	DNode* _findNode_()
	{
		if (auto select = pthis->m_nodes.nodeOnMouse(); select != pthis->m_nodes.rend())
			return select->get();

		if (auto select = pthis->m_roads.trafficNodeOnMouse(); select != pthis->m_roads.rend())
			return &(*select)->inNode();

		return nullptr;
	}

	void _putLine_()
	{
		if (DNode* toNode = _findNode_(); toNode)
		{
			if (auto select = pthis->m_links.findSameLink(m_linePlot.get()->fromNode(), toNode); select != pthis->m_links.end())
			{
				m_selectedNode.get()->lines.emplace_back(select->get());
				m_linePlot.clear();
			}
			else
				m_selectedNode.get()->lines.emplace_back(pthis->m_links.emplace_back(m_linePlot.place(toNode)).get());

			m_selectedNode.get()->nodes.emplace_back(toNode);
		}
		else
			m_linePlot.clear();
	}
};
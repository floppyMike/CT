
class App::SSetup : public sdl::IState
{
public:
	SSetup(App* p)
		: pthis(p)
		, m_selectedNode(p->m_r)
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
					_deleteNode_();
					break;

				case SDLK_p:
					_createNode_();
					break;

				case SDLK_s:
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
			if (m_onMouseLine)
				_putLine_();
			break;

		case SDL_MOUSEMOTION:
			if (m_onMouseLine)
				_translateLine_(e);
			break;

		default:
			break;
		}
	}

	void draw() override
	{
		for (auto& i : pthis->m_roads)
		{
			i->draw();

			pthis->m_r->setColor(sdl::BLACK);
			for (const auto& i : i->lines)
				i->draw();
		}

		m_selectedNode.draw();
	}

private:
	App* pthis;

	DLink* m_onMouseLine;
	Selected m_selectedNode;


	void _createTrafficLightOnMouse_()
	{
		auto prev = m_selectedNode.select(std::make_unique<TrafficNode>(pthis->m_r, mousePosition()));
		
		if (prev)
			pthis->m_roads.emplace_back(std::move(prev));
	}

	void _deleteTrafficNode_()
	{
		auto select = pthis->m_roads.trafficNodeOnMouse();

		if (select != pthis->m_roads.rend())
		{
			pthis->m_links.eraseLinesToNode(&(*select)->inNode());
			pthis->m_links.eraseLinesToNode(&(*select)->outNode());

			if (m_selectedNode.isSelected(select->get()))
				m_selectedNode.clear();

			pthis->m_roads.erase(select.base() - 1);
		}
	}

	void _deleteNode_()
	{
		const auto mousePos = mousePosition();

		auto select = pthis->m_nodes.nodeOnMouse();

		if (select != pthis->m_nodes.rend())
		{
			pthis->m_links.eraseLinesToNode(select->get());
			pthis->m_nodes.erase(select.base() - 1);
		}
	}

	void _createNode_()
	{
		pthis->m_nodes.emplace_back(std::make_unique<DNode>(pthis->m_r, mousePosition()));
	}

	void _startSim_()
	{
		pthis->m_state.set<SSimulation>(pthis);
	}

	void _spawnLine_()
	{
		const auto mousePos = mousePosition();

		DNode* fromNode = nullptr;

		if (m_selectedNode.get()->outNode().isNodeOnMouse())
			fromNode = &m_selectedNode.get()->outNode();
		else
		{
			const auto select = pthis->m_nodes.nodeOnMouse();

			if (select != pthis->m_nodes.rend())
				fromNode = select->get();
			else
				return;
		}

		m_onMouseLine = &pthis->m_links.emplace_back(std::make_unique<DLink>(pthis->m_r,
			sdl::Line{ { fromNode->shape().x + 2, fromNode->shape().y + 2 }, mousePos }))->fromNode(fromNode);

		m_selectedNode.get()->nodes.emplace_back(fromNode);
		m_selectedNode.get()->lines.emplace_back(m_onMouseLine);
	}

	void _select_()
	{
		auto select = pthis->m_roads.trafficNodeOnMouse();

		if (select != pthis->m_roads.rend())
			*select = std::move(m_selectedNode.select(std::move(*select)));
	}

	void _translateLine_(const SDL_Event& e)
	{
		m_onMouseLine->shape({ m_onMouseLine->shape().pos1(), { e.motion.x, e.motion.y } });
	}

	void _putLine_()
	{
		const auto mousePos = mousePosition();

		DNode* toNode = nullptr;

		auto select = pthis->m_nodes.nodeOnMouse();

		if (select != pthis->m_nodes.rend())
			toNode = select->get();
		else
		{
			auto select = pthis->m_roads.trafficNodeOnMouse();

			if (select != pthis->m_roads.rend())
				toNode = &(*select)->inNode();
			else
				toNode = nullptr;
		}

		if (toNode != nullptr)
		{
			auto select = std::find_if(pthis->m_links.begin(), pthis->m_links.end() - 1, 
				[this, &toNode](const auto& l) { return l->compareWith(m_selectedNode.get()->nodes.back()) && l->compareWith(toNode); });

			if (select != pthis->m_links.end() - 1)
			{
				pthis->m_links.pop_back();
				m_selectedNode.get()->lines.back() = select->get();
				m_onMouseLine = select->get();
			}
			else
				m_onMouseLine->shape({ m_onMouseLine->shape().pos1(), { toNode->shape().pos() + sdl::Point(2, 2) } }).toNode(toNode);
		}
		else
		{
			pthis->m_links.pop_back();
			m_selectedNode.get()->lines.pop_back();
		}

		m_onMouseLine = nullptr;
	}
};
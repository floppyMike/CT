
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
		m_selectedNode.draw();
	}

private:
	App* pthis;

	Link* m_onMouseLine;
	Selected m_selectedNode;


	auto _mousePos_()
	{
		sdl::Point<int> pos;
		SDL_GetMouseState(&pos.x, &pos.y);
		return pos;
	}

	auto _nodeOnMouse_()
	{
		const auto mousePos = _mousePos_();

		auto select = std::find_if(pthis->m_nodes.rbegin(), pthis->m_nodes.rend(), [&mousePos](const auto& n)
			{ return sdl::collision(n->shape(), mousePos); });

		return select;
	}

	auto _trafficNodeOnMouse_()
	{
		const auto mousePos = _mousePos_();

		auto select = std::find_if(pthis->m_roads.rbegin(), pthis->m_roads.rend(), [&mousePos](const auto& n)
			{ return sdl::collision(n->light.shape(), mousePos); });

		return select;
	}

	void _eraseLinesToNode_(Node* ptr)
	{
		for (auto& i : pthis->m_roads)
			i->lines.erase(std::remove_if(i->lines.begin(), i->lines.end(),
				[&ptr](const auto& n) { return n.compareWith(ptr); }), i->lines.end());
	}

	void _createTrafficLightOnMouse_()
	{
		pthis->m_roads.emplace_back(std::make_unique<TrafficNode>(pthis->m_r, _mousePos_()));
	}

	void _deleteTrafficNode_()
	{
		const auto mousePos = _mousePos_();

		auto select = _trafficNodeOnMouse_();

		if (select != pthis->m_roads.rend())
		{
			_eraseLinesToNode_(&(*select)->light.inNode());
			_eraseLinesToNode_(&(*select)->light.outNode());

			if (m_selectedNode.get() == select->get())
				m_selectedNode.clear();

			pthis->m_roads.erase(select.base() - 1);
		}
	}

	void _deleteNode_()
	{
		const auto mousePos = _mousePos_();

		auto select = _nodeOnMouse_();

		if (select != pthis->m_nodes.rend())
		{
			_eraseLinesToNode_(select->get());
			pthis->m_nodes.erase(select.base() - 1);
		}
	}

	void _createNode_()
	{
		pthis->m_nodes.emplace_back(std::make_unique<Node>(pthis->m_r, _mousePos_()));
	}

	void _startSim_()
	{
		pthis->m_state.set<SSimulation>(pthis);
	}

	void _spawnLine_()
	{
		const auto mousePos = _mousePos_();

		Node* fromNode = nullptr;
		if (sdl::collision(m_selectedNode.get()->light.outNode().shape(), mousePos))
			fromNode = &m_selectedNode.get()->light.outNode();
		else
		{
			const auto select = _nodeOnMouse_();

			if (select != pthis->m_nodes.rend())
				fromNode = select->get();
			else
				return;
		}

		m_onMouseLine = &m_selectedNode.get()->lines.emplace_back(pthis->m_r,
			sdl::Line{ { fromNode->shape().x + 2, fromNode->shape().y + 2 }, mousePos }).fromNode(fromNode);

		m_selectedNode.get()->nodes.emplace_back(fromNode);
	}

	void _select_()
	{
		const auto mousePos = _mousePos_();;

		auto select = _trafficNodeOnMouse_();

		if (select != pthis->m_roads.rend())
			m_selectedNode.select(select->get());
	}

	void _translateLine_(const SDL_Event& e)
	{
		m_onMouseLine->shape({ m_onMouseLine->shape().pos1(), { e.motion.x, e.motion.y } });
	}

	void _putLine_()
	{
		const auto mousePos = _mousePos_();

		Node* toNode = nullptr;

		auto select = _nodeOnMouse_();

		if (select != pthis->m_nodes.rend())
			toNode = select->get();
		else
		{
			auto select = _trafficNodeOnMouse_();

			if (select != pthis->m_roads.rend())
				toNode = &(*select)->light.inNode();
			else
				toNode = nullptr;
		}

		if (toNode != nullptr)
			m_onMouseLine->shape({ m_onMouseLine->shape().pos1(), { toNode->shape().pos() + sdl::Point(2, 2) } }).toNode(toNode);
		else
			m_selectedNode.get()->lines.pop_back();

		m_onMouseLine = nullptr;
	}
};
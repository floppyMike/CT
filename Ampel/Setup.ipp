
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
			_putLine_();
			break;

		case SDL_MOUSEMOTION:
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

	void _createTrafficLightOnMouse_()
	{
		pthis->m_roads.emplace_back(pthis->m_r, _mousePos_());
	}

	void _deleteTrafficNode_()
	{
		const auto mousePos = _mousePos_();

		auto select = std::find_if(pthis->m_roads.rbegin(), pthis->m_roads.rend(), [&mousePos](const TrafficNode& n)
			{ return sdl::collision(n.light.shape(), mousePos); });

		if (select != pthis->m_roads.rend())
			pthis->m_roads.erase(select.base() - 1);
	}

	void _deleteNode_()
	{
		const auto mousePos = _mousePos_();

		auto select = std::find_if(pthis->m_nodes.rbegin(), pthis->m_nodes.rend(), [&mousePos](const Node& n)
			{ return sdl::collision(n.shape(), mousePos); });

		auto* ptr = &*select;

		pthis->m_lines.erase(std::remove_if(pthis->m_lines.begin(), pthis->m_lines.end(),
			[&ptr](const Link& n) { return n.compareWith(ptr); }), pthis->m_lines.end());

		if (select != pthis->m_nodes.rend())
			pthis->m_nodes.erase(select.base() - 1);
	}

	void _createNode_()
	{
		pthis->m_nodes.emplace_back(pthis->m_r, _mousePos_());
	}

	void _startSim_()
	{
		pthis->m_state.set<SSimulation>(pthis);
	}

	void _spawnLine_()
	{
		const auto mousePos = _mousePos_();

		Node* fromNode = nullptr;
		if (sdl::collision(m_selectedNode.get().light.outNode().shape(), mousePos))
			fromNode = &m_selectedNode.get().light.outNode();
		else
		{
			auto select = std::find_if(pthis->m_nodes.rbegin(), pthis->m_nodes.rend(), [&mousePos](const Node& r)
				{ return sdl::collision(r.shape(), mousePos); });

			if (select != pthis->m_nodes.rend())
				fromNode = &*select;
			else
				return;
		}

		m_onMouseLine = &pthis->m_lines.emplace_back(pthis->m_r, 
			sdl::Line{ { fromNode->shape().x + 2, fromNode->shape().y + 2 }, mousePos }).fromNode(fromNode);

		m_selectedNode.get().nodes.emplace_back(fromNode);
		m_selectedNode.get().lines.emplace_back(m_onMouseLine);
	}

	void _select_()
	{
		const auto mousePos = _mousePos_();;

		auto select = std::find_if(pthis->m_roads.rbegin(), pthis->m_roads.rend(), [&mousePos](const TrafficNode& n)
			{ return sdl::collision(n.light.shape(), mousePos); });

		if (select != pthis->m_roads.rend())
			m_selectedNode.select(select->get());
	}

	void _translateLine_(const SDL_Event& e)
	{
		if (m_onMouseLine != nullptr)
			m_onMouseLine->shape({ m_onMouseLine->shape().pos1(), { e.motion.x, e.motion.y } });
	}

	void _putLine_()
	{
		if (m_onMouseLine != nullptr)
		{
			const auto mousePos = _mousePos_();

			Node* toNode = nullptr;

			auto select = std::find_if(pthis->m_nodes.rbegin(), pthis->m_nodes.rend(), [&mousePos](const Node& r)
				{ return sdl::collision(r.shape(), mousePos); });

			if (select != pthis->m_nodes.rend())
				toNode = &*select;
			else
			{
				auto select = std::find_if(pthis->m_roads.rbegin(), pthis->m_roads.rend(), [&mousePos](const TrafficNode& n)
					{ return sdl::collision(n.light.inNode().shape(), mousePos); });

				if (select != pthis->m_roads.rend())
					toNode = &select->light.inNode();
				else
					toNode = nullptr;
			}

			if (toNode != nullptr)
				m_onMouseLine->shape({ m_onMouseLine->shape().pos1(), { toNode->shape().pos() + sdl::Point(2, 2) } }).toNode(toNode);
			else
				pthis->m_lines.pop_back();

			m_onMouseLine = nullptr;
		}
	}
};
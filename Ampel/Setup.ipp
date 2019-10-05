
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
					_deleteObject_();
					break;

				case SDLK_p:
					_createNode_();
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

	sdl::LineDraw<>* m_onMouseLine;
	Selected m_selectedNode;


	void _createTrafficLightOnMouse_()
	{
		sdl::Point<int> pos;
		SDL_GetMouseState(&pos.x, &pos.y);

		pthis->m_roads.emplace_back(pthis->m_r, pos);
	}

	void _deleteObject_()
	{
		sdl::Point<int> pos;
		SDL_GetMouseState(&pos.x, &pos.y);

		auto select = std::find_if(pthis->m_roads.rbegin(), pthis->m_roads.rend(), [&pos](const TrafficNode& n)
			{ return sdl::collision(n.light.shape(), pos); });

		if (select != pthis->m_roads.rend())
			pthis->m_roads.erase(select.base() - 1);
	}

	void _createNode_()
	{
		sdl::Point<int> pos;
		SDL_GetMouseState(&pos.x, &pos.y);

		pthis->m_nodes.emplace_back(pthis->m_r, pos);
	}

	void _spawnLine_()
	{
		sdl::Point<int> pos;
		SDL_GetMouseState(&pos.x, &pos.y);

		Node* fromNode = nullptr;
		if (sdl::collision(m_selectedNode.get().light.outNode().shape(), pos))
			fromNode = &m_selectedNode.get().light.outNode();
		else
		{
			auto select = std::find_if(pthis->m_nodes.rbegin(), pthis->m_nodes.rend(), [&pos](const Node& r)
				{ return sdl::collision(r.shape(), pos); });

			if (select != pthis->m_nodes.rend())
				fromNode = &*select;
			else
				return;
		}

		m_onMouseLine = &pthis->m_lines.emplace_back(pthis->m_r).shape({ { fromNode->shape().x + 2, fromNode->shape().y + 2 }, pos });

		m_selectedNode.get().nodes.emplace_back(fromNode);
		m_selectedNode.get().lines.emplace_back(m_onMouseLine);
	}

	void _select_()
	{
		sdl::Point<int> pos;
		SDL_GetMouseState(&pos.x, &pos.y);

		auto select = std::find_if(pthis->m_roads.rbegin(), pthis->m_roads.rend(), [&pos](const TrafficNode& n)
			{ return sdl::collision(n.light.shape(), pos); });

		if (select != pthis->m_roads.rend())
			m_selectedNode.select(&*select);
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
			sdl::Point<int> pos;
			SDL_GetMouseState(&pos.x, &pos.y);

			Node* toNode = nullptr;

			auto select = std::find_if(pthis->m_nodes.rbegin(), pthis->m_nodes.rend(), [&pos](const Node& r)
				{ return sdl::collision(r.shape(), pos); });

			if (select != pthis->m_nodes.rend())
				toNode = &*select;
			else
			{
				auto select = std::find_if(pthis->m_roads.rbegin(), pthis->m_roads.rend(), [&pos](const TrafficNode& n)
					{ return sdl::collision(n.light.inNode().shape(), pos); });

				if (select != pthis->m_roads.rend())
					toNode = &select->light.inNode();
				else
					toNode = nullptr;
			}

			if (toNode != nullptr)
				m_onMouseLine->shape({ m_onMouseLine->shape().pos1(), { toNode->shape().pos() + sdl::Point(2, 2) } });
			else
				pthis->m_lines.pop_back();

			m_onMouseLine = nullptr;
		}
	}
};
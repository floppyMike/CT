
class App::SSetup : public sdl::IState
{
public:
	SSetup(App* p)
		: pthis(p)
		, m_seperator(p->m_r)
		, m_selectedNode(p->m_r)
	{
		const auto xCoord = WINDOW_SIZE.w * 3 >> 2;
		m_seperator.shape({ xCoord, -1, 5, WINDOW_SIZE.h + 2 });
	}

	void input(const SDL_Event& e) override
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			_createTrafficLightOnMouse_(e);
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (m_selectedNode.isSelected())
				_spawnLine_(e);
			_select_();
			break;

		case SDL_MOUSEBUTTONUP:
			_putLine_(e);
			break;

		case SDL_MOUSEMOTION:
			_translateBasedOnMov_(e);
			break;

		default:
			break;
		}
	}

	void update() override
	{

	}

	void draw() override
	{
		m_seperator.renderer()->setColor(sdl::BLACK);
		m_seperator.draw();

		m_selectedNode.draw();


	}

private:
	App* pthis;

	sdl::RectDraw<> m_seperator;
	sdl::LineDraw<>* m_onMouseLine;

	Selected m_selectedNode;


	void _createTrafficLightOnMouse_(const SDL_Event& e)
	{
		sdl::Point<int> pos;
		SDL_GetMouseState(&pos.x, &pos.y);

		switch (e.key.keysym.sym)
		{
		case SDLK_c:
			if (e.key.repeat == 0 &&
				sdl::collision(sdl::Rect(0, 0, (WINDOW_SIZE.w * 3 >> 2) - LightPair::TOTAL_WIDTH, WINDOW_SIZE.h), pos))
			{
				m_selectedNode.select(&pthis->m_roads.push(pthis->m_r, pos));
			}
			break;

		case SDLK_d:
			if (e.key.repeat == 0)
			{
				auto select = std::find_if(pthis->m_roads.rbegin(), pthis->m_roads.rend(), [&pos](const TrafficNode& n)
					{
						return sdl::collision(n.light.shape(), pos);
					});

				if (select != pthis->m_roads.rend())
					pthis->m_roads.erase(select.base() - 1);
			}
			break;

		case SDLK_p:
			if (e.key.repeat == 0)
			{
				pthis->m_nodes.emplace_back(pthis->m_r, pos);
			}
			break;

		default:
			break;
		}
	}

	void _spawnLine_(const SDL_Event& e)
	{
		sdl::Point<int> pos;
		SDL_GetMouseState(&pos.x, &pos.y);

		Node* fromNode = nullptr;
		if (sdl::collision(m_selectedNode.get().light.inNode().shape(), pos))
			fromNode = &m_selectedNode.get().light.inNode();
		else
		{
			auto select = std::find_if(pthis->m_nodes.rbegin(), pthis->m_nodes.rend(), [&pos](const Node& r)
				{
					return sdl::collision(r.shape(), pos);
				});

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
			{
				return sdl::collision(n.light.shape(), pos);
			});

		if (select != pthis->m_roads.rend())
			m_selectedNode.select(&*select);
		else
			m_selectedNode.clear();
	}

	void _translateBasedOnMov_(const SDL_Event& e)
	{
		if (m_onMouseLine != nullptr)
			m_onMouseLine->shape({ m_onMouseLine->shape().pos1(), { e.motion.x, e.motion.y } });
	}

	void _putLine_(const SDL_Event& e)
	{
		sdl::Point<int> pos;
		SDL_GetMouseState(&pos.x, &pos.y);

		if (m_onMouseLine != nullptr)
		{
			auto select = std::find_if(pthis->m_nodes.rbegin(), pthis->m_nodes.rend(), [&pos](const Node& r)
				{
					return sdl::collision(r.shape(), pos);
				});

			if (select != pthis->m_nodes.rend())
			{
				m_onMouseLine->shape({ m_onMouseLine->shape().pos1(), { select->shape().pos() + sdl::Point(2, 2) } });
			}
			else
				pthis->m_lines.pop_back();

			m_onMouseLine = nullptr;
		}
	}
};
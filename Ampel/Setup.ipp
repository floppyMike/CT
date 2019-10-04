
class App::SSetup : public sdl::IState
{
public:
	SSetup(App* p)
		: pthis(p)
		, m_seperator(p->m_r)
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
			_handleObjectOnMouse_(e);
			break;

		case SDL_MOUSEBUTTONUP:
			m_selected = nullptr;
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
		m_seperator.renderer()->setColor({ 0, 0, 0, 0xFF });
		m_seperator.draw();

		for (auto& i : pthis->m_roads)
			i.light.draw();
	}

private:
	App* pthis;

	sdl::RectDraw<> m_seperator;
	Road* m_selected = nullptr;


	void _createTrafficLightOnMouse_(const SDL_Event& e)
	{
		sdl::Point<int> pos;
		SDL_GetMouseState(&pos.x, &pos.y);

		switch (e.key.keysym.sym)
		{
		case SDLK_c:
			if (e.key.repeat == 0 && 
				sdl::collision(sdl::Rect(0, 0, (WINDOW_SIZE.w * 3 >> 2) - RoadLights::TOTAL_WIDTH, WINDOW_SIZE.h), pos))
				pthis->m_roads.push(pthis->m_r, pos);
			break;

		case SDLK_d:
			if (e.key.repeat == 0)
			{
				auto select = pthis->m_roads.insideWhich<RoadsDB::iterator>(pos);
				if (select != pthis->m_roads.end())
					pthis->m_roads.erase(select);
			}
			break;

		default:
			break;
		}
	}

	void _handleObjectOnMouse_(const SDL_Event& e)
	{
		sdl::Point<int> pos;
		SDL_GetMouseState(&pos.x, &pos.y);

		m_selected = pthis->m_roads.insideWhich<Road*>(pos);
	}

	void _translateBasedOnMov_(const SDL_Event& e)
	{
		if (m_selected != nullptr)
			m_selected->light.translate({ e.motion.xrel, e.motion.yrel });
	}
};
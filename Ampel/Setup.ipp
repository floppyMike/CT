
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
		{
			sdl::Point<int> pos;
			SDL_GetMouseState(&pos.x, &pos.y);

			if (e.key.repeat == 0 && e.key.keysym.sym == SDLK_c && 
				sdl::collision(sdl::Rect(0, 0, (WINDOW_SIZE.w * 3 >> 2) - RoadLights::TOTAL_WIDTH, WINDOW_SIZE.h), pos))
			{
				pthis->m_lights.emplace_back(pthis->m_r, pos);
			}

			break;
		}

		case SDL_MOUSEBUTTONDOWN:
		{
			sdl::Point<int> pos;
			SDL_GetMouseState(&pos.x, &pos.y);

			m_selected = pthis->insideWhich(pos);

			break;
		}

		case SDL_MOUSEBUTTONUP:
			m_selected = nullptr;
			break;

		case SDL_MOUSEMOTION:
			if (m_selected != nullptr)
			{
				m_selected->light.translate({ e.motion.xrel, e.motion.yrel });
			}
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

		for (auto& i : pthis->m_lights)
			i.light.draw();
	}

private:
	App* pthis;

	sdl::RectDraw<> m_seperator;
	Road* m_selected = nullptr;
};
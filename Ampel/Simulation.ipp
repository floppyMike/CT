

class App::SSimulation : public sdl::IState
{
public:
	SSimulation(App* app, Sequence&& seq)
		: pthis(app)
		, m_seq(std::move(seq))
	{
		*pthis->m_doRender = true;
	}

	void update() override
	{
		
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
	}

private:
	App* pthis;
	Sequence m_seq;
};



class App::SSimulation : public sdl::IState
{
public:
	static constexpr std::chrono::seconds DURATION = 10s;

	SSimulation(App* app, SequenceDB&& seq)
		: pthis(app)
		, m_seq(std::move(seq))
		, m_iter(m_seq.begin())
		, m_dur(std::chrono::steady_clock::now() + DURATION)
	{
		*pthis->m_doRender = true;

		for (auto& i : *m_iter)
			(*i)->flipTo(RoadLights::TrafficState::PASSING);
	}

	void update() override
	{
		for (auto& i : pthis->m_roads)
			i->update();

		if (std::chrono::steady_clock::now() >= m_dur)
		{
			for (auto& i : *m_iter)
				(*i)->flipTo(RoadLights::TrafficState::STOPPED);

			_jumpNext_();
			m_dur = std::chrono::steady_clock::now() + DURATION;

			for (auto& i : *m_iter)
				(*i)->flipTo(RoadLights::TrafficState::PASSING);
		}
	}

	void draw() override
	{
		for (auto& i : pthis->m_roads)
			i->draw();

		for (auto& i : *m_iter)
		{
			pthis->m_r->setColor(sdl::RED);
			for (const auto& i : (*i)->lines)
				i->draw();
		}
	}

private:
	App* pthis;

	SequenceDB m_seq;
	SequenceDB::iterator m_iter;

	std::chrono::steady_clock::time_point m_dur;


	void _jumpNext_()
	{
		if (++m_iter == m_seq.end())
			m_iter = m_seq.begin();
	}
};

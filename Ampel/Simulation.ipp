

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
			auto nextSeq = _nextIter_();

			for (auto [iterPrev, iterNew] = std::pair(m_iter->begin(), nextSeq->begin()); iterPrev != m_iter->end(); ++iterPrev)
			{
				if ((*iterPrev)->get() == (*iterNew)->get() && (**iterPrev)->state() != (**iterNew)->state())
				{
					(**iterNew)->flip();
					++iterNew;
				}
			}

			m_iter = nextSeq;
			m_dur = std::chrono::steady_clock::now() + DURATION;

			//for (auto& i : *m_iter)
			//{
			//	(*i)->flipTo(RoadLights::TrafficState::STOPPED);
			//}

			//_jumpNext_();
			//m_dur = std::chrono::steady_clock::now() + DURATION;

			//for (auto& i : *m_iter)
			//	(*i)->flipTo(RoadLights::TrafficState::PASSING);
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

	auto _nextIter_() noexcept -> SequenceDB::iterator
	{
		auto iter = m_iter + 1;
		if (iter == m_seq.end())
			iter = m_seq.begin();
		return iter;
	}
};

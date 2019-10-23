

class App::SSimulation : public sdl::IState
{
public:
	static constexpr std::chrono::seconds DURATION = std::chrono::seconds(10);

	SSimulation(App* app, Sequence&& seq)
		: pthis(app)
		, m_seq(std::move(seq))
		, m_iter(m_seq.begin())
		, m_dur(std::chrono::steady_clock::now() + DURATION)
	{
		*pthis->m_doRender = true;
	}

	void update() override
	{
		if (std::chrono::steady_clock::now() >= m_dur)
		{
			_jumpNext_();
			m_dur = std::chrono::steady_clock::now() + DURATION;
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

		//for (auto [trafNodeIter, markIter] = std::pair{ pthis->m_roads.begin(), m_iter->begin() }; trafNodeIter != pthis->m_roads.end(); ++trafNodeIter)
		//{
		//	(*trafNodeIter)->draw();

		//	if (markIter != m_iter->end() && trafNodeIter == *markIter)
		//	{
		//		pthis->m_r->setColor(sdl::RED);
		//		++markIter;
		//	}
		//	else
		//		pthis->m_r->setColor(sdl::BLACK);

		//	for (const auto& i : pthis->m_links)
		//		i->draw();
		//}
	}

private:
	App* pthis;

	Sequence m_seq;
	Sequence::iterator m_iter;

	std::chrono::steady_clock::time_point m_dur;


	void _jumpNext_()
	{
		if (++m_iter == m_seq.end())
			m_iter = m_seq.begin();
	}
};


class App::SCompile : public sdl::IState
{
public:
	SCompile(App* app)
		: pthis(app)
	{
		pthis->m_doRender = false;
		m_seqGen = std::async(std::launch::async, [this] { return _generate_(); });
	}

	void update() override
	{
		if (m_seqGen.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
			pthis->m_state.set<App::SSimulation>(pthis, std::move(m_seqGen.get()));
	}

	void draw() override
	{

	}

private:
	App* pthis;

	std::future<std::vector<std::vector<decltype(pthis->m_roads.begin())>>> m_seqGen;


	void _eraseDupe_()
	{
		for (auto& i : pthis->m_roads)
			i->nodes.erase(std::unique(i->nodes.begin(), i->nodes.end()), i->nodes.end());
	}

	std::vector<std::vector<decltype(pthis->m_roads.begin())>> _generate_()
	{
		_eraseDupe_();

		std::vector<std::vector<decltype(pthis->m_roads.begin())>> seq(1);

		for (auto buffIter = pthis->m_roads.begin(); buffIter != pthis->m_roads.end(); ++buffIter)
		{
			seq.back().emplace_back(buffIter);

			for (auto compIter = buffIter + 1; compIter != buffIter; ++compIter)
			{
				if (compIter == pthis->m_roads.end())
					compIter = pthis->m_roads.begin();

				for (auto& seqIter : seq.back())
					if (std::find_first_of((*compIter)->nodes.begin(), (*compIter)->nodes.end(), 
						(*seqIter)->nodes.begin(), (*seqIter)->nodes.end()) != (*compIter)->nodes.end())
					{
						seq.back().emplace_back(compIter);
					}
			}
		}


		return seq;
	}
};

class App::SCompile : public sdl::IState
{
public:
	SCompile(App* app)
		: pthis(app)
	{
		*pthis->m_doRender = false;
		m_seqGen = std::async(std::launch::async, [this] { return _generate_(); });
	}

	void update() override
	{
		if (m_seqGen.valid() && m_seqGen.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
			pthis->m_state.set<App::SSimulation>(pthis, std::move(m_seqGen.get()));
	}

private:
	App* pthis;

	std::future<SequenceDB> m_seqGen;


	void _eraseDupe_()
	{
		for (auto& i : pthis->m_roads)
			i->nodes.erase(std::unique(i->nodes.begin(), i->nodes.end()), i->nodes.end());
	}

	auto _generate_() -> SequenceDB
	{
		_eraseDupe_();
		std::clog << "Duplicates erased.\n";

		SequenceDB seq;

		for (auto buffIter = pthis->m_roads.begin(); buffIter != pthis->m_roads.end(); ++buffIter)
		{
			std::clog << "New Traffic Squence allocate.\n";

			seq.pushRow();
			seq.push(buffIter);

			for (auto compIter = buffIter + 1; compIter != buffIter;)
			{
				if (compIter == pthis->m_roads.end())
				{
					std::clog << "Loop reset.\n";
					compIter = pthis->m_roads.begin();
					continue;
				}

				std::clog << "Element address: " << compIter->get() << '\n';

				if (!seq.checkIfUsed(compIter))
					std::clog << "Element push.\n";
					seq.push(compIter);

				++compIter;
			}
		}

		seq.makeUnique();

		
		return seq;
	}
};

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
		if (m_seqGen.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
			pthis->m_state.set<App::SSimulation>(pthis, std::move(m_seqGen.get()));
	}

	void draw() override
	{
		return;
	}

private:
	App* pthis;

	std::future<Sequence> m_seqGen;


	void _eraseDupe_()
	{
		for (auto& i : pthis->m_roads)
			i->nodes.erase(std::unique(i->nodes.begin(), i->nodes.end()), i->nodes.end());
	}

	auto _generate_() -> Sequence
	{
		_eraseDupe_();

		Sequence seq;

		for (auto buffIter = pthis->m_roads.begin(); buffIter != pthis->m_roads.end(); ++buffIter)
		{
			seq.push(buffIter);

			for (auto compIter = buffIter + 1; compIter != buffIter;)
			{
				if (compIter == pthis->m_roads.end())
				{
					compIter = pthis->m_roads.begin();
					continue;
				}

				if (!seq.checkIfUsed(compIter))
					seq.push(compIter);

				++compIter;
			}

			seq.pushRow();
		}


		return seq;
	}
};
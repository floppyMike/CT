
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
		auto ass = m_seqGen.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready;
	}

	void draw() override
	{

	}

private:
	App* pthis;

	std::future<std::vector<bool>> m_seqGen;


	void _eraseDupe_()
	{
		for (auto& i : pthis->m_roads)
			i->nodes.erase(std::unique(i->nodes.begin(), i->nodes.end()), i->nodes.end());
	}

	std::vector<bool> _generate_()
	{
		_eraseDupe_();
		std::clog << "Duplicates erased.\n";

		std::vector<decltype(pthis->m_roads.begin())> orderedList(pthis->m_roads.size());
		std::generate(orderedList.begin(), orderedList.end(), [beg = pthis->m_roads.begin()]() mutable { return beg++; });
		std::clog << "Buffer generated.\n";

		std::sort(orderedList.begin(), orderedList.end(), [](auto i1, auto i2) { return (*i1)->nodes.size() < (*i2)->nodes.size(); });
		std::clog << "Buffer sorted.\n";

		std::vector<std::vector<decltype(pthis->m_roads.begin())>> seq(1);

		for (auto buffIter = orderedList.begin(); buffIter != orderedList.end(); ++buffIter)
		{
			for (auto& seqIter : seq.back())
				if (std::find_first_of((*seqIter)->nodes.begin(), (*seqIter)->nodes.end(),
					(**buffIter)->nodes.begin(), (**buffIter)->nodes.end()) == (*seqIter)->nodes.end())
				{
					seq.back().emplace_back(*buffIter);
				}
		}

		for (size_t seqIndex = 0; seqIndex < seq.size(); ++seqIndex)
		{
			for (auto& i : orderedList)
			{
				for (auto iter = (*i)->nodes.begin(); iter != (*i)->nodes.end(); ++iter)
				{
					if (seq[seqIndex][std::distance(pthis->m_roads.begin(), iter)])
					{

					}
				}
			}
		}


		return std::vector<bool>();
	}
};
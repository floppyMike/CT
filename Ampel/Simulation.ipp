

class App::SSimulation : public sdl::IState
{
public:
	SSimulation(App* app)
		: pthis(app)
	{
		m_seqGen = std::async(std::launch::async, [] { return Sequence(); });
	}

	void draw() override
	{

	}

private:
	App* pthis;

	std::future<Sequence> m_seqGen;
};

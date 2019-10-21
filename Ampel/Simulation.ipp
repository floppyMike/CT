

class App::SSimulation : public sdl::IState
{
public:
	SSimulation(App* app, Sequence&& seq)
		: pthis(app)
	{
		*pthis->m_doRender = true;
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
};

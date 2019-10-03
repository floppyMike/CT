
class App::SSetup : public sdl::IState
{
public:
	SSetup(App* p)
		: pthis(p)
		, m_seperator(p->m_r)
		, m_test(p->m_r, { 50, 50 })
	{
		const auto xCoord = WINDOW_SIZE.w * 3 >> 2;
		m_seperator.shape({ xCoord, -1, 5, WINDOW_SIZE.h + 2 });
	}

	void draw() override
	{
		m_seperator.renderer()->setColor({ 0, 0, 0, 0xFF });
		m_seperator.draw();
		m_test.draw();
	}

private:
	App* pthis;

	sdl::RectDraw<> m_seperator;
	RoadLights m_test;
};
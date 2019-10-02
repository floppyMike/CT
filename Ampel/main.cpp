#include <SDL.h>
#include <CustomLibrary/SDL/SDLWindow.h>
#include <CustomLibrary/SDL/Engine.h>
#include <CustomLibrary/SDL/Geometry.h>
#include <CustomLibrary/SDL/Button.h>
#include <CustomLibrary/SDL/Event.h>

using namespace ctl;
using namespace std::chrono_literals;

/* SDL Update List:
- Replace "ImplRend" template with SDL_Renderer* -> Removes a lot of complexity
- Implement missing asserts
- Rename Renderer::clear to fill
- Implement crtp for drawable Geometric Shapes
*/

enum Events
{
	BUTTON_PRESS
};


class Light
{
	static constexpr std::array<SDL_Color, 3> COLORS = { sdl::RED, sdl::YELLOW, sdl::GREEN };

public:
	enum Color { RED, YELLOW, GREEN };

	Light(sdl::Renderer* rend, const sdl::Circle<int, Uint32>& c, Color col) noexcept
		: m_circle(rend)
		, m_color(col)
	{
		m_circle.shape(c);
	}

	Light& flipSwitch() noexcept
	{
		m_on = !m_on;
		return *this;
	}

	Light& change(bool s) noexcept
	{
		m_on = s;
		return *this;
	}

	void draw() const
	{
		if (m_on)
		{
			m_circle.renderer()->setColor(COLORS[m_color]);
			m_circle.drawFilled();
		}

		m_circle.renderer()->setColor({ 0, 0, 0, 0xFF });
		m_circle.draw();
	}

private:
	sdl::CircleDraw<> m_circle;
	Color m_color;
	bool m_on = false;
};


class LightBox
{
public:
	LightBox(sdl::Renderer* r, const sdl::Point<int>& coord, int width, std::initializer_list<Light::Color>&& colors)
		: m_box(r)
	{
		sdl::Dim<int> dim;
		dim.w = width;

		const Uint32 radius = width * 3 >> 3;
		const auto pause = width >> 2;

		dim.h = 2 * radius * colors.size() + pause * (colors.size() + 1);
		m_box.shape({ coord, dim });

		m_lights.reserve(colors.size());
		for (int i = 0; i < colors.size(); ++i)
		{
			sdl::Circle<int, Uint32> cir(coord.x + (width >> 1), coord.y + pause + radius + i * ((radius << 1) + pause), radius);
			const auto& col = *(colors.begin() + i);

			m_lights.emplace_back(r, cir, col);
		}
	}

	auto& flipLight(size_t idx)
	{
		m_lights[idx].flipSwitch();
		return *this;
	}

	auto& change(size_t idx, bool s)
	{
		m_lights[idx].change(s);
		return *this;
	}
	
	void draw()
	{
		m_box.renderer()->setColor({ 0, 0, 0, 0xFF });
		m_box.draw();

		for (const auto& i : m_lights)
			i.draw();
	}

	constexpr const auto& shape() const { return m_box.shape(); }

private:
	sdl::RectDraw<> m_box;
	std::vector<Light> m_lights;
};


class LightBody
{
	static constexpr int FLOOR = 450;

public:
	LightBody(sdl::Renderer* r, const sdl::Point<int>& coord, int width)
		: m_pole(r)
		, m_foot(r)
	{
		const auto poleWidth = width >> 2;
		const auto footHight = width >> 3;

		m_pole.shape({ coord.x + ((width - poleWidth) >> 1), coord.y, poleWidth, FLOOR - coord.y - footHight + 1 });
		m_foot.shape({ coord.x, FLOOR - footHight, width, footHight });
	}

	void draw()
	{
		m_pole.renderer()->setColor({ 0, 0, 0, 0xFF });
		m_pole.draw();
		m_foot.draw();
	}

	constexpr auto poleShape() { return m_pole.shape(); }

private:
	sdl::RectDraw<> m_pole;
	sdl::RectDraw<> m_foot;
};


class TrafficLight
{
public:
	TrafficLight(sdl::Renderer* r, const sdl::Point<int>& pos, int width, std::initializer_list<Light::Color>&& colors)
		: m_box(r, pos, width, std::move(colors))
		, m_body(r, { pos.x, pos.y + m_box.shape().h - 1 }, width)
	{
	}

	auto& flipLight(size_t idx) noexcept
	{
		m_box.flipLight(idx);
		return *this;
	}

	auto& change(size_t idx, bool s) noexcept
	{
		m_box.change(idx, s);
		return *this;
	}

	virtual void draw()
	{
		m_body.draw();
		m_box.draw();
	}

protected:
	LightBox m_box;
	LightBody m_body;
};


class Button
{
public:
	Button(sdl::Renderer* r)
		: m_box(r)
		, m_button(r)
	{
		m_button.func([this] { m_event.pushEvent(); });
		m_event.userType(Events::BUTTON_PRESS);
	}

	auto& boxShape(const sdl::Rect<int, int>& s) noexcept
	{
		m_box.shape(s);
		m_button.shape({ s.x + (s.w >> 1), s.y + (s.h >> 1), std::min<Uint32>(s.w >> 1, s.h >> 1) - (s.w >> 2) });
		return *this;
	}

	void event(const SDL_Event& e)
	{
		m_button.event(e);
	}

	void draw()
	{
		m_box.renderer()->setColor({ 0xFF, 0xFF, 0xFF, 0xFF });
		m_box.drawFilled();
		m_box.renderer()->setColor({ 0, 0, 0, 0xFF });
		m_box.draw();

		m_box.renderer()->setColor({ 128, 128, 128, 0xFF });
		m_button.drawFilled();
	}

private:
	sdl::RectDraw<> m_box;
	sdl::CircleDraw<sdl::Renderer, sdl::ButtonEx> m_button;

	sdl::UserEvent m_event;
};


class VehicleLight : public TrafficLight
{
public:
	VehicleLight(sdl::Renderer* r, const sdl::Point<int>& pos, int width, std::initializer_list<Light::Color>&& colors)
		: TrafficLight(r, pos, width, std::move(colors))
		, m_button(r)
	{
		const sdl::Dim<int> buttonBox(this->m_box.shape().w >> 1, this->m_box.shape().h >> 2);
		m_button.boxShape({ { pos.x + ((this->m_box.shape().w - buttonBox.w) >> 1),
			m_body.poleShape().y + ((m_body.poleShape().h - buttonBox.h) >> 1) }, buttonBox });
	}

	void event(const SDL_Event& e)
	{
		m_button.event(e);
	}

	void draw()
	{
		TrafficLight::draw();
		m_button.draw();
	}

private:
	Button m_button;
};


class Window
{
	using Duration = std::chrono::steady_clock::duration;

	static constexpr Duration BLINKING = 3s;
	static constexpr Duration PRESS_DELAY = 5s;
	static constexpr Duration GREEN_DURATION = 10s;

	static constexpr Duration BLINK_TICK = (1000ms / 2);

	enum class State
	{
		BLINK, PRESS, GREEN, WAIT
	};

public:
	Window()
		: m_win("Ampel", { 640, 490 })
		, m_rend(&m_win)
		, m_veh(&m_rend, { 200, 50 }, 50, { Light::RED, Light::YELLOW, Light::GREEN })
		, m_ped(&m_rend, { 400, 50 }, 50, { Light::RED, Light::GREEN })
	{
		m_time.start();

		m_veh.change(1, true);
	}

	void event(const SDL_Event& e)
	{
		switch (m_state)
		{
		case Window::State::BLINK:
			break;

		case Window::State::PRESS:
			m_veh.event(e);
			if (e.user.type == Events::BUTTON_PRESS)
			{
				m_time.start();

				m_veh.change(1, true);
				m_veh.change(0, false);
				m_veh.change(2, false);

				m_state = State::GREEN;
			}
			break;

		case Window::State::GREEN:
			break;

		default:
			break;
		}
	}

	void update()
	{
		switch (m_state)
		{
		case Window::State::BLINK:
			if (m_time.ticks<std::chrono::milliseconds>() >= BLINK_TICK)
			{
				m_point += m_time.ticks<std::chrono::milliseconds>();

				m_time.stop();
				m_time.start();

				m_veh.flipLight(1);
				if (m_point >= BLINKING)
				{
					m_state = State::PRESS;

					m_veh.change(2, true);
					m_veh.change(1, false);
					m_ped.change(0, true);

					m_time.stop();
				}
			}
			break;

		case Window::State::PRESS:
			break;

		case Window::State::GREEN:
			if (m_time.ticks<>() >= PRESS_DELAY)
			{
				m_ped.change(1, true);
				m_ped.change(0, false);
				
				m_veh.change(0, true);
				m_veh.change(1, false);

				m_time.stop();
				m_time.start();

				m_state = State::WAIT;
			}
			break;

		case State::WAIT:
			if (m_time.ticks<>() >= GREEN_DURATION)
			{
				m_ped.change(1, false);
				m_ped.change(0, true);

				m_veh.change(0, false);
				m_veh.change(2, true);

				m_time.stop();

				m_state = State::PRESS;
			}
			break;

		default:
			break;
		}
	}
	void fixedUpdate()
	{

	}
	void render()
	{
		m_rend.setColor({ 0xFF, 0xFF, 0xFF, 0xFF });
		m_rend.clear();

		m_veh.draw();
		m_ped.draw();

		m_rend.render();
	}

private:
	sdl::Window m_win;
	sdl::Renderer m_rend;

	State m_state = State::BLINK;

	ctl::Timer m_time;
	Duration m_point = Duration(0);

	VehicleLight m_veh;
	TrafficLight m_ped;
};


int main(int argc, char** argv)
{
	sdl::SDL sdl;

	Window win;
	sdl::RunLoop<decltype(win)> run;
	run.addWindow(&win);

	run.run(30);

	return 0;
}
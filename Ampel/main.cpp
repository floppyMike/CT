#include <SDL.h>
#include <CustomLibrary/SDL/SDLWindow.h>
#include <CustomLibrary/SDL/Engine.h>
#include <CustomLibrary/SDL/Geometry.h>

using namespace ctl;

/* SDL Update List:
- Replace "ImplRend" template with SDL_Renderer* -> Removes a lot of complexity
- Implement missing asserts
- Rename Renderer::clear to fill
*/


class Light
{
	static constexpr std::array<SDL_Color, 3> COLORS = { sdl::RED, sdl::YELLOW, sdl::GREEN };

public:
	enum Color { RED, YELLOW, GREEN };

	Light(sdl::Renderer* rend, const sdl::Circle<int, Uint32>& c, Color col)
		: m_circle(rend)
		, m_color(col)
	{
		m_circle.shape(c);
	}

	void draw() const
	{
		m_circle.renderer()->setColor(COLORS[m_color]);
		m_circle.drawFilled();
		m_circle.renderer()->setColor({ 0, 0, 0, 0xFF });
		m_circle.draw();
	}

private:
	sdl::CircleDraw<> m_circle;
	Color m_color;
};


class LightBox
{
public:
	LightBox(sdl::Renderer* r, const sdl::Point<int>& coord, int width, std::initializer_list<Light::Color>&& colors)
		: m_box(r)
		, m_lightFlags(colors.size(), true)
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
		m_lightFlags[idx].flip();
		return *this;
	}

	void draw()
	{
		m_box.renderer()->setColor({ 0, 0, 0, 0xFF });
		m_box.draw();

		for (auto [iterL, iterF] = std::pair(m_lights.begin(), m_lightFlags.begin()); iterL != m_lights.end(); ++iterL, ++iterF)
			if (*iterF)
				iterL->draw();
	}

	constexpr const auto& shape() const { return m_box.shape(); }

private:
	sdl::RectDraw<> m_box;

	std::vector<Light> m_lights;
	std::vector<bool> m_lightFlags;
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

	TrafficLight& flipLight(size_t idx) noexcept
	{
		m_box.flipLight(idx);
	}

	void draw()
	{
		m_body.draw();
		m_box.draw();
	}

private:
	LightBox m_box;
	LightBody m_body;
};


class Window
{
public:
	Window()
		: m_win("Ampel", { 640, 490 })
		, m_rend(&m_win)
		, m_ped(&m_rend, { 50, 50 }, 50, { Light::RED, Light::GREEN })
	{
	}

	void event(const SDL_Event& e)
	{

	}
	void update()
	{

	}
	void fixedUpdate()
	{

	}
	void render()
	{
		m_rend.setColor({ 0xFF, 0xFF, 0xFF, 0xFF });
		m_rend.clear();

		m_ped.draw();

		m_rend.render();
	}

private:
	sdl::Window m_win;
	sdl::Renderer m_rend;

	//ctl::Timer m_time;

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









































//template<size_t LAMP_AMOUNT>
//class Lamp
//{
//	static constexpr int GROUND = 450;
//	static constexpr sdl::Point<int> LAMP_SPOT = { 70, 20 };
//	static constexpr int LAMP_WIDTH = 50;
//
//	static constexpr double LIGHT_RAD = LAMP_WIDTH * 3. / 8.;
//	static constexpr double LIGHT_BREAK = LAMP_WIDTH / 4.;
//	static constexpr int LAMP_HIGHT = 2. * LIGHT_RAD * LAMP_AMOUNT + LIGHT_BREAK * (LAMP_AMOUNT + 1.);
//
//	static constexpr auto _lightCoordGen_ = [](int idx) constexpr -> sdl::Circle<int, Uint32>
//	{
//		return { static_cast<int>(LAMP_SPOT.x + LAMP_WIDTH / 2.), 
//			static_cast<int>(LAMP_SPOT.y + LIGHT_BREAK + LIGHT_RAD + idx * (2. * LIGHT_RAD + LIGHT_BREAK)), 
//			static_cast<Uint32>(LIGHT_RAD) };
//	};
//
//	static constexpr std::array<sdl::Circle<int, Uint32>, LAMP_AMOUNT> LIGHTS =
//	{
//		_lightCoordGen_(0), _lightCoordGen_(1), _lightCoordGen_(2)
//	};
//
//public:
//	Lamp(sdl::Renderer* r)
//		: m_lights{ Light{ r, LIGHTS[0], sdl::RED }, { r, LIGHTS[1], sdl::YELLOW }, { r, LIGHTS[2], sdl::GREEN } }
//		, m_box(r)
//	{
//
//
//		m_box.shape({ LAMP_SPOT.x, LAMP_SPOT.y, LAMP_WIDTH, LAMP_HIGHT });
//	}
//
//	void draw() const
//	{
//		m_box.renderer()->setColor({ 0, 0, 0, 0xFF });
//		m_box.draw();
//
//		for (const auto& i : m_lights)
//			i.draw();
//	}
//
//private:
//	std::array<Light, LAMP_AMOUNT> m_lights;
//	sdl::RectDraw<> m_box;
//};
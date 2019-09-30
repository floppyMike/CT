#include <SDL.h>
#include <CustomLibrary/SDL/SDLWindow.h>
#include <CustomLibrary/SDL/Engine.h>
#include <CustomLibrary/SDL/Geometry.h>

using namespace ctl;

/* SDL Update List:
- Replace "ImplRend" template with SDL_Renderer* -> Removes a lot of complexity
*/


class LampGen
{
public:


};


class Light
{
public:
	Light(sdl::Renderer* rend, const sdl::Circle<int, unsigned int>& c, const SDL_Color& col)
		: m_circle(rend)
		, m_color(col)
	{
		m_circle.shape(c);
	}

	void draw() const
	{
		m_circle.renderer()->setColor(m_color);
		m_circle.drawFilled();
	}

private:
	sdl::CircleDraw<> m_circle;
	SDL_Color m_color;
};


template<size_t LAMP_AMOUNT>
class Lamp
{
	static constexpr int GROUND = 450;
	static constexpr sdl::Point<int> LAMP_SPOT = { 70, 20 };
	static constexpr int LAMP_WIDTH = 50;

	static constexpr double LIGHT_RAD = LAMP_WIDTH * 3. / 8.;
	static constexpr double LIGHT_BREAK = LAMP_WIDTH / 4.;
	static constexpr int LAMP_HIGHT = 2. * LIGHT_RAD * LAMP_AMOUNT + LIGHT_BREAK * (LAMP_AMOUNT + 1.);

	static constexpr auto _lightCoordGen_ = [](int idx) constexpr -> sdl::Circle<int, Uint32>
	{
		return { static_cast<int>(LAMP_SPOT.x + LAMP_WIDTH / 2.), 
			static_cast<int>(LAMP_SPOT.y + LIGHT_BREAK + LIGHT_RAD + idx * (2. * LIGHT_RAD + LIGHT_BREAK)), 
			static_cast<Uint32>(LIGHT_RAD) };
	};

	static constexpr std::array<sdl::Circle<int, Uint32>, LAMP_AMOUNT> LIGHTS =
	{
		_lightCoordGen_(0), _lightCoordGen_(1), _lightCoordGen_(2)
	};

public:
	Lamp(sdl::Renderer* r)
		: m_lights{ Light{ r, LIGHTS[0], sdl::RED }, { r, LIGHTS[1], sdl::YELLOW }, { r, LIGHTS[2], sdl::GREEN } }
		, m_box(r)
	{
		m_box.shape({ LAMP_SPOT.x, LAMP_SPOT.y, LAMP_WIDTH, LAMP_HIGHT });
	}

	void draw() const
	{
		m_box.renderer()->setColor({ 0, 0, 0, 0xFF });
		m_box.draw();

		for (const auto& i : m_lights)
			i.draw();
	}

private:
	std::array<Light, LAMP_AMOUNT> m_lights;
	sdl::RectDraw<> m_box;
};


class Window
{
public:
	Window()
		: m_win("Ampel", { 640, 490 })
		, m_rend(&m_win)
		, m_lamp(&m_rend)
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

		m_lamp.draw();

		m_rend.render();
	}

private:
	sdl::Window m_win;
	sdl::Renderer m_rend;

	Lamp m_lamp;
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
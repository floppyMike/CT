#include <SDL.h>
#include <SDL_image.h>
#include <CustomLibrary/SDL/SDLWindow.h>
#include <CustomLibrary/SDL/Engine.h>

using namespace ctl;

class State
{
public:
	State(sdl::Renderer*)
	{
	}

	void event(const SDL_Event&)
	{

	}
	void input(const SDL_Event&) 
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

	}

private:

};


int main(int argc, char** argv)
{
	sdl::SDL sdl;
	sdl.initIMG();

	sdl::SDLWindow<State> win("Ampel", { 640, 490 }, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	win.setState<State>();
	sdl::RunLoop<decltype(win)> run(30);
	run.addWindow(&win);

	run.run();

	return 0;
}
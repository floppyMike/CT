#include "Window.h"

int main(int argc, char** argv)
{
	sdl::SDL sdl;

	Window win;
	sdl::RunLoop<decltype(win)> run;
	run.addWindow(&win);

	run.run(30);

	return 0;
}
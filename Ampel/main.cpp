#include "Window.h"

int main(int argc, char** argv)
{
	try
	{
		sdl::SDL sdl;

		Window win;
		sdl::RunLoop<decltype(win)> run;
		run.addWindow(&win);

		run.run(30);
	}
	catch (const std::exception& w)
	{
		std::cerr << w.what() << '\n';
	}

	return 0;
}
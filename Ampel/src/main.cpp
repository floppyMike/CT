#include "Includes.h"
#include "Window.h"

int main(int argc, char **argv)
{
	try
	{
		sdl::SDL sdl;

		Window						win;
		sdl::RunLoop<decltype(win)> run;
		run.add_window(&win);

		run.run(60);
	}
	catch (const std::exception &w)
	{
		std::cerr << w.what() << '\n';
	}

	return 0;
}

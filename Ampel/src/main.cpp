#include "Application.h"
#include "Includes.h"


auto main(int argc, char **argv) -> int
{
	try
	{
		sdl::SDL sdl;

		App							win;
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

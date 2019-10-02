#include "Window.h"

/* SDL Update List:
- Replace "ImplRend" template with SDL_Renderer* -> Removes a lot of complexity
- Implement missing asserts
- Rename Renderer::clear to fill
- Implement crtp for drawable Geometric Shapes
*/


int main(int argc, char** argv)
{
	sdl::SDL sdl;

	Window win;
	sdl::RunLoop<decltype(win)> run;
	run.addWindow(&win);

	run.run(30);

	return 0;
}
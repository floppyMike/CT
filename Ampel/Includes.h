#pragma once

#include <SDL.h>

#include <CustomLibrary/SDL/Engine.h>
#include <CustomLibrary/SDL/Geometry.h>
#include <CustomLibrary/SDL/Button.h>
#include <CustomLibrary/SDL/Event.h>
#include <CustomLibrary/SDL/State.h>

#include <future>

using namespace ctl;
using namespace std::chrono_literals;

auto mousePosition()
{
	sdl::Point<int> pos;
	SDL_GetMouseState(&pos.x, &pos.y);
	return pos;
}

constexpr sdl::Dim<int> WINDOW_SIZE = { 1280, 720 };

enum Events
{
	BUTTON_PRESS
};

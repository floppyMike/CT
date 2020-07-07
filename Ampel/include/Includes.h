#pragma once

#include <SDL2/SDL.h>

#include <CustomLibrary/SDL/Engine.h>
#include <CustomLibrary/SDL/Window.h>
#include <CustomLibrary/SDL/Geometry.h>
#include <CustomLibrary/SDL/Button.h>
#include <CustomLibrary/SDL/Event.h>
#include <CustomLibrary/SDL/State.h>

#include <future>
#include <numeric>
#include <iostream>

using namespace ctl;
using namespace std::chrono_literals;

auto mousePosition()
{
	mth::Point<int> pos;
	SDL_GetMouseState(&pos.x, &pos.y);
	return pos;
}

constexpr mth::Dim<int> WINDOW_SIZE = { 1280, 720 };

enum Events
{
	BUTTON_PRESS
};

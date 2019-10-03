#pragma once

#include <SDL.h>
#include <CustomLibrary/SDL/SDLWindow.h>
#include <CustomLibrary/SDL/Engine.h>
#include <CustomLibrary/SDL/Geometry.h>
#include <CustomLibrary/SDL/Button.h>
#include <CustomLibrary/SDL/Event.h>

using namespace ctl;
using namespace std::chrono_literals;

constexpr sdl::Dim<int> WINDOW_SIZE = { 1280, 720 };

enum Events
{
	BUTTON_PRESS
};

#pragma once

#include <SDL2/SDL.h>

#include <CustomLibrary/BasicTypes.h>

#include <CustomLibrary/SDL/Engine.h>
#include <CustomLibrary/SDL/Window.h>
#include <CustomLibrary/SDL/Renderer.h>
#include <CustomLibrary/SDL/Button.h>
#include <CustomLibrary/SDL/Event.h>
#include <CustomLibrary/SDL/Geometry.h>
#include <CustomLibrary/SDL/State.h>
#include <CustomLibrary/SDL/Drawable.h>

#include <future>
#include <iostream>
#include <numeric>
#include <chrono>

using namespace ctl;
using namespace std::chrono_literals;


static constexpr mth::Dim<int> WINDOW_DEFAULT_SIZE = { 1280, 720 };

enum Events
{
	BUTTON_PRESS
};

#pragma once

#include <SDL2/SDL.h>

#include <CustomLibrary/SDL/Engine.h>
#include <CustomLibrary/SDL/Window.h>
#include <CustomLibrary/SDL/Geometry.h>
#include <CustomLibrary/SDL/Button.h>
#include <CustomLibrary/SDL/Event.h>
#include <CustomLibrary/SDL/State.h>
#include <CustomLibrary/SDL/Collider.h>

#include <future>
#include <numeric>
#include <iostream>

using namespace ctl;
using namespace std::chrono_literals;

static constexpr mth::Dim<int> WINDOW_SIZE = { 1280, 720 };

enum Events
{
	BUTTON_PRESS
};

template<typename T>
concept has_shape = requires(const T &t)
{
	t->shape();
};

template<typename Arr>
auto range_collided(Arr &arr) requires has_shape<decltype(arr[0])>
{
	return std::find_if(std::rbegin(arr),
						std::rend(arr), // Using reverse iterator for quicker responce
										// newer things get deleted quicker
						[](const auto &tn) { return sdl::collision(tn->shape(), sdl::mouse_position()); });
}
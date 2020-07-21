#pragma once

#include "Includes.h"

static constexpr mth::Dim<int> NODE_DIM = { 5, 5 };
using Node								= sdl::RectFrame;

auto operator<<(sdl::Renderer &r, const Node &n) -> sdl::Renderer &
{
	sdl::Draw<const Node>(&n, &r).filled_rect();
	return r;
}
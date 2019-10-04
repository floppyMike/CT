#pragma once

#include "Includes.h"
#include "RoadLights.h"

using Node = sdl::Point<int>;


class Road
{
public:
	//Road(sdl::Renderer* r, const sdl::Point<int>& pos)
	//	: light(r, pos)
	//{
	//}



private:
	//std::chrono::steady_clock::time_point onTill;
	std::vector<Node*> path;
};

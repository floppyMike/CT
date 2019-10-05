#pragma once

#include "Includes.h"
#include "RoadLights.h"


struct TrafficNode
{
	TrafficNode(sdl::Renderer* r, const sdl::Point<int>& pos)
		: light(r, pos)
	{
	}

	LightPair light;
	std::vector<Node*> nodes;
	std::vector<sdl::LineDraw<>*> lines;
};

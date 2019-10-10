#pragma once

#include "Includes.h"
#include "TrafficConnector.h"
#include "Line.h"


struct TrafficNode : TrafficConnector
{
	using TrafficConnector::TrafficConnector;

	std::vector<DNode*> nodes;
	std::vector<Link*> lines;
};

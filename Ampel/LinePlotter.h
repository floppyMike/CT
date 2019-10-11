#pragma once

#include "Includes.h"
#include "Line.h"


class LinePlotter
{
public:
	LinePlotter()
	{
	}

private:
	std::unique_ptr<DLink> m_link;
};

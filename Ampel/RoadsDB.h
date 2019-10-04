#pragma once

#include "Includes.h"
#include "RoadLights.h"

struct Road
{
	Road(sdl::Renderer* r, const sdl::Point<int>& pos)
		: light(r, pos)
	{
	}

	RoadLights light;
	//std::chrono::steady_clock::time_point onTill;
	//std::vector<size_t> path;
};


class RoadsDB
{
public:
	RoadsDB() = default;

	template<typename... Arg>
	auto& push(Arg&&... args)
	{
		return m_lights.emplace_back(std::forward<Arg>(args)...);
	}

	auto begin() const noexcept
	{
		return m_lights.begin();
	}
	auto begin() noexcept
	{
		return m_lights.begin();
	}

	auto end() const noexcept
	{
		return m_lights.end();
	}
	auto end() noexcept
	{
		return m_lights.end();
	}

	Road* insideWhich(const sdl::Point<int>& p) noexcept
	{
		Road* ptr = nullptr;
		for (auto iter = m_lights.rbegin(); iter != m_lights.rend(); ++iter)
			if (sdl::collision(iter->light.shape(), p))
			{
				ptr = &*iter;
				break;
			}

		return ptr;
	}

private:
	std::vector<Road> m_lights;
};

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


class LightsPairsDB
{
public:
	using iterator = std::vector<TrafficNode>::iterator;
	using reverse_iterator = std::vector<TrafficNode>::reverse_iterator;

	LightsPairsDB() = default;

	template<typename... Arg>
	auto& push(Arg&&... args)
	{
		return m_lights.emplace_back(std::forward<Arg>(args)...);
	}

	void erase(iterator iter)
	{
		m_lights.erase(iter);
	}

	auto begin() const noexcept
	{
		return m_lights.begin();
	}
	auto begin() noexcept
	{
		return m_lights.begin();
	}
	auto rbegin() const noexcept
	{
		return m_lights.rbegin();
	}
	auto rbegin() noexcept
	{
		return m_lights.rbegin();
	}

	auto end() const noexcept
	{
		return m_lights.end();
	}
	auto end() noexcept
	{
		return m_lights.end();
	}
	auto rend() const noexcept
	{
		return m_lights.rend();
	}
	auto rend() noexcept
	{
		return m_lights.rend();
	}

private:
	std::vector<TrafficNode> m_lights;
};

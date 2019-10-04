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
	using iterator = std::vector<Road>::iterator;

	RoadsDB() = default;

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

	auto end() const noexcept
	{
		return m_lights.end();
	}
	auto end() noexcept
	{
		return m_lights.end();
	}

	template<typename Ret>
	Ret insideWhich(const sdl::Point<int>& p) noexcept
	{
		auto iter = m_lights.end();
		if (!m_lights.empty())
			do
			{
				--iter;
				if (sdl::collision(iter->light.shape(), p))
					break;
				else if (iter == m_lights.begin())
				{
					iter = m_lights.end();
					break;
				}
			} while (true);

		if constexpr (std::is_same_v<Ret, iterator>)
			return iter;
		else if constexpr (std::is_same_v<Ret, Road*>)
			return iter == m_lights.end() ? nullptr : &*iter;
		else
			static_assert(false, "Incombatible type.");
	}

private:
	std::vector<Road> m_lights;
};

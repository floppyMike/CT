#pragma once

#include "Includes.h"
#include "Road.h"


struct TrafficNode
{
	TrafficNode(sdl::Renderer* r, const sdl::Point<int>& pos)
		: light(r, pos)
	{
	}

	LightPair light;
	Road road;
};


class LightsPairsDB
{
public:
	using iterator = std::vector<TrafficNode>::iterator;

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
		else if constexpr (std::is_same_v<Ret, TrafficNode*>)
			return iter == m_lights.end() ? nullptr : &*iter;
		else
			static_assert(false, "Incombatible type.");
	}

private:
	std::vector<TrafficNode> m_lights;
};

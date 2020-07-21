#pragma once

#include "Includes.h"
#include "RoadsDB.h"
#include "TrafficNodeDB.h"

/*
class Sequence
{
public:
	using iterator		 = std::vector<DTrafficNodeDB::iterator>::iterator;
	using const_iterator = std::vector<DTrafficNodeDB::iterator>::const_iterator;

	void push(DTrafficNodeDB::iterator iter) { m_seq.emplace_back(iter); }

	auto begin() { return m_seq.begin(); }
	auto end() { return m_seq.end(); }

	auto begin() const { return m_seq.begin(); }
	auto end() const { return m_seq.end(); }

private:
	std::vector<DTrafficNodeDB::iterator> m_seq;
};
*/

class RoadLightsState
{
public:
	enum class TrafficState
	{
		PASSING,
		STOPPED
	};

	static constexpr std::chrono::seconds YELLOW_TRANFER_TIME = 2s;

	explicit RoadLightsState(DTrafficNode *b)
		: m_box(b)
	{
	}

	void update()
	{
		if (std::chrono::steady_clock::now() >= m_tranferTill)
		{
			m_box->vehLight().change(1, false);

			if (!m_state)
				m_box->vehLight().change(0, true);
			else
			{
				m_box->vehLight().change(0, false);
				m_box->vehLight().change(2, true);
			}

			m_tranferTill = std::chrono::steady_clock::time_point::max();
		}
	}

	void flipTo(bool state)
	{
		if (state == m_state)
			return;

		m_state = state;

		m_box->vehLight().change(1, true);

		if (!m_state)
			m_box->vehLight().change(2, false);

		m_tranferTill = std::chrono::steady_clock::now() + YELLOW_TRANFER_TIME;
	}

	void flip() noexcept { flipTo(!state()); }
	auto state() noexcept -> bool { return m_state; }

	[[nodiscard]] auto traffic_node() const noexcept { return m_box; }

private:
	DTrafficNode *m_box;

	std::chrono::steady_clock::time_point m_tranferTill = std::chrono::steady_clock::time_point::max();
	bool								  m_state		= false; // false -> Stop ; true -> Pass
};

using Sequence = std::vector<RoadLightsState*>;
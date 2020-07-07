#pragma once

#include "LightBox.h"
#include "Node.h"


template<template<typename> class... Func>
class FRoadLights : public Func<FRoadLights<Func...>>...
{
public:
	static constexpr int WIDTH = 21;
	static constexpr int DIS = 5;
	static constexpr int TOTAL_WIDTH = (WIDTH << 1) + DIS;

	FRoadLights() = delete;

	FRoadLights(sdl::Renderer* r, const mth::Point<int>& pos)
		: m_veh(r, pos, WIDTH, { Light::RED, Light::YELLOW, Light::GREEN })
		, m_ped(r, { pos.x + WIDTH + DIS, pos.y }, WIDTH, { Light::RED, Light::GREEN })
	{
		m_veh.change(0, true);
	}

	mth::Rect<int, int> shape() const noexcept
	{
		return { m_veh.shape().pos(), { TOTAL_WIDTH, m_veh.shape().h } };
	}

	void translate(const mth::Point<int>& delta)
	{
		m_veh.translate(delta);
		m_ped.translate(delta);
	}

	constexpr auto pos() const noexcept
	{
		return m_veh.shape().pos();
	}

	auto& vehLight() noexcept
	{
		return m_veh;
	}
	auto& pedLight() noexcept
	{
		return m_veh;
	}

	void draw()
	{
		m_veh.draw();
		m_ped.draw();
	}

protected:
	LightBox m_veh;
	LightBox m_ped;
};


template<typename T>
class RoadLightsLightChanger : public ctl::crtp<T, RoadLightsLightChanger>
{
public:
	enum class TrafficState { PASSING, STOPPED };
	static constexpr std::chrono::seconds YELLOW_TRANFER_TIME = 2s;

	void update()
	{
		if (std::chrono::steady_clock::now() >= m_tranferTill)
		{
			this->_().vehLight().change(1, false);

			if (m_state == TrafficState::STOPPED)
				this->_().vehLight().change(0, true);
			else
			{
				this->_().vehLight().change(0, false);
				this->_().vehLight().change(2, true);
			}

			m_tranferTill = std::chrono::steady_clock::time_point::max();
		}
	}

	void flipTo(TrafficState state)
	{
		if (state == m_state)
			return;
		m_state = state;

		this->_().vehLight().change(1, true);

		if (m_state == TrafficState::STOPPED)
			this->_().vehLight().change(2, false);

		m_tranferTill = std::chrono::steady_clock::now() + YELLOW_TRANFER_TIME;
	}

	void flip()
	{
		switch (m_state)
		{
		case TrafficState::PASSING:
			flipTo(TrafficState::STOPPED);
			break;

		case TrafficState::STOPPED:
			flipTo(TrafficState::PASSING);
			break;

		default:
			break;
		}
	}

	TrafficState state() noexcept
	{
		return m_state;
	}

private:
	std::chrono::steady_clock::time_point m_tranferTill = std::chrono::steady_clock::time_point::max();
	TrafficState m_state = TrafficState::STOPPED;
};


using RoadLights = FRoadLights<RoadLightsLightChanger>;
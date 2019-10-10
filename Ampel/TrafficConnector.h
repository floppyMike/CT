#pragma once

#include "Includes.h"
#include "RoadLights.h"

class TrafficConnector : RoadLights
{
	static constexpr int IN_OUT_DIS = 10;

public:
	TrafficConnector(sdl::Renderer* r, const sdl::Point<int>& pos)
		: RoadLights(r, pos)
		, m_out(r, { pos.x + (WIDTH >> 1), pos.y + m_veh.shape().h + IN_OUT_DIS })
		, m_in(r, { pos.x + (WIDTH >> 1) + WIDTH, pos.y + m_veh.shape().h + IN_OUT_DIS })
	{
	}

	auto& outNode() noexcept { return m_out; }
	const auto& outNode() const noexcept { return m_out; }

	auto& inNode() noexcept { return m_in; }
	const auto& inNode() const noexcept { return m_in; }

	sdl::Rect<int, int> shape() const noexcept
	{
		return { m_veh.shape().pos(), { TOTAL_WIDTH, m_veh.shape().h + IN_OUT_DIS + DNode::DIM.h } };
	}

	void translate(const sdl::Point<int>& delta)
	{
		RoadLights::translate(delta);
		m_out.translate(delta);
		m_in.translate(delta);
	}

	void draw()
	{
		RoadLights::draw();
		m_out.draw();
		m_in.draw();
	}

	using RoadLights::pos;

private:
	DNode m_out;
	DNode m_in;
};
